#ifndef SORT_QUICKSORT_H
#define SORT_QUICKSORT_H

#include <vector>
using namespace std;

class QuickSort {
public:
    QuickSort(vector<int> &source);
    void Sort(int low, int high);

private:
    vector<int>& numbers;
    int partition(int arr[], int low, int high, int pivot);
    int pivot(int arr[], int low, int high);
};

#endif //SORT_QUICKSORT_H
