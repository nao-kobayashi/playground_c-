#include <iostream>
#include <vector>

using namespace std;

struct Book {
    int bookId;
    string title;
    string auther;
};

template<typename T, typename A, typename F,
        typename R = typename decay<typename result_of<
                typename decay<F>::type&(
                typename vector<T, A>::const_reference)>::type>::type>
vector<R> select(const vector<T, A> &c, F&& f) {
    vector<R> v;
    transform(cbegin(c), cend(c), back_inserter(v), forward<F>(f));
    return v;
}

int main() {
    vector<Book> books {
            {101, "The C++ Programing Language", "Bjarne Stroustrup"},
            {203, "Effective Modern C++", "Scott Meyers"},
            {404, "The Modern C++ Programing Cookbook", "Marius Bancila"}
    };

    auto titles = select(books, [](const Book &b){ return b.title; });
    for(auto title : titles) {
        cout << title << endl;
    }

    return 0;
}
