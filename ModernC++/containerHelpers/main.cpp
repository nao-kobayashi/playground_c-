#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<typename C, typename... Args>
void push_back(C& c, Args&&... args) {
    (c.push_back(args), ...);
}

template<class C, class T>
bool contains(const C &c, const T &value) {
    return cend(c) != find(cbegin(c), cend(c), value);
}

template<class C, class... T>
bool contains_any(const C &c, T &&... value) {
    return (... || contains(c, value));
}

template<class C, class... T>
bool contains_all(const C &c, T &&... value) {
    return (... && contains(c, value));
}

template<class C, class... T>
bool contains_none(const C &c, T &&... value) {
    return !contains_any(c, std::forward<T>(value)...);
}

int main() {
    vector<int> v;
    push_back(v, 21, 2, 3, 4);
    cout << "container values ";
    copy(cbegin(v), cend(v), ostream_iterator<int>(cout, " "));
    cout << endl;

    list<int> l;
    push_back(l, 1,2,3,4);

    for (int i = 0; i < 6; i++) {
        cout << "contains " << i << " in container -> " << (contains(v, i) ? "true" : "false") << endl;
    }

    cout << "contains_any(should 1) => " << contains_any(v, 20, 21, 22, 23) << endl;
    cout << "contains_all(should 0) => " << contains_all(v, 20, 21, 22, 23) << endl;
    cout << "contains_none(should 0) => " << contains_none(v, 20, 21, 22, 23) << endl;

    cout << "contains_any(should 0) => " << contains_any(v, 20, 22, 23) << endl;
    cout << "contains_all(should 1) => " << contains_all(l, 1, 2, 3, 4) << endl;
    cout << "contains_none(should 1) => " << contains_none(v, 20, 22, 23) << endl;

    return 0;
}
