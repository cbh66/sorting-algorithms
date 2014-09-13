/*---------------------------------------------------------------------------*\
 *  get-timing-stats.cpp                                                     *
 *  Written by:  Colin Hamilton, Tufts University                            *
 *  Last Modified:  2014-9-13                                                *
 *  Description:                                                             *
 *    This program uses the ./time shell program to gather statistics on the *
 *    speed of a given executable, and records that record in the source     *
 *    code of the file itself - in a comment appended to the end.            *
 *    Note that it is assumed that the source code of the file is the name   *
 *    of the executable, but with an extension indicating the language.      *
 *  TO DO:                                                                   *
 *    Allow the program to work with more than just CPP files.               *
 *    Allow the user to specify the name of the output file.                 *
 *    Allow the user to specify any sentinel in the output file to indicate  *
 *      the place to insert the data.                                        *
 *    Add a --quiet option to remove prompts and narration.                  *
 *    Maybe add some outputs to only display with --verbose.                 *
 *    Allow the user to specify the precision of the data recorded.          *
 *    Have an option whereby the program can find data of this format in a   *
 *      file, and delete it.  (May need to add a terminating sentinal, even  *
 *      something like the word END.  But it has to not be a valid file /   *
 *      test name).                                                         *
 *    Add standard --version and --help options.                             *
 *    Allow the user to specify the header that goes above the data, perhaps *
 *      allowing options like --show-date or something.                      *
 *    Allow searching the sentinel to ignore whitespace, or consider all     *
 *      whitespace equal.                                                    *
\*---------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

/*  Holds the data for a single test run several times.
 *  Each vector should be the same length.
 */
struct TimingData {
    string test_name;
    vector<double> clock_time;
    vector<double> user_time;
    vector<double> system_time;
};


void read_one_test(string file_name, map<string, TimingData> &tests);
void add_times(map<string, TimingData> &tests, string test_name, double real,
               double user, double sys);
double get_time(ifstream &input);
void run_system_call(string command, bool echo = true);
void print_results(map<string, TimingData> &tests, ofstream &output);
void print_vector(vector<double> &v, string seperator, ofstream &output);
void copy_until_sentinel(ifstream &input, ofstream &output, string sentinel);
void copy_after_sentinel(ifstream &input, ofstream &output);


int main(int argc, char *argv[])
{
    string timing_program = "./time";
    string temp_timing_file = "/tmp/timing_stats_output.data";
    string extension = ".cpp";
    string program_name;
    int num_tests = 5;
/*-------------------------Parse program arguments---------------------------*/
    if (argc > 3 || argc < 2) {
        cerr << "Usage: ./get-timing-stats [number of tests to run]"
             << " file-to-test" << endl;
        return 1;
    }
    /*  First argument is either a number or the program name.
     *  If it's a number, then the second argument is the program name.
     */
    if (!(num_tests = atoi(argv[1]))) {
        num_tests = 5;
        program_name = argv[1];
    } else if (argc > 2) {
        program_name = argv[2];
    } else {
        cerr << "Please specify a program to test." << endl;
        return 1;
    }
    string temp_output_file = "/tmp/" + program_name + extension;

/*-------------------------------Now run tests-------------------------------*/
    map<string, TimingData> tests;
    cout << "Running " << num_tests << " tests on " << program_name << endl;
    string command = timing_program + " " + program_name + " "
                   + temp_timing_file;
    string remove_command = "rm " + temp_timing_file;
    for (int i = 0; i < num_tests; ++i) {
        run_system_call(command, true);
        read_one_test(temp_timing_file, tests);
        run_system_call(remove_command, true);
    }

/*--------------Now send results to comments in source file------------------*/
    ofstream output;
    ifstream input;
    output.open(temp_output_file.c_str());
    if (!output.is_open()) cerr << "Failed to open output";
    input.open((program_name + extension).c_str());
    if (!input.is_open()) cerr << "Failed to open input";
    output.setf(ios::fixed);
    copy_until_sentinel(input, output, "/* STATS:");
    print_results(tests, output);
    copy_after_sentinel(input, output);
    run_system_call("mv " + temp_output_file + " " + program_name + extension,
                    true);
    return 0;
}


/*  run_system_call()
 *  Runs a system call, given a string containing the command to execute.
 *  Parameters:  command is the command to execute.
 *               echo specifies whether the command should be written to cerr
 *                 before it is run, and defaults to true.
 */
void run_system_call(string command, bool echo)
{
    if (echo) cerr << command << endl;
    system(command.c_str());
}


/*  read_one_test()
 *  Reads the output file of a single timing test and updates the list of tests
 *    with the new information.  Any new tests will have a position created
 *    for them, and any tests that have already been run will have this round's
 *    data added.
 *  Parameters: the name of the file to which the tests were written,
 *    and the map of tests to update.
 *  Notes: The function may throw an exception if the file could not be opened.
 *    It is expected that each test will be in the following format:
 *  
 *  Some phrase uniquely identifying the test
 *  real  #m##s
 *  user  #m##s
 *  sys   #m##s END-OF-TEST
 *
 *  Where END-OF-TEST does not represent a literal string.
 *  It is an UNCHECKED runtime error if the format is different from this.
 *  The results are undefined.
 */
