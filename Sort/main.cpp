#include <iostream>
#include <vector>
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"
using namespace std;

#define BUBBLE_SORT 1
#define SELECTION_SORT 2
#define MERGE_SORT 3

//#define DEBUG

int main() {
#ifndef DEBUG
    int method;
    cout << "Select Sort Method" << endl;
    cout << BUBBLE_SORT << ": Bubble Sort" << endl;
    cout << SELECTION_SORT << ": Selection Sort" << endl;
    cout << MERGE_SORT << ": Merge Sort" << endl;
    cin >> method;

    int n;
    cout << "Enter the amount of numbers to sort:";
    cin >> n;
    cout << "Enter " << n << " numbers:";

    int num;
    vector<int> numbers;
    for (int i = 0; i < n; i++) {
        cin >> num;
        numbers.push_back(num);
    }
#else
    int method = 3;
    int n = 10;
    vector<int> numbers;
    for (auto i = n; i > 0; i--) {
        numbers.push_back(i);
    }
#endif

    switch (method) {
        case BUBBLE_SORT: {
            BubbleSort::Sort(numbers);
            break;
        }
        case SELECTION_SORT: {
            SelectionSort::Sort(numbers);
            break;
        }
        case MERGE_SORT: {
            MergeSort::Sort(numbers, 0, numbers.size() - 1);
            break;
        }

    }

    cout << "Sorted Array:";
    for (auto ans: numbers) {
        cout << ans << " ";
    }
    cout << endl;

    return 0;
}

