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

/* STATS:
Tests run on Sat Sep 13 01:29:17 2014
 Timing input file data/random-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.4230s        0.4350s        0.4330s        0.4460s        0.4700s      0.4414s
User:     0.4210s        0.4330s        0.4300s        0.4440s        0.4670s      0.4390s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/random-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:    44.7920s       44.1910s       44.1380s       44.0370s       44.3600s      44.3036s
User:    44.5890s       44.1150s       44.0310s       43.9400s       44.2580s      44.1866s
System:   0.1010s        0.0560s        0.0780s        0.0750s        0.0820s      0.0784s

 Timing input file data/random-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.0070s        0.0100s        0.0080s        0.0070s        0.0070s      0.0078s
User:     0.0050s        0.0080s        0.0060s        0.0050s        0.0050s      0.0058s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/random-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.0070s        0.0160s        0.0090s        0.0070s        0.0070s      0.0092s
User:     0.0050s        0.0080s        0.0060s        0.0060s        0.0050s      0.0060s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/random-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.0070s        0.0100s        0.0070s        0.0070s        0.0070s      0.0076s
User:     0.0050s        0.0070s        0.0050s        0.0050s        0.0050s      0.0054s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.5270s        0.7080s        0.5330s        0.5310s        0.5240s      0.5646s
User:     0.5260s        0.7010s        0.5300s        0.5300s        0.5220s      0.5618s
System:   0.0010s        0.0020s        0.0010s        0.0010s        0.0010s      0.0012s

 Timing input file data/reverse-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:    44.9860s       49.5290s       44.1280s       46.1600s       44.4040s      45.8414s
User:    44.8490s       49.3820s       44.0670s       46.0380s       44.3380s      45.7348s
System:   0.0510s        0.0710s        0.0560s        0.0890s        0.0590s      0.0652s

 Timing input file data/reverse-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.0090s        0.0070s        0.0070s        0.0070s        0.0070s      0.0074s
User:     0.0070s        0.0050s        0.0050s        0.0050s        0.0060s      0.0056s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.0070s        0.0070s        0.0070s        0.0070s        0.0070s      0.0070s
User:     0.0050s        0.0060s        0.0050s        0.0050s        0.0050s      0.0052s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.0090s        0.0070s        0.0070s        0.0070s        0.0070s      0.0074s
User:     0.0070s        0.0050s        0.0050s        0.0050s        0.0060s      0.0056s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.4240s        0.4240s        0.4240s        0.4520s        0.4330s      0.4314s
User:     0.4210s        0.4230s        0.4220s        0.4500s        0.4310s      0.4294s
System:   0.0020s        0.0010s        0.0010s        0.0010s        0.0010s      0.0012s

 Timing input file data/sorted-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:    42.5860s       43.9700s       44.1760s       44.1670s       42.3240s      43.4446s
User:    42.5400s       43.8210s       44.0710s       44.0660s       42.2740s      43.3544s
System:   0.0420s        0.0630s        0.0800s        0.0780s        0.0380s      0.0602s

 Timing input file data/sorted-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.0070s        0.0070s        0.0070s        0.0070s        0.0070s      0.0070s
User:     0.0060s        0.0050s        0.0050s        0.0050s        0.0050s      0.0052s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.0070s        0.0070s        0.0070s        0.0070s        0.0070s      0.0070s
User:     0.0060s        0.0050s        0.0050s        0.0050s        0.0050s      0.0052s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4        AVG
Real:     0.0070s        0.0070s        0.0070s        0.0070s        0.0060s      0.0068s
User:     0.0050s        0.0060s        0.0050s        0.0050s        0.0050s      0.0052s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s


Tests run on Sat Sep 13 01:10:27 2014
 Timing input file data/random-10-000-all.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.4250s      0.4250s      0.4220s      0.4490s      0.4240s      0.4290s
User:     0.4230s      0.4240s      0.4210s      0.4460s      0.4220s      0.4272s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s

 Timing input file data/random-100-000-all.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:    43.1720s      43.0690s      42.7150s      42.9600s      42.8580s      42.9548s
User:    43.1020s      43.0050s      42.6690s      42.9090s      42.8110s      42.8992s
System:   0.0650s      0.0500s      0.0440s      0.0470s      0.0410s      0.0494s

 Timing input file data/random-1000-all.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.0080s      0.0070s      0.0070s      0.0070s      0.0070s      0.0072s
User:     0.0060s      0.0050s      0.0050s      0.0050s      0.0050s      0.0052s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s

 Timing input file data/random-1000-neg.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.0070s      0.0070s      0.0070s      0.0070s      0.0070s      0.0070s
User:     0.0050s      0.0050s      0.0050s      0.0060s      0.0050s      0.0052s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s

 Timing input file data/random-1000-nonneg.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.0070s      0.0070s      0.0070s      0.0070s      0.0070s      0.0070s
User:     0.0050s      0.0050s      0.0050s      0.0050s      0.0050s      0.0050s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s

 Timing input file data/reverse-10-000-all.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.5260s      0.5140s      0.5220s      0.5310s      0.5260s      0.5238s
User:     0.5240s      0.5120s      0.5200s      0.5290s      0.5240s      0.5218s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s

 Timing input file data/reverse-100-000-all.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:    44.0470s      43.5660s      44.0410s      44.0230s      44.2700s      43.9894s
User:    43.9880s      43.5280s      43.9880s      43.9680s      44.2080s      43.9360s
System:   0.0560s      0.0350s      0.0490s      0.0520s      0.0550s      0.0494s

 Timing input file data/reverse-1000-all.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.0070s      0.0080s      0.0070s      0.0070s      0.0070s      0.0072s
User:     0.0050s      0.0060s      0.0060s      0.0050s      0.0050s      0.0054s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s

 Timing input file data/reverse-1000-neg.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.0070s      0.0070s      0.0070s      0.0070s      0.0070s      0.0070s
User:     0.0060s      0.0060s      0.0050s      0.0060s      0.0060s      0.0058s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s

 Timing input file data/reverse-1000-nonneg.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.0070s      0.0070s      0.0070s      0.0070s      0.0070s      0.0070s
User:     0.0060s      0.0060s      0.0050s      0.0050s      0.0060s      0.0056s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s

 Timing input file data/sorted-10-000-all.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.4270s      0.4180s      0.4360s      0.4240s      0.4410s      0.4292s
User:     0.4250s      0.4160s      0.4340s      0.4220s      0.4390s      0.4272s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0020s      0.0012s

 Timing input file data/sorted-100-000-all.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:    43.1690s     42.1960s     42.9770s     42.6750s     43.8770s     42.9788s
User:    43.0790s     42.1590s     42.9120s     42.6220s     43.7170s     42.8978s
System:   0.0840s      0.0360s      0.0520s      0.0490s      0.0600s      0.0562s

 Timing input file data/sorted-1000-all.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.0070s      0.0060s      0.0070s      0.0070s      0.0080s      0.0070s
User:     0.0050s      0.0050s      0.0050s      0.0050s      0.0060s      0.0052s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s

 Timing input file data/sorted-1000-neg.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.0070s      0.0070s      0.0090s      0.0070s      0.0080s      0.0076s
User:     0.0050s      0.0050s      0.0070s      0.0050s      0.0060s      0.0056s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s

 Timing input file data/sorted-1000-nonneg.data:
        TRIAL 0      TRIAL 1      TRIAL 2      TRIAL 3      TRIAL 4      AVG
Real:     0.0070s      0.0070s      0.0070s      0.0070s      0.0070s      0.0070s
User:     0.0050s      0.0050s      0.0050s      0.0050s      0.0050s      0.0050s
System:   0.0010s      0.0010s      0.0010s      0.0010s      0.0010s      0.0010s


*/

