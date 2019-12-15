#include "all.h"

using namespace std;

template < typename array >
struct array_iterator {
    array & a;
    std::size_t i;

    array_iterator(array & a, std::size_t i)
        : a(a), i(i) {}

    typename array::refer
    operator *() {
        return a[i];
    }

    array_iterator & operator ++() {
        ++i;
        return *this;
    }

    array_iterator & operator ++(int) {
        array_iterator copy = *this;
        ++*this;
        return copy;
    }

    array_iterator & operator --() {
        --i;
        return *this;
    }

    array_iterator & operator --(int) {
        array_iterator copy = *this;
        --*this;
        return copy;
    }

    bool operator ==( array_iterator const & right ){
        return i == right.i;
    }

    bool operator !=( array_iterator const & right ){
        return i != right.i;
    }
};

template < typename T, std::size_t N >
struct Array {
    using refer = T &;
    using iterator = array_iterator<Array>;

    T storage[N];

    T& operator [] (std::size_t i) {
        return storage[i];
    }

    std::size_t len() const {
        return N;
    }

    void print() const {
        for ( std::size_t i = 0; i < N; i++) {
            cout << storage[i] << endl;
        }
    }

    T& front() {
        return storage[0];
    }
 
    T const & front() const {
        return storage[0];
    }

    T& back() {
        return storage[N - 1];
    }
 
    T const & back() const {
        return storage[N - 1];
    }

    iterator begin() {
        return iterator(*this, 0);
    }

    iterator end() {
        return iterator(*this, N);
    }
};


int main() {
    Array<int, 5> a = {1, 2, 3, 4, 5};
    cout << "array five len=" << a.len() << endl; 
    cout << "first element" << a.front() << endl; 
    cout << "last element" << a.back() << endl;
    a.print();

    auto iter = a.begin();
    cout << "iter " << *iter << endl;
    ++iter;
    cout << "iter " << *iter << endl;

    const Array<int, 3> b = {1, 2, 3 };
    cout << "array three const len=" << b.len() << endl;  
    cout << "first element" << b.front() << endl; 
    cout << "last element" << b.back() << endl;
    b.print();


    Array<int, 10> c = {1, 2, 3, 4, 55, 61, 71, 48, 90, 101};
    std::for_each(
        std::begin(c), 
        std::end(c), 
        [](auto x) { cout << x << endl;}
    );
}