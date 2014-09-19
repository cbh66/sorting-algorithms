/*---------------------------------------------------------------------------*\
 *  get-timing-stats.cpp                                                     *
 *  Written by:  Colin Hamilton, Tufts University                            *
 *  Created:  2014-9-13                                                *
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
#include <fstream>
#include <ctime>
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include "timing-data.h"
#include "program-output.h"
using namespace std;

const string VERSION_INFORMATION =
    "Get Timing Stats 1.0\n"
    "Copyright (C) 2014 Colin B Hamilton\n"
    "This is free software: you are free to change and redistribute it.\n"
    "There is NO WARRANTY, to the extent permitted by law.";

const string USAGE_INFORMATION =
    "Usage: get-timing-stats [options] executable";

void quiet_prompt(string s);
void run_system_call(string command, bool echo = true);
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
string OUTPUT_HEADER;
int NUM_TESTS;


int main(int argc, char *argv[])
{
    namespace fs = boost::filesystem;
    string timing_program = "./time";

    parse_command_line_args(argc, argv);
    string temp_timing_file = fs::temp_directory_path().native()
                            + fs::unique_path().native() + ".time";

    if (BE_QUIET) cerr << "Being quiet" << endl;
    if (BE_VERBOSE) cerr << "Being verbose" << endl;
    if (APPEND_OUTPUT) cerr << "Appending output" << endl;
    if (INSERT_OUTPUT) cerr << "Inserting output" << endl;
    cerr << "Sentinel: " << OUTPUT_SENTINEL << endl;
    cerr << "Program name: " << PROGRAM_NAME << endl;
    cerr << "Output file: " << OUTPUT_FILE_NAME << endl;
    cerr << "Temp file: " << temp_timing_file << endl;

    TimeSet tests;
    quiet_prompt("Running " + boost::lexical_cast<string>(NUM_TESTS) +
                 " tests on " + PROGRAM_NAME);
    string command = timing_program + " " + PROGRAM_NAME + " "
                   + temp_timing_file;
    for (int i = 0; i < NUM_TESTS; ++i) {
        quiet_prompt("Running test set " + boost::lexical_cast<string>(i + 1) +
                     " of " + boost::lexical_cast<string>(NUM_TESTS));
        run_system_call(command, BE_VERBOSE);
        read_one_test(temp_timing_file, tests);
        fs::resize_file(temp_timing_file, 0);
    }

    if (OUTPUT_FILE_NAME == "") {
        print_results(tests, cout, OUTPUT_HEADER);
        fs::remove(temp_timing_file);
        return 0;
    }

    ofstream output;
    ifstream input;
    output.open(temp_timing_file.c_str());
    if (!output.is_open()) {
        cerr << "Unable to create temporary file" << endl;
        return 1;
    }
    input.open((OUTPUT_FILE_NAME).c_str());
    if (input.is_open()) {
        copy_until_sentinel(input, output, OUTPUT_SENTINEL);
    }
    print_results(tests, output, OUTPUT_HEADER);
    if (input.is_open()) {
        copy_after_sentinel(input, output);
    }
    fs::rename(temp_timing_file, OUTPUT_FILE_NAME);
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
    time_t current_time = time(NULL);
    OUTPUT_HEADER = "Tests run on " +
                  boost::lexical_cast<string>(ctime(&current_time));
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

