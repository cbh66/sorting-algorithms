#include "program-output.h"
#include <iomanip>
using namespace std;


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
void print_results(const TimeSet &tests, ostream &output, string header)
{
    TimeSet::const_iterator i = tests.begin();
    TimeSet::const_iterator end = tests.end();
    output << header;
    output.setf(ios::fixed);
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
void print_vector(const vector<double> &v, string seperator, ostream &output)
{
    int size = 0;
    double total = 0.0;
    vector<double>::const_iterator end = v.end();
    output.precision(4);
    output.fill(' ');
    for (vector<double>::const_iterator i = v.begin(); i != end; ++i) {
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
