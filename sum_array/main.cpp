#include <iostream>

using namespace std;

template<class T> T summary(const T arr[], const int size, T def_val = 0) {
    T sum = def_val;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

template<class T1, class T2> void copy_array(
    const T1 source[], 
    T2 destination[], 
    int size
) {
    for (int i = 0; i < size; i++) {
        destination[i] = static_cast<T2>(source[i]);
    }
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << summary(arr, 10) << endl;

    double arr2[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.9};
    cout << summary(arr2, 10) << endl;

    cout << summary(arr2, 10, 10.0) << endl;

    double arr_cp[10];
    copy_array(arr, arr_cp, 10);
    for (int i = 0; i < 10; i++) {
        cout << arr_cp[i] << " ";
    }
    cout  << endl;

    // char arr3[] = {'a', 'b', 'c'};
    // char def = ' ';
    // cout << summary(arr3, 3, def) << endl;
}