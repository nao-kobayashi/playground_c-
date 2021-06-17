#ifndef BUBBLE_SORT_DEF
#define BUBBLE_SORT_DEF

#include <vector>
using namespace std;

class BubbleSort {
public:
    BubbleSort(vector<int>& numbers);
    void Sort();

private:
    vector<int>& numbers;
};

#endif