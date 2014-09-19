#include <fstream>
#include "timing-data.h"
using namespace std;



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
static double get_time(ifstream &input)
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
static void add_times(TimeSet &tests, string test_name, double real,
               double user, double sys)
{
    TimeSet::iterator elem = tests.find(test_name);
    if (elem == tests.end()) {
        tests[test_name].test_name = test_name;
    }
    tests[test_name].clock_time.push_back(real);
    tests[test_name].user_time.push_back(user);
    tests[test_name].system_time.push_back(sys);
}


/*  read_one_test()
 *  Reads the output file of a single timing test and updates the list of tests
 *    with the new information.  Any new tests will have a position created
 *    for them, and any tests that have already been run will have this round's
 *    data added.
 *  Return value: none, but the tests parameter is modified by reference.
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
 *  The results are then undefined.
 */
void read_one_test(string file_name, TimeSet &tests)
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
