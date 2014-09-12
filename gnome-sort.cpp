/*---------------------------------------------------------------------------*\
 *  gnome-sort.cpp                                                           *
 *  Written By:  Colin B Hamilton, Tufts University                          *
 *  Last Modified: 2014-9-11                                                 *
 *  Description:                                                             *
 *    The gnome sort algorithm takes a vector of ints and returns the        *
 *    sorted permutation of that vector.  It runs by:                        *
 *    1) Stepping through the array, looking for adjacent elements in the    *
 *       wrong order.                                                        *
 *    2) When found, taking the smaller of the two elements all the way back *
 *       to a position where it is in the correct order.                     *
 *    3) Continuing the search until the end of the array is reached.        *
 *  The name "gnome sort" apparently comes from the visualization of gnomes  *
 *  moving flower pots.  When they find one in the wrong position, they      *
 *  carry it back to the right position.  It can be thought of either as     *
 *    1) A varient of bubble sort, where the algorithm steps backwards after *
 *       every swap, thus dealing with the slowness of "turtles" - those     *
 *       elements near the end that should be near the front, which move     *
 *       very slowly in bubble sort;  OR                                     *
 *    2) A varient of insertion sort, where the keeping of a sorted          *
 *       sub-array and expanding it is only implicit.                        *
\*---------------------------------------------------------------------------*/

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
    int last = 0;
    int size = list.size();
    while (pos < size) {
        if (list[pos - 1] <= list[pos]) {
            if (last != 0) {
                pos = last;
                last = 0;
            }
            ++pos;
        } else {
            swap(list, pos - 1, pos);
            if (pos > 1) {
                if (last == 0) last = pos;
                --pos;
            }
        }
    }
    return list;
}

/*
STATS:
For input file data/random-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.584s    0m0.613s    0m0.597s     0.5980s
user    0m0.582s    0m0.582s    0m0.594s     0.5860s
sys     0m0.001s    0m0.002s    0m0.002s     0.0017s
For input file data/random-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m58.916s   0m58.828s   0m58.348s   58.6973s
user    0m58.884s   0m58.754s   0m58.315s   58.6510s
sys     0m0.025s    0m0.027s    0m0.030s     0.0273s
For input file data/random-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.009s    0m0.037s    0m0.008s     0.0180s
user    0m0.007s    0m0.007s    0m0.007s     0.0070s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/random-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.008s    0m0.015s    0m0.008s     0.0103s
user    0m0.007s    0m0.007s    0m0.007s     0.0070s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/random-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.009s    0m0.024s    0m0.008s     0.0137s
user    0m0.007s    0m0.008s    0m0.007s     0.0073s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m1.177s    0m1.194s    0m1.176s     1.1823s
user    0m1.175s    0m1.175s    0m1.174s     1.1747s
sys     0m0.001s    0m0.002s    0m0.001s     0.0013s
For input file data/reverse-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    1m57.752s   1m56.376s   1m57.019s  117.0490s
user    1m57.681s   1m56.277s   1m56.953s  116.9703s
sys     0m0.049s    0m0.050s    0m0.060s     0.0530s
For input file data/reverse-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.015s    0m0.053s    0m0.014s     0.0273s
user    0m0.013s    0m0.017s    0m0.013s     0.0143s
sys     0m0.001s    0m0.002s    0m0.001s     0.0013s
For input file data/reverse-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.014s    0m0.024s    0m0.014s     0.0173s
user    0m0.013s    0m0.015s    0m0.013s     0.0137s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.016s    0m0.015s    0m0.014s     0.0150s
user    0m0.015s    0m0.013s    0m0.013s     0.0137s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.077s    0m0.018s    0m0.007s     0.0340s
user    0m0.007s    0m0.007s    0m0.005s     0.0063s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.057s    0m0.081s    0m0.059s     0.0657s
user    0m0.055s    0m0.061s    0m0.057s     0.0577s
sys     0m0.002s    0m0.002s    0m0.002s     0.0020s
For input file data/sorted-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.002s    0m0.014s    0m0.002s     0.0060s
user    0m0.001s    0m0.001s    0m0.001s     0.0010s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.002s    0m0.010s    0m0.002s     0.0047s
user    0m0.001s    0m0.001s    0m0.001s     0.0010s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.002s    0m0.015s    0m0.002s     0.0063s
user    0m0.001s    0m0.001s    0m0.001s     0.0010s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s


*/
