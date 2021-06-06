#include "QuickSort.h"
#include <iostream>

//higher number of the first two different elements.
int QuickSort::pivot(int *arr, int low, int high) {
    int k = low + 1;
    //consider continuing same values.
    while (k <= high && arr[low] == arr[k]) {
        k++;
    }

    if (k > high) return -1;
    if (arr[low] >= arr[k]) return low;

    return k;
}

int QuickSort::partition(int *arr, int low, int high, int pivot) {
    int l = low, r = high;

    while (l <= r){
        while (l <= high && arr[l] < pivot) {
            l++;
        }

        while (r >= low && arr[r] >= pivot) {
            r--;
        }

        if (l > r) break;
        int tmp = arr[l];
        arr[l] = arr[r];
        arr[r] = tmp;
        l++;
        r--;
    }

    return l;
}

void QuickSort::Sort(vector<int> &numbers, int low, int high) {
    if (low < high) {
        int* arr = numbers.data();
        int p = pivot(arr, low, high);
        if ( p != -1) {
            int k = partition(arr, low, high, arr[p]);
            Sort(numbers, low, k - 1);
            Sort(numbers, k, high);
        }
    }
}