#include <iostream>
#include <vector>

using namespace std;

template <class T, size_t R, size_t C>
class array2d {
    typedef T value_type;
    typedef value_type* iterator;
    typedef value_type const* const_iterator;
    vector<T> arr;
public:
    array2d(): arr(R * C) {}
    explicit array2d(initializer_list<T> list): arr(list) {}
    constexpr T* data() noexcept {return arr.data();}
    constexpr T const *data() const noexcept {return arr.data();}

    constexpr T& at(const size_t r, const size_t c) {
        return arr.at(r*C + c);
    }

    constexpr const T &at(const size_t r, const size_t c) const {
        return arr.at(r*C + c);
    }

    constexpr T& operator() (const size_t r, const size_t c) {
        return arr[r*C + c];
    }

    constexpr const T &operator() (const size_t r, const size_t c) const {
        return arr[r*C + c];
    }

    constexpr bool empty() const noexcept { return R == 0 || C == 0; }

    constexpr size_t size(int const rank) const {
        if (rank == 1) return R;
        else if (rank == 2) return C;

        throw out_of_range("Rank is out of range.");
    }

    void fill(const T &value) {
        std::fill(std::begin(arr), std::end(arr), value);
    }

    void swap(array2d &other) noexcept { arr.swap(other.arr); }

    const_iterator begin() const { return arr.data(); }
    const_iterator end() const { return arr.data() + arr.size(); }
    iterator begin() { return arr.data(); }
    iterator end() { return arr.data() + arr.size(); }
};

int main() {
    array2d<int, 2, 3> a {1, 2, 3, 4, 5, 6};
    for (size_t i = 0; i < a.size(1); i++) {
        for (size_t j = 0; j < a.size(2); j++) {
            a(i, j) *= 2;
        }
    }

    copy(cbegin(a), cend(a), ostream_iterator<int>(cout, " "));
    cout << endl;

    array2d<int, 2, 3> b;
    b.fill(1);
    copy(cbegin(b), cend(b), ostream_iterator<int>(cout, " "));
    cout << endl;

    a.swap(b);
    copy(cbegin(a), cend(a), ostream_iterator<int>(cout, " "));
    cout << endl;
    copy(cbegin(b), cend(b), ostream_iterator<int>(cout, " "));
    cout << endl;

    array2d<int, 2, 3> c(move(b));
//    copy(cbegin(b), cend(b), ostream_iterator<int>(cout, " "));
//    cout << endl;
    copy(cbegin(c), cend(c), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
