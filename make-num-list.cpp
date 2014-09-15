#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void init_random();
void write_sorted_nums(int min, int max, int amt, ostream &file);
void write_rev_sorted_nums(int min, int max, int amt, ostream &file);
void write_random_nums(int min, int max, int amt, ostream &file);

int main(int argc, char *argv[])
{
	string sort = "-s", rev_sort = "-b", random = "-r", max_opt = "-max", min_opt = "-min", amt_opt = "-amt";
	string file_name = "";
	int amt = 10, min = 0, max = 0;
	int type = 0;   // 0 for random, 1 for sorted, -1 for reverse sorted
	ofstream user_file;
	streambuf *buf = NULL;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (sort == argv[i]) {
				type = 1;
			} else if (rev_sort == argv[i]) {
				type = -1;
			} else if (random == argv[i]) {
				type = 0;
			} else if (max_opt == argv[i]) {
				if (i >= argc - 1 || (max = atoi(argv[++i])) == 0) {
					cerr << "Please provide a number after " << max_opt << " (leave the option out to mean 0)" << endl;
					return 1;
				}

			} else if (min_opt == argv[i]) {
				if (i >= argc - 1 || (min = atoi(argv[++i])) == 0) {
					cerr << "Please provide a number after " << min_opt << " (leave the option out to mean 0)" << endl;
					return 1;
				}
			} else if (amt_opt == argv[i]) {
				if (i >= argc - 1 || (amt = atoi(argv[++i])) <= 0) {
					cerr << "Please provide a positive number after " << amt_opt << endl;
					return 1;
				}
			} else {
				cerr << "Unknown option " << argv[i] << endl;
			}
		} else {
			file_name = argv[i];
		}
	}
	if (max < min) {
		cerr << "Your max of " << max << " is smaller than your min of " << min << "!" << endl;
		return 1;
	}

	cerr << "Writing " << amt << " ";
	if (type < 0) {
		cerr << "reverse sorted";
	} else if (type > 0) {
		cerr << "sorted";
	} else {
		cerr << "random";
	}
	if (min != 0 || max != 0) {
		cerr << " numbers between " << min << " and " << max << " to ";
	} else {
		min = -amt;
		max = amt;
		cerr << " numbers between default min of " << min << " and default max of "<< max << " to ";
	}
	if (file_name == "") {
		cerr << "standard output" << endl;
		buf = cout.rdbuf();
	} else {
		cerr << "file " << file_name << endl;
		user_file.open(file_name.c_str());
		if (!user_file.is_open()) {
			cerr << "But there was an error opening the file.  Aborting." << endl;
			return 1;
		}
		buf = user_file.rdbuf();
	}
	ostream output_file(buf);

	init_random();

	if (type < 0) {
		write_rev_sorted_nums(min, max, amt, output_file);
	} else if (type > 0) {
		write_sorted_nums(min, max, amt, output_file);
	} else {
		write_random_nums(min, max, amt, output_file);
	}
	output_file << endl;
	return 0;
}


void init_random()
{
	time_t now = time(NULL);
	tm *time_struct = gmtime(&now);
	int num_seed = 0;
	num_seed = (time_struct->tm_min + time_struct->tm_sec + 2)
			* (time_struct->tm_year - time_struct->tm_mday + time_struct->tm_sec + 13)
			- time_struct->tm_yday + 17;
	srand(num_seed);
}

void write_sorted_nums(int min, int max, int amt, ostream &file)
{
	string divider = "";
	int gradient = 2 * (max - min + 1) / amt;
	if (gradient < 2) gradient = 2;             // Because mod doesn't work well with 1.
	int current_num = min + rand() % gradient;
	for (int i = 0; i < amt; i++) {
		current_num += rand() % gradient;
		file << divider << (current_num < max ? current_num : current_num = max - (amt - i - 1));
		divider = " ";
	}
}

void write_rev_sorted_nums(int min, int max, int amt, ostream &file)
{
	string divider = "";
	int gradient = 2 * (max - min + 1) / (amt);
	if (gradient < 2) gradient = 2;
	int current_num = max - rand() % gradient;
	for (int i = 0; i < amt; i++) {
		current_num -= rand() % gradient;
		file << divider << (current_num > min ? current_num : current_num = min + (amt - i - 1));
		divider = " ";
	}
}

void write_random_nums(int min, int max, int amt, ostream &file)
{
	string divider = "";
	int region_size = max - min + 1;
	for (int i = 0; i < amt; i++) {
		file << divider << min + (rand() % region_size);
		divider = " ";
	}
}
