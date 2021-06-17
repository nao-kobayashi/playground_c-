#ifndef SELECTION_SORT_DEF
#define SELECTION_SORT_DEF

#include <vector>
using namespace std;

class SelectionSort {
public:
    SelectionSort(vector<int>& numbers);
    void Sort();

private:
    vector<int>& numbers;
};

#endif