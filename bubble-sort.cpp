/*---------------------------------------------------------------------------*\
 *  bubble-sort.cpp                                                          *
 *  Written By:  Colin B Hamilton, Tufts University                          *
 *  Last Modified: 2014-9-11                                                 *
 *  Description:                                                             *
 *    The bubble sort algorithm takes a vector of ints and returns the       *
 *    sorted permutation of that vector.  It runs by:                        *
 *    1) Stepping through the array, looking for adjacent elements in the    *
 *       wrong order.                                                        *
 *    2) Swapping those elements, when found.                                *
 *    3) Repeating until it steps through the array without finding any      *
 *       out-of-order elements.                                              *
 *  The name "bubble sort" comes from the idea that the algorithm moves      *
 *  elements slightly closer to the right positions each time, like          *
 *  they are "bubbling" into the correct positions, like bubbles rising to   *
 *  the surface.  Note, however, that large elements move fast; elements get *
 *  pushed very quickly to the end of the array, but it takes quite some     *
 *  time to move elements to the front if they were originally toward the    *
 *  end.  The former elements are known as "rabbits," for their speed, while *
 *  the latter are known as "turtles."                                       *
\*---------------------------------------------------------------------------*/

#include "sort.h"

void swap(std::vector<int> &array, int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

int bubble(std::vector<int> &list, int size_unsorted)
{
    int last_element_swapped = 1;
    for (int i = 1; i < size_unsorted; ++i) {
        if (list[i - 1] > list[i]) {
            swap(list, i - 1, i);
            last_element_swapped = i;
        }
    }
    return last_element_swapped;
}

std::vector<int> sort(std::vector<int> list)
{
    int len = list.size();
    while (len > 1) {
        len = bubble(list, len);
    }
    return list;
}

/*
STATS:
For input file data/random-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m1.037s    0m1.056s    0m1.017s     1.0367s
user    0m1.026s    0m1.021s    0m1.015s     1.0207s
sys     0m0.002s    0m0.002s    0m0.001s     0.0017s
For input file data/random-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    1m47.155s   1m42.294s   1m42.325s  103.9247s
user    1m46.867s   1m42.196s   1m42.245s  103.7693s
sys     0m0.108s    0m0.058s    0m0.051s     0.0723s
For input file data/random-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.051s    0m0.050s    0m0.013s     0.0380s
user    0m0.013s    0m0.014s    0m0.011s     0.0127s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/random-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.027s    0m0.023s    0m0.012s     0.0207s
user    0m0.014s    0m0.011s    0m0.011s     0.0120s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/random-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.020s    0m0.025s    0m0.014s     0.0197s
user    0m0.011s    0m0.014s    0m0.013s     0.0127s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m1.335s    0m1.281s    0m1.263s     1.2930s
user    0m1.318s    0m1.268s    0m1.261s     1.2823s
sys     0m0.003s    0m0.002s    0m0.001s     0.0020s
For input file data/reverse-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    2m14.256s   2m6.025s    2m6.450s   128.9103s
user    2m13.914s   2m5.906s    2m6.335s   128.7183s
sys     0m0.077s    0m0.046s    0m0.069s     0.0640s
For input file data/reverse-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.372s    0m0.046s    0m0.016s     0.1447s
user    0m0.016s    0m0.019s    0m0.014s     0.0490s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.026s    0m0.021s    0m0.017s     0.0213s
user    0m0.016s    0m0.013s    0m0.016s     0.0150s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.017s    0m0.016s    0m0.018s     0.0170s
user    0m0.015s    0m0.014s    0m0.016s     0.0150s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.016s    0m0.020s    0m0.007s     0.0143s
user    0m0.007s    0m0.007s    0m0.005s     0.0063s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.078s    0m0.076s    0m0.058s     0.0707s
user    0m0.059s    0m0.056s    0m0.056s     0.0570s
sys     0m0.002s    0m0.003s    0m0.002s     0.0023s
For input file data/sorted-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.017s    0m0.019s    0m0.002s     0.0127s
user    0m0.001s    0m0.001s    0m0.001s     0.0010s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.010s    0m0.010s    0m0.002s     0.0073s
user    0m0.002s    0m0.002s    0m0.001s     0.0017s
sys     0m0.002s    0m0.002s    0m0.001s     0.0017s
For input file data/sorted-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.015s    0m0.015s    0m0.002s     0.0107s
user    0m0.001s    0m0.002s    0m0.001s     0.0013s
sys     0m0.001s    0m0.002s    0m0.001s     0.0013s


*/
