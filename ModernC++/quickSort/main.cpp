#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template<class RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
    auto pivot = *first;
    auto i = first + 1;
    auto j = last - 1;

    //cout << "pivot: " << pivot << " first: " << *i << " last: " << *j << endl;
    while (i <= j) {
        while (i <= j && *i <= pivot)  {
            i++;
        }
        while (i <= j && *j > pivot) {
            j--;
        }
        if (i < j) std::iter_swap(i, j);
    }
//    cout << *(i-1) << " " << *first << endl;
    iter_swap(i - 1, first);
//    cout << *(i-1) << " " << *first << endl;
    return i - 1;
}

template <class RandomIt>
void quick_sort(RandomIt first, RandomIt last) {
    if (first < last ) {
        auto p = partition(first, last);
//        cout << "p is " << *p << endl;
        quick_sort(first, p);
        quick_sort(p + 1, last);
    }
}

template<typename T>
void display(const vector<T> &v) {
    for (auto n: v) {
        cout << n << " ";
    }
    cout << endl;
}

template<class RandomIt, class Compare>
RandomIt partition_with_comp(RandomIt first, RandomIt last, Compare comp) {
    auto pivot = *first;
    auto i = first + 1;
    auto j = last - 1;

    while (i <= j) {
        while (i <= j && comp(*i, pivot))  {
            i++;
        }
        while (i <= j && !comp(*j, pivot)) {
            j--;
        }
        if (i < j) std::iter_swap(i, j);
    }
    iter_swap(i - 1, first);
    return i - 1;
}

template <class RandomIt, class Compare>
void quick_sort(RandomIt first, RandomIt last, Compare comp) {
    if (first < last ) {
        auto p = partition_with_comp(first, last, comp);
        quick_sort(first, p, comp);
        quick_sort(p + 1, last, comp);
    }
}

void sort_normal() {
    vector<int> v {1, 5, 3, 8, 6, 2, 9, 7, 4};
    quick_sort(begin(v), end(v));
    display(v);

    vector<int> v2 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    quick_sort(begin(v2), end(v2));
    display(v2);

    vector<int> v3 {9, 8, 7, 6, 5, 4, 3, 2, 1 };
    quick_sort(begin(v3), end(v3));
    display(v3);
}

void sort_greater() {
    vector<int> v {1, 5, 3, 8, 6, 2, 9, 7, 4};
    quick_sort(begin(v), end(v), greater_equal<>());
    display(v);

    vector<int> v2 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    quick_sort(begin(v2), end(v2), greater_equal<>());
    display(v2);

    vector<int> v3 {9, 8, 7, 6, 5, 4, 3, 2, 1 };
    quick_sort(begin(v3), end(v3), greater_equal<>());
    display(v3);
}

void sort_less() {
    vector<int> v {1, 5, 3, 8, 6, 2, 9, 7, 4};
    quick_sort(begin(v), end(v), less_equal<>());
    display(v);

    vector<int> v2 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    quick_sort(begin(v2), end(v2), less_equal<>());
    display(v2);

    vector<int> v3 {9, 8, 7, 6, 5, 4, 3, 2, 1 };
    quick_sort(begin(v3), end(v3), less_equal<>());
    display(v3);
}

int main() {
    cout << "normal calling" << endl;
    sort_normal();

    cout << "with greater function calling" << endl;
    sort_greater();

    cout << "with less function calling" << endl;
    sort_less();

    return 0;
}
