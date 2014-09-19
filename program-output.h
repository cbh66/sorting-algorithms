/*---------------------------------------------------------------------------*\
 *  program_output.h                                                         *
 *  Written by: Colin Hamilton, Tufts University                             *
 *  Created:  2014-9-18                                                      *
 *  Defines a set of functions that deal with formatted printing.            *
\*---------------------------------------------------------------------------*/
#ifndef PROGRAM_OUTPUT_H_DEFINED
#define PROGRAM_OUTPUT_H_DEFINED
#include "timing-data.h"
#include <map>
#include <vector>
#include <fstream>
#include <string>

void print_results(const TimeSet &tests, std::ostream &output, std::string header);
void print_vector(const std::vector<double> &v, std::string seperator, std::ostream &output);
void copy_until_sentinel(std::ifstream &input, std::ofstream &output, std::string sentinel);
void copy_after_sentinel(std::ifstream &input, std::ofstream &output);

#endif
