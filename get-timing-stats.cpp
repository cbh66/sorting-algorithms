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
 *    Add a --quiet option to remove prompts and narration.                  *
 *    Maybe add some outputs to only display with --verbose.                 *
 *    Allow the user to specify the precision of the data recorded.          *
 *    Have an option whereby the program can find data of this format in a   *
 *      file, and delete it.  (May need to add a terminating sentinal, even  *
 *      something like the word END.  But it has to not be a valid file /    *
 *      test name).                                                          *
 *    Allow the user to specify the header that goes above the data, perhaps *
 *      allowing options like --show-date or something.                      *
 *    Allow searching the sentinel to ignore whitespace, or consider all     *
 *      whitespace equal.                                                    *
 *    Consolidate this program with the shell-based time program.            *
 *    Split the code into modules, maybe classes.                            *
\*---------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
using namespace std;

const string VERSION_INFORMATION =
    "Get Timing Stats 1.0\n"
    "Copyright (C) 2014 Colin B Hamilton\n"
    "This is free software: you are free to change and redistribute it.\n"
    "There is NO WARRANTY, to the extent permitted by law.";

const string USAGE_INFORMATION =
    "Usage: get-timing-stats [options] executable";

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
void quiet_prompt(string s);

void print_results(map<string, TimingData> &tests, ostream &output);
void print_vector(vector<double> &v, string seperator, ostream &output);
void copy_until_sentinel(ifstream &input, ofstream &output, string sentinel);
void copy_after_sentinel(ifstream &input, ofstream &output);

void parse_command_line_args(int argc, char *argv[]);
void validate_command_line_args();
string escape_string(string s);
bool BE_QUIET = false;
bool BE_VERBOSE = false;
bool APPEND_OUTPUT = false;
bool INSERT_OUTPUT = false;
string PROGRAM_NAME;
string OUTPUT_FILE_NAME;
string OUTPUT_SENTINEL;
int NUM_TESTS;


int main(int argc, char *argv[])
{
    namespace fs = boost::filesystem;
    string timing_program = "./time";
    string temp_timing_file = fs::temp_directory_path().native()
                            + fs::unique_path().native() + ".time";

    parse_command_line_args(argc, argv);
    string temp_output_file = tmpnam(NULL);

    if (BE_QUIET) cerr << "Being quiet" << endl;
    if (BE_VERBOSE) cerr << "Being verbose" << endl;
    if (APPEND_OUTPUT) cerr << "Appending output" << endl;
    if (INSERT_OUTPUT) cerr << "Inserting output" << endl;
    cerr << "Sentinel: " << OUTPUT_SENTINEL << endl;
    cerr << "Program name: " << PROGRAM_NAME << endl;
    cerr << "Output file: " << OUTPUT_FILE_NAME << endl;
    cerr << "Temp file: " << temp_timing_file << endl;

    map<string, TimingData> tests;
    quiet_prompt("Running " + boost::lexical_cast<string>(NUM_TESTS) +
                 " tests on " + PROGRAM_NAME);
    string command = timing_program + " " + PROGRAM_NAME + " "
                   + temp_timing_file;
    string remove_command = "rm " + temp_timing_file;
    for (int i = 0; i < NUM_TESTS; ++i) {
        quiet_prompt("Running test set " + boost::lexical_cast<string>(i + 1) +
                     " of " + boost::lexical_cast<string>(NUM_TESTS));
        run_system_call(command, BE_VERBOSE);
        read_one_test(temp_timing_file, tests);
        fs::resize_file(temp_timing_file, 0);
    }

    if (OUTPUT_FILE_NAME == "") {
        print_results(tests, cout);
        fs::remove(temp_timing_file);
        return 0;
    }

    ofstream output;
    ifstream input;
    output.open(temp_output_file.c_str());
    if (!output.is_open()) {
        cerr << "Unable to create temporary file" << endl;
        return 1;
    }
    output.setf(ios::fixed);
    input.open((OUTPUT_FILE_NAME).c_str());
    if (input.is_open()) {
        copy_until_sentinel(input, output, OUTPUT_SENTINEL);
    }
    print_results(tests, output);
    if (input.is_open()) {
        copy_after_sentinel(input, output);
    }
    fs::rename(temp_output_file, OUTPUT_FILE_NAME);
    fs::remove(temp_timing_file);
    return 0;
}


/*  parse_command_line_args()
 *  Goes through the array of arguments and either sets the appropriate global
 *    variables or calls the appropriate functions.
 */
