#include <iostream>
#include <vector>
#include "sort.h"
using namespace std;

int main()
{
	vector<int> list;
	int current;
	cin >> current;
	while (!cin.eof()) {
		list.push_back(current);
		cin >> current;
    }

	list = sort(list);

	string divider = "";
	int end = list.size();
	for (int i = 0; i < end; ++i) {
		cout << divider << list[i];
		divider = " ";
	}
    cout << endl;
	return 0;
}