void read_one_test(string file_name, map<string, TimingData> &tests)
{
    ifstream input;
    string test_name, temp;
    double real, user, sys;
    input.open(file_name.c_str());
    if (!input.is_open()) throw string("Could not open file");
    input >> temp;
    while (input.good()) {
        if (temp == "real") {
            real = get_time(input);
        }
        else if (temp == "user") {
            user = get_time(input);
        }
        else if (temp == "sys") {
            sys = get_time(input);
            add_times(tests, test_name, real, user, sys);
            test_name = "";
        } else {
            test_name += " " + temp;
        }
        input >> temp;
    }
}


/*  get_time()
 *  Reads the time from a given input file and returns the value, as a double
 *    representing the number of seconds.  The format of the time read is 
 *    the default format returned by the shell's time utility.
 *  Parameters:  The input file stream to read from.
 *  Notes:  This function may throw an exception if the stream is not currently
 *    pointing right before a sequence of characters of the form
 *      #m####s
 *    That is, the sequence (integer - letter m - decimal number - letter s)
 */
double get_time(ifstream &input)
{
    int min;
    double sec;
    input >> min;
    if (input.get() != 'm') throw string("Formatting error");
    input >> sec;
    if (input.get() != 's') throw string("formatting error");
    return (min * 60) + sec;
}


/*  add_times()
 *  Adds the three times given to a particular test in the list of tests.
 *    If the test has not yet been run, it is created.
 *  Parameters:  The map of tests to update,
 *               The name of the specific test to update in the map,
 *               The three times to add, in seconds.
 */
void add_times(map<string, TimingData> &tests, string test_name, double real,
               double user, double sys)
{
    map<string, TimingData>::iterator elem = tests.find(test_name);
    if (elem == tests.end()) {
        tests[test_name].test_name = test_name;
    }
    tests[test_name].clock_time.push_back(real);
    tests[test_name].user_time.push_back(user);
    tests[test_name].system_time.push_back(sys);
}


/*  print_results()
 *  Prints the results of running all tests.  For each test, the times for each
 *    trial are printed, and then the average.
 *  Parameters:  The map of tests, and the output file to print to.
 *  Format:  The output is the following format, with an entry for each test:
 *
 *    RESULTS HEADER
 *    THIS TEST'S HEADER
 *             TRIAL 0      TRIAL 1     ...     AVG
 *  Real:      #s           #s          ...     #s
 *  User:      #s           #s          ...     #s
 *  System:    #s           #s          ...     #s
 *
 *  Where RESULTS HEADER, by default, is "Tests run on (current date/time)"
 *    and is printed only once, before all tests are listed.
 *  THIS TEST'S HEADER is whatever was read in the input before each test's
 *    time.
 */
void print_results(map<string, TimingData> &tests, ofstream &output)
{
    map<string, TimingData>::iterator i = tests.begin();
    map<string, TimingData>::iterator end = tests.end();
    time_t current_time = time(NULL);
    output << endl << "Tests run on " << ctime(&current_time);
    while (i != end) {
        output << i->first << endl;
        int size = i->second.clock_time.size();
        for (int j = 0; j < size; ++j) {
            output << "        TRIAL " << j;
        }
        output << "       AVG" << endl;
        output << "Real:   ";
        print_vector(i->second.clock_time, "s      ", output);
        output << "s" << endl << "User:   ";
        print_vector(i->second.user_time, "s      ", output);
        output << "s" << endl << "System: ";
        print_vector(i->second.system_time, "s      ", output);
        output << "s" << endl << endl;
        ++i;
    }
}


/*  print_vector()
 *  Prints each entry in a vector to an output stream, and then prints the
 *    average of all entries in the vector.
 *  Parameters: The vector to print, the string to print between each entry,
 *              and the output file to print to.
 *  Output is a single line of the format:
 *    [entry 0][seperator][entry 1][seperator]...[entry n][seperator][average]
 *  Note that currently, each entry is aligned to a width of 8:
 *    3 characters (padded with spaces if there aren't enough digits),
 *    the decimal point, and four digits after the decimal.
 *    This makes it easier to align multiple lines so the decimals match.
 *    A future version may allow the user to specify the width and precision.
 */
void print_vector(vector<double> &v, string seperator, ofstream &output)
{
    int size = 0;
    double total = 0.0;
    vector<double>::iterator end = v.end();
    output.precision(4);
    output.fill(' ');
    for (vector<double>::iterator i = v.begin(); i != end; ++i) {
        total += *i;
        ++size;
        output << setw(8) << std::right << *i << seperator;
    }
    output << total / size;
}


/*  copy_until_sentinel()
 *  Writes the contents of one file to another, stopping when the sequence of
 *    characters in sentinel is encountered.  Note that these characters are
 *    also copied to the file.
 *  Parameters:  The input file stream, the output file stream, and the
 *               sentinel string to search for.
 *  Note:  If the sentinel does not appear in the input file, this function
 *    will copy the entire file, leaving the input stream at the EOF.
 *  Future versions may allow for wildcard characters, or provide an option
 *    to consider all whitespace equal.  For now, the sentinel must match
 *    exactly, character-for-character.
 */
void copy_until_sentinel(ifstream &input, ofstream &output, string sentinel)
{
    char c = input.get();
    while (c != EOF) {
        for (unsigned i = 0; c == sentinel[i]; c = input.get(), ++i) {
            output.put(c);
            if (i == sentinel.length() - 1) return;
        }
        output.put(c);
        c = input.get();
    }
}


/*  copy_after_sentinel()
 *  Copies an input file stream to an output file stream.
 *  Parameters:  The input file stream and the output file stream.
 */
void copy_after_sentinel(ifstream &input, ofstream &output)
{
    char c;
    c = input.get();
    while (c != EOF) {
        output.put(c);
        c = input.get();
    }
}
