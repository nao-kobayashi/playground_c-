#include "SelectionSort.h"

using namespace std;

/*void SelectionSort(vector<int>* numbers) {
    int *arr = numbers->data();
    for (int i = 0; i < numbers->size(); i++) {
        for (int j = i + 1; j < numbers->size();j++) {
            if (arr[j] < arr[i]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}*/

SelectionSort::SelectionSort(vector<int> &numbers): numbers(numbers) {}

//call by reference is more secure than call by pointer.
void SelectionSort::Sort() {
    int *arr = numbers.data();
    for (int i = 0; i < numbers.size(); i++) {
        for (int j = i + 1; j < numbers.size();j++) {
            if (arr[j] < arr[i]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}