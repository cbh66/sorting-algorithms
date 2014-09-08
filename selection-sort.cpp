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
For input file data/random-100-000-all.data:
		TRIAL 1		TRIAL 2		TRIAL 3
real	0m42.550s	0m44.521s	0m42.656s
user	0m42.512s	0m44.386s	0m42.614s
sys		0m0.036s	0m0.074s	0m0.039s
For input file data/random-1000-all.data:
		TRIAL 1 	TRIAL 2		TRIAL 3
real	0m0.007s	0m0.007s	0m0.007s
user	0m0.005s	0m0.005s	0m0.005s
sys		0m0.001s	0m0.001s	0m0.001s
For input file data/random-1000-neg.data:
		TRIAL 1 	TRIAL 2		TRIAL 3
real	0m0.006s	0m0.007s	0m0.006s
user	0m0.005s	0m0.005s	0m0.005s
sys		0m0.001s	0m0.001s	0m0.001s
For input file data/random-1000-nonneg.data:
		TRIAL 1 	TRIAL 2		TRIAL 3
real	0m0.006s	0m0.006s	0m0.006s
user	0m0.005s	0m0.005s	0m0.005s
sys		0m0.001s	0m0.001s	0m0.001s
For input file data/reverse-100-000-all.data:
		TRIAL 1 	TRIAL 2		TRIAL 3
real	0m44.118s	0m44.181s	0m45.228s
user	0m44.056s	0m44.130s	0m45.137s
sys		0m0.050s	0m0.045s	0m0.063s
For input file data/reverse-1000-all.data:
		TRIAL 1 	TRIAL 2 	TRIAL 3
real	0m0.007s	0m0.007s	0m0.007s
user	0m0.006s	0m0.006s	0m0.005s
sys		0m0.001s	0m0.001s	0m0.001s
For input file data/reverse-1000-neg.data:
		TRIAL 1 	TRIAL 2 	TRIAL 3
real	0m0.007s	0m0.007s	0m0.006s
user	0m0.006s	0m0.005s	0m0.005s
sys		0m0.001s	0m0.001s	0m0.001s
For input file data/reverse-1000-nonneg.data:
		TRIAL 1 	TRIAL 2 	TRIAL 3
real	0m0.007s	0m0.007s	0m0.006s
user	0m0.006s	0m0.006s	0m0.005s
sys		0m0.001s	0m0.001s	0m0.001s
For input file data/sorted-100-000-all.data:
		TRIAL 1 	TRIAL 2 	TRIAL 3
real	0m42.850s	0m42.467s	0m43.547s
user	0m42.799s	0m42.419s	0m43.459s
sys		0m0.043s	0m0.045s	0m0.060s
For input file data/sorted-1000-all.data:
		TRIAL 1 	TRIAL 2 	TRIAL 3
real	0m0.007s	0m0.006s	0m0.006s
user	0m0.005s	0m0.005s	0m0.005s
sys		0m0.001s	0m0.001s	0m0.001s
For input file data/sorted-1000-neg.data:
		TRIAL 1 	TRIAL 2 	TRIAL 3
real	0m0.006s	0m0.006s	0m0.006s
user	0m0.005s	0m0.005s	0m0.005s
sys		0m0.001s	0m0.001s	0m0.001s
For input file data/sorted-1000-nonneg.data:
		TRIAL 1 	TRIAL 2 	TRIAL 3
real	0m0.006s	0m0.006s	0m0.006s
user	0m0.005s	0m0.005s	0m0.005s
sys		0m0.001s	0m0.001s	0m0.001s

*/
