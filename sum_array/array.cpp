#include <stdio.h>
#include <iostream>
using namespace std;

// double sum(double array[], int size) {
double sum(double* array, int size) {
    double result = 0.0;
    int i = 0;

    for (i = 0; i < size; i++) {
        result += array[i];
    }

    return result;
}

int main(void) {
    double arr[] = {1.0, 12.2, 3.5};

    cout << sum(arr, 3) << endl;
}