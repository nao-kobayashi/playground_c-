#ifndef SORT_QUICKSORT_H
#define SORT_QUICKSORT_H

#include <vector>
using namespace std;

class QuickSort {
public:
    static void Sort(vector<int>& numbers, int low, int high);

private:
    static int partition(int arr[], int low, int high, int pivot);
    static int pivot(int arr[], int low, int high);
};

#endif //SORT_QUICKSORT_H
