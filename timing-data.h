/*---------------------------------------------------------------------------*\
 *  timing-data.h                                                            *
 *  Written by: Colin Hamilton, Tufts University                             *
 *  Created:  2014-9-18                                                      *
 *  Defines a struct for storing the data of timing tests, and a function    *
 *    for running individual sets of tests.                                  *
\*---------------------------------------------------------------------------*/
#ifndef TIMING_DATA_H_INCLUDED
#define TIMING_DATA_H_INCLUDED
#include <vector>
#include <map>
#include <string>
/*  Holds the data for a single test run several times.
 *  Each vector should be the same length.
 */
struct TimingData {
    std::string test_name;
    std::vector<double> clock_time;
    std::vector<double> user_time;
    std::vector<double> system_time;
};
typedef std::map<std::string, TimingData> TimeSet;

void read_one_test(std::string file_name, TimeSet &tests);

#endif
