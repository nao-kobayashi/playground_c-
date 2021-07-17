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
    cout << *(i-1) << " " << *first << endl;
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

int main() {
    vector<int> v {1, 5, 3, 8, 6, 2, 9, 7, 4};
    quick_sort(begin(v), end(v));

    for (auto n: v) {
        cout << n << " ";
    }

    return 0;
}
