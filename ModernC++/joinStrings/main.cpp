#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template<typename Iter>
string join_strings(Iter begin, Iter end, const char * const separator) {
    ostringstream oss;
    //-1 needs to eliminate last separator.
    copy(begin, end - 1, ostream_iterator<string>(oss, separator));
    oss << *(end - 1);
    return oss.str();
}

template<typename C>
string join_strings(const C &c, const char * const separator) {
    if (c.size() == 0) return {};
    return join_strings(cbegin(c), cend(c), separator);
}

int main() {
    vector<string> v1 {"this", "is", "an", "example"};
    vector<string> v2 {"example"};
    vector<string> v3 {};

    cout << join_strings(v1, " ") << endl;
    assert(join_strings(v1, " ") == "this is an example"s);
    assert(join_strings(v2, " ") == "example"s);
    assert(join_strings(v3, " ") == ""s);

    return 0;
}
