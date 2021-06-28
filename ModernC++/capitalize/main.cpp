#include <iostream>
#include <sstream>

using namespace std;

template<class Elem>
using tstring = basic_string<Elem, char_traits<Elem>, allocator<Elem>>;

template<class Elem>
using tstringstream = basic_stringstream<Elem, char_traits<Elem>, allocator<Elem>>;

template<class Elem>
tstring<Elem> capitalize(const tstring<Elem> &text) {
    tstringstream<Elem> result;
    bool newWord = true;
    for (auto const ch : text) {
        newWord = newWord || ispunct(ch) || isspace(ch);
        if (isalpha(ch)) {
            if (newWord) {
                result << static_cast<Elem>(toupper(ch));
                newWord = false;
            } else {
                result << static_cast<Elem>(tolower(ch));
            }
        } else {
            result << ch;
        }
    }
    return result.str();
}

int main() {
    assert("The C++ Challenger"s == capitalize("the c++ challenger"s));
    assert("This Is An Example, Should Work!"s == capitalize("THIS IS an EXAMPle, should wORK!"s));
    cout << capitalize("the c++ challenger"s) << endl;
    cout << capitalize("THIS IS an EXAMPle, should wORK!"s) << endl;
    return 0;
}
