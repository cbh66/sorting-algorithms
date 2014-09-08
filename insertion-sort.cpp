#include "sort.h"

void swap(std::vector<int> &array, int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

void insert(std::vector<int> &array, int index)
{
    int elem = array[index];
    /* Shifts all elements > elem up by one, leaves i pointing at elem's position. */
    int i;
    for (i = index; i > 0 && array[i - 1] > elem; --i) {
        array[i] = array[i - 1];
    }
    array[i] = elem;
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
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.667s    0m0.387s   0m0.309s      0.4543s
user    0m0.309s    0m0.383s   0m0.307s      0.3330s
sys     0m0.001s    0m0.002s   0m0.001s      0.0013s
For input file data/random-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m31.204s   0m30.991s   0m30.675s   30.9567s
user    0m31.166s   0m30.965s   0m30.660s   30.9303s
sys     0m0.023s    0m0.018s    0m0.012s     0.0177s
For input file data/random-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.005s    0m0.005s    0m0.006s     0.0053s
user    0m0.004s    0m0.004s    0m0.004s     0.0040s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/random-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.005s    0m0.005s    0m0.005s     0.0050s
user    0m0.004s    0m0.004s    0m0.004s     0.0040s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/random-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.006s    0m0.005s    0m0.005s     0.0050s
user    0m0.005s    0m0.004s    0m0.004s     0.0040s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.698s    0m0.617s    0m0.610s     0.6417s
user    0m0.694s    0m0.615s    0m0.609s     0.6393s
sys     0m0.002s    0m0.001s    0m0.001s     0.0017s
For input file data/reverse-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    1m2.374s    1m2.362s    1m1.395s    62.0437s
user    1m2.298s    1m2.290s    1m1.364s    61.9840s
sys     0m0.037s    0m0.046s    0m0.027s     0.0367s
For input file data/reverse-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.045s    0m0.008s    0m0.009s     0.0207s
user    0m0.011s    0m0.007s    0m0.007s     0.0083s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.011s    0m0.009s    0m0.008s     0.0093s
user    0m0.007s    0m0.007s    0m0.007s     0.0070s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/reverse-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.009s    0m0.009s    0m0.008s     0.0087s
user    0m0.007s    0m0.007s    0m0.007s     0.0070s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-10-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.023s    0m0.007s    0m0.006s     0.0120s
user    0m0.009s    0m0.005s    0m0.005s     0.0063s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-100-000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.090s    0m0.057s    0m0.056s     0.0677s
user    0m0.080s    0m0.054s    0m0.054s     0.0627s
sys     0m0.003s    0m0.002s    0m0.002s     0.0023s
For input file data/sorted-1000-all.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.023s    0m0.002s    0m0.002s     0.0090s
user    0m0.001s    0m0.001s    0m0.001s     0.0010s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-1000-neg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.010s    0m0.002s    0m0.002s     0.0047s
user    0m0.001s    0m0.001s    0m0.001s     0.0010s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s
For input file data/sorted-1000-nonneg.data:
        TRIAL 1     TRIAL 2     TRIAL 3     AVG
real    0m0.015s    0m0.002s    0m0.002s     0.0063s
user    0m0.001s    0m0.001s    0m0.001s     0.0010s
sys     0m0.001s    0m0.001s    0m0.001s     0.0010s

*/
