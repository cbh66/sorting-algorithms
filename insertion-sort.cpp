#include "sort.h"

void swap(std::vector<int> &array, int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

void insert(std::vector<int> &array, int index)
{
    for (int i = index - 1; i >= 0; --i) {
        if (array[i + 1] < array[i]) swap(array, i, i + 1);
        else return;
    }
}

std::vector<int> sort(std::vector<int> list)
{
    int last = list.size() - 1;
    for (int i = 1; i <= last; ++i) {
        insert(list, i);
    }
    return list;
}

/*
STATS:
For input file data/random-10-000-all.data:

real    0m11.443s
user    0m11.407s
sys     0m0.016s
For input file data/random-100-000-all.data:

real    20m21.573s
user    20m19.226s
sys     0m1.595s
For input file data/random-1000-all.data:

real    0m0.186s
user    0m0.146s
sys     0m0.002s
For input file data/random-1000-neg.data:

real    0m0.170s
user    0m0.126s
sys     0m0.002s
For input file data/random-1000-nonneg.data:

real    0m0.134s
user    0m0.115s
sys     0m0.002s
For input file data/reverse-10-000-all.data:

real    0m12.484s
user    0m12.451s
sys     0m0.019s


*/
