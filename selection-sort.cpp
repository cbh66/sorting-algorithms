/*---------------------------------------------------------------------------*\
 *  selection-sort.cpp                                                       *
 *  Written By:  Colin B Hamilton, Tufts University                          *
 *  Last Modified: 2014-9-11                                                 *
 *  Description:                                                             *
 *    The selection sort algorithm takes a vector of ints and returns the    *
 *    sorted permutation of that vector.  It runs by:                        *
 *    1) Beginning with a sorted sub-array of size 0.                        *
 *    2) Finding the minimum value of the remaining, unsorted elements.      *
 *    3) Expanding the sorted sub-array by appending that value.             *
 *    4) Repeating until the sorted sub-array's size is that of the full     *
 *       array.                                                              *
 *  The name "selection sort" comes from the fact that at each step, we are  *
 *  selecting what the next element should be, and then placing it in the    *
 *  next slot.
\*---------------------------------------------------------------------------*/

#include "sort.h"

void swap(std::vector<int> &array, int first, int second)
{
	int temp = array[first];
	array[first] = array[second];
	array[second] = temp;
}

int index_of_min(std::vector<int> array, int start, int end)
{
	int current_min = start;
	for (int i = start + 1; i <= end; ++i) {
		if (array[i] < array[current_min]) current_min = i;
	}
	return current_min;
}

std::vector<int> sort(std::vector<int> list)
{
	int last = list.size() - 1;
	for (int i = 0; i <= last; ++i) {
		swap(list, i, index_of_min(list, i, last));
	}
	return list;
}

/*
STATS:
For input file data/random-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.431s    0m0.427s    0m0.438s     0.4320s
user    0m0.429s    0m0.424s    0m0.435s     0.4293s
sys     0m0.001s    0m0.002s    0m0.002s     0.0017s
For input file data/random-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m42.550s   0m44.521s   0m42.656s   43.2423s
user    0m42.512s   0m44.386s   0m42.614s   43.1707s
sys     0m0.036s    0m0.074s    0m0.039s     0.0497s
For input file data/random-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.007s    0m0.007s    0m0.007s     0.0070s
user    0m0.005s    0m0.005s    0m0.005s     0.0050s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/random-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.006s    0m0.007s    0m0.006s     0.0063s
user    0m0.005s    0m0.005s    0m0.005s     0.0050s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/random-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.006s    0m0.006s    0m0.006s     0.0060s
user    0m0.005s    0m0.005s    0m0.005s     0.0050s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.531s    0m0.525s    0m0.527s     0.5277s
user    0m0.529s    0m0.523s    0m0.524s     0.5253s
sys     0m0.002s    0m0.002s    0m0.002s     0.0020s
For input file data/reverse-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m44.118s   0m44.181s   0m45.228s   44.5090s
user    0m44.056s   0m44.130s   0m45.137s   44.4410s
sys     0m0.050s    0m0.045s    0m0.063s     0.0527s
For input file data/reverse-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.007s    0m0.007s    0m0.007s     0.0070s
user    0m0.006s    0m0.006s    0m0.005s     0.0057s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.007s    0m0.007s    0m0.006s     0.0067s
user    0m0.006s    0m0.005s    0m0.005s     0.0053s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.007s    0m0.007s    0m0.006s     0.0067s
user    0m0.006s    0m0.006s    0m0.005s     0.0057s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.434s    0m0.427s    0m0.427s     0.4293s
user    0m0.431s    0m0.424s    0m0.424s     0.4263s
sys     0m0.002s    0m0.002s    0m0.002s     0.0020s
For input file data/sorted-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m42.850s   0m42.467s   0m43.547s   42.9547s
user    0m42.799s   0m42.419s   0m43.459s   42.8923s
sys     0m0.043s    0m0.045s    0m0.060s     0.0493s
For input file data/sorted-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.007s    0m0.006s    0m0.006s     0.0063s
user    0m0.005s    0m0.005s    0m0.005s     0.0050s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.006s    0m0.006s    0m0.006s     0.0060s
user    0m0.005s    0m0.005s    0m0.005s     0.0050s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.006s    0m0.006s    0m0.006s     0.0060s
user    0m0.005s    0m0.005s    0m0.005s     0.0050s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s

*/