void parse_command_line_args(int argc, char *argv[])
{
    namespace po = boost::program_options;
    po::variables_map args;
    po::options_description generic("Generic options");
    po::positional_options_description p_desc;
    generic.add_options()
        ("help,h", "Produce help message")
        ("version,v", "Produce version, origin, and legal information")
        ("quiet,q", po::bool_switch(&BE_QUIET),
            "Suppress non-error-related program output")
        ("verbose,v", po::bool_switch(&BE_VERBOSE),
            "Print detailed output during program operation")
        ("input", po::value<string>(&PROGRAM_NAME)->required(),
            "Specify executable to run")
        ("output,o", po::value<string>(&OUTPUT_FILE_NAME),
            "Specify file to output to")
        ("append,a", po::bool_switch(&APPEND_OUTPUT),
            "Append report to end of output file")
        ("insert,i", po::bool_switch(&INSERT_OUTPUT),
            "Insert report after a sentinel in output file")
        ("sentinel,s", po::value<string>(&OUTPUT_SENTINEL),
            "Provide the sentinel after which to insert the report\n"
            "(Only available in insert mode)")
        ("times,t", po::value<int>(&NUM_TESTS)->default_value(1),
            "Specify the number of times to repeat the set of tests")
    ;
    p_desc.add("input", 1);
    try {
        po::store(po::command_line_parser(argc, argv).
                  options(generic).positional(p_desc).run(), args);
        po::notify(args);
    } catch (exception &err) {
        cerr << "Error in arguments: " << err.what() << endl;
        cerr << "(For help, use the --help or -h options)" << endl;
        exit(1);
    }

    if (args.count("help")) {
        cout << USAGE_INFORMATION << endl;
        cout << generic;
        exit(0);
    }
    if (args.count("version")) {
        cout << VERSION_INFORMATION << endl;
        exit(0);
    }
    validate_command_line_args();
}

/*  validate_command_line_args()
 *  Searches for inconsistencies among the program's settings.  Sets some
 *    default values for cases where arguments were not specified.
 *    Uses backslashes in input strings as escape characters.
 */
void validate_command_line_args()
{
    if (BE_QUIET && BE_VERBOSE) {
        cerr << "Cannot be both quiet and verbose.  Please choose one."
             << endl;
        exit(1);
    }
    if (APPEND_OUTPUT && INSERT_OUTPUT) {
        cerr << "Cannot both append and insert output.  Please choose one."
             << endl;
        exit(1);
    }
    // If neither mode is specified, insert if a sentinel has been given
    if (!APPEND_OUTPUT && !INSERT_OUTPUT) {
        if (OUTPUT_SENTINEL != "") INSERT_OUTPUT = true;
        else APPEND_OUTPUT = true;
    }
    OUTPUT_FILE_NAME = escape_string(OUTPUT_FILE_NAME);
}

/*  escape_string()
 *  Parses a string and interprets it C-style, interpretting backslashes as
 *    escape characters.  This function is even more permissive; if unknown
 *    escape sequences are encountered, they are interpretted literally.
 *    Returns the string with the proper characters inserted
 *    (eg newline, tab, bell).
 */
string escape_string(string s)
{
    string r_val = "";
    char escape_char = '\\';
    int len = s.length();
    for (int i = 0; i < len; ++i) {
        if (s[i] == escape_char) {
            if (i < len - 1) {
                switch (s[++i]) {
                    case '0':  r_val += '\0'; break;
                    case 'a':  r_val += '\a'; break;
                    case 'b':  r_val += '\b'; break;
                    case 'e':  r_val += '\e'; break;
                    case 'f':  r_val += '\f'; break;
                    case 'n':  r_val += '\n'; break;
                    case 'r':  r_val += '\r'; break;
                    case 't':  r_val += '\t'; break;
                    case 'v':  r_val += '\v'; break;
/*                  case '\\': r_val += '\\'; break;  Escaped on command line
                    case '\'': r_val += '\''; break;
                    case '\"': r_val += '\"'; break;*/
                    default:
                        r_val += escape_char;
                        r_val += s[i];
                }
                continue;
            }
        }
        r_val += s[i];
    }
    return r_val;
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


/*  quiet_prompt()
 *  Prints the given string, followed by a newline, unless the user has set
 *    quiet mode.
 */
void quiet_prompt(string s)
{
    if (!BE_QUIET) cerr << s << endl;
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
void print_results(map<string, TimingData> &tests, ostream &output)
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
void print_vector(vector<double> &v, string seperator, ostream &output)
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
    output << setw(8) << total / size;
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
