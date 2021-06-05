#ifndef SORT_MERGESORT_H
#define SORT_MERGESORT_H
#include <vector>
using namespace std;

class MergeSort {
public:
    static void Sort(vector<int>& numbers, int left, int right);

private:
    static void Merge(int arr[], int left, int mid, int right);
};
#endif //SORT_MERGESORT_H
