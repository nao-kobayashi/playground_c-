#ifndef SORT_MERGESORT_H
#define SORT_MERGESORT_H
#include <vector>
using namespace std;

class MergeSort {
public:
    MergeSort(vector<int>& numbers);
    void Sort(int left, int right);

private:
    vector<int>& numbers;
    void Merge(int left, int mid, int right);
};
#endif //SORT_MERGESORT_H
