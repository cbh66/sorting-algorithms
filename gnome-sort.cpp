#include "sort.h"

void swap(std::vector<int> &array, int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

std::vector<int> sort(std::vector<int> list)
{
    int pos = 1;
    int size = list.size();
    while (pos < size) {
        if (list[pos - 1] <= list[pos]) {
            ++pos;
        } else {
            swap(list, pos - 1, pos);
            if (pos > 1) --pos;
        }
    }
    return list;
}

/*
STATS:
Timing input file data/random-10-000-all.data:

real    0m0.821s
user    0m0.790s
sys 0m0.002s
Timing input file data/random-100-000-all.data:

real    1m20.657s
user    1m20.570s
sys 0m0.041s
Timing input file data/random-1000-all.data:

real    0m0.375s
user    0m0.012s
sys 0m0.001s
Timing input file data/random-1000-neg.data:

real    0m0.012s
user    0m0.009s
sys 0m0.001s
Timing input file data/random-1000-nonneg.data:

real    0m0.026s
user    0m0.012s
sys 0m0.001s
Timing input file data/reverse-10-000-all.data:

real    0m1.636s
user    0m1.622s
sys 0m0.002s
Timing input file data/reverse-100-000-all.data:

real    2m39.630s
user    2m39.539s
sys 0m0.053s
Timing input file data/reverse-1000-all.data:

real    0m0.058s
user    0m0.023s
sys 0m0.001s
Timing input file data/reverse-1000-neg.data:

real    0m0.034s
user    0m0.020s
sys 0m0.001s
Timing input file data/reverse-1000-nonneg.data:

real    0m0.019s
user    0m0.017s
sys 0m0.001s
Timing input file data/sorted-10-000-all.data:

real    0m0.022s
user    0m0.007s
sys 0m0.001s
Timing input file data/sorted-100-000-all.data:

real    0m0.074s
user    0m0.055s
sys 0m0.002s
Timing input file data/sorted-1000-all.data:

real    0m0.010s
user    0m0.001s
sys 0m0.001s
Timing input file data/sorted-1000-neg.data:

real    0m0.021s
user    0m0.002s
sys 0m0.002s
Timing input file data/sorted-1000-nonneg.data:

real    0m0.015s
user    0m0.001s
sys 0m0.002s


*/
