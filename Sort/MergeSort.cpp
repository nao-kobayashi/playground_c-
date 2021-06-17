#include "MergeSort.h"

MergeSort::MergeSort(vector<int> &numbers): numbers(numbers) {}

void MergeSort::Merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = numbers[left + i];
    }

    for (int i = 0; i < n2; i++) {
        R[i] = numbers[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            numbers[k] = L[i];
            i++;
        } else {
            numbers[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        numbers[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        numbers[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort::Sort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSort::Sort(left, mid);
        MergeSort::Sort(mid + 1, right);
        MergeSort::Merge(left, mid, right);
    }
}