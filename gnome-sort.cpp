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

/* STATS:
Tests run on Sat Sep 13 12:20:32 2014
 Timing input file data/random-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.6280s        0.5900s        0.5830s        0.5880s        0.5820s      0.5942s
User:     0.5830s        0.5890s        0.5810s        0.5860s        0.5800s      0.5838s
System:   0.0020s        0.0010s        0.0010s        0.0010s        0.0010s      0.0012s

 Timing input file data/random-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:    57.9620s       57.9510s       57.6810s       57.9880s       58.0060s     57.9176s
User:    57.9430s       57.9310s       57.6670s       57.9660s       57.9840s     57.8982s
System:   0.0170s        0.0170s        0.0140s        0.0190s        0.0190s      0.0172s

 Timing input file data/random-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0080s        0.0080s        0.0080s        0.0080s        0.0080s      0.0080s
User:     0.0070s        0.0070s        0.0070s        0.0070s        0.0070s      0.0070s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/random-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0080s        0.0080s        0.0080s        0.0090s        0.0080s      0.0082s
User:     0.0070s        0.0070s        0.0070s        0.0070s        0.0070s      0.0070s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/random-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0080s        0.0090s        0.0080s        0.0100s        0.0080s      0.0086s
User:     0.0070s        0.0070s        0.0070s        0.0080s        0.0070s      0.0072s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     1.1620s        1.1640s        1.1720s        1.1670s        1.1620s      1.1654s
User:     1.1600s        1.1630s        1.1700s        1.1650s        1.1600s      1.1636s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:   115.6730s      116.5790s      116.9230s      116.2930s      115.7350s    116.2406s
User:   115.6400s      116.5230s      116.8470s      116.2430s      115.6990s    116.1904s
System:   0.0310s        0.0470s        0.0500s        0.0390s        0.0300s      0.0394s

 Timing input file data/reverse-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0140s        0.0150s        0.0140s        0.0150s        0.0140s      0.0144s
User:     0.0130s        0.0130s        0.0130s        0.0130s        0.0130s      0.0130s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0140s        0.0140s        0.0140s        0.0140s        0.0140s      0.0140s
User:     0.0130s        0.0120s        0.0120s        0.0130s        0.0130s      0.0126s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0140s        0.0140s        0.0140s        0.0140s        0.0140s      0.0140s
User:     0.0130s        0.0120s        0.0120s        0.0130s        0.0130s      0.0126s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0060s        0.0070s        0.0070s        0.0060s        0.0060s      0.0064s
User:     0.0050s        0.0050s        0.0060s        0.0050s        0.0050s      0.0052s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0560s        0.0550s        0.0550s        0.0560s        0.0550s      0.0554s
User:     0.0540s        0.0530s        0.0530s        0.0540s        0.0530s      0.0534s
System:   0.0010s        0.0020s        0.0010s        0.0010s        0.0010s      0.0012s

 Timing input file data/sorted-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0020s        0.0020s        0.0020s        0.0020s        0.0020s      0.0020s
User:     0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0020s        0.0020s        0.0020s        0.0020s        0.0020s      0.0020s
User:     0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0020s        0.0020s        0.0020s        0.0020s        0.0020s      0.0020s
User:     0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s


*/
