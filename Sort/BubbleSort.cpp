#include "BubbleSort.h"

using namespace std;

BubbleSort::BubbleSort(vector<int> &numbers): numbers(numbers) {}

void BubbleSort::Sort() {
    int n = numbers.size();
    short swap_check = 1;
    for (int i = 0; (i < n) && (swap_check == 1); i++) {
        swap_check = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (numbers[j] > numbers[j + 1]) {
                swap_check = 1;
                swap(numbers[j], numbers[j + 1]);
            }
        }
    }
}