#include "sort.h"

void swap(std::vector<int> &array, int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

bool bubble(std::vector<int> &list)
{
    bool made_a_swap = false;
    int len = list.size();
    for (int i = 1; i < len; ++i) {
        if (list[i - 1] > list[i]) {
            swap(list, i - 1, i);
            made_a_swap = true;
        }
    }
    return made_a_swap;
}

std::vector<int> sort(std::vector<int> list)
{
    while (bubble(list)) {}
    return list;
}
