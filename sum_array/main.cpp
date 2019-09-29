#include <iostream>

using namespace std;

template<class T> T summary(T arr[], int size, T def_val) {
    T sum = def_val;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << summary(arr, 10, 0) << endl;

    double arr2[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.9};
    cout << summary(arr2, 10, 0.0) << endl;

    // char arr3[] = {'a', 'b', 'c'};
    // char def = ' ';
    // cout << summary(arr3, 3, def) << endl;
}