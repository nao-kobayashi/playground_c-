#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

template<class Elem>
using tstring = basic_string<Elem, char_traits<Elem>, allocator<Elem>>;

template<class Elem>
using tstringstream = basic_stringstream<Elem, char_traits<Elem>, allocator<Elem>>;

template<class Elem>
inline vector<tstring<Elem>> split(tstring<Elem> text, const Elem delimiter) {
    auto sstr = tstringstream<Elem> { text };
    auto tokens = vector<tstring<Elem>>{};
    auto token = tstring<Elem>{};
    while (getline(sstr, token, delimiter)) {
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

template<class Elem>
inline vector<tstring<Elem>> split(tstring<Elem> text, const tstring<Elem> &delimiters) {
    auto tokens = vector<tstring<Elem>>{};
    size_t pos, prev_pos = 0;
    while ((pos = text.find_first_of(delimiters, prev_pos)) != tstring<Elem>::npos) {
        if (pos > prev_pos) {
            tokens.push_back(text.substr(prev_pos, pos - prev_pos));
        }
        prev_pos = pos + 1;
    }

    if (prev_pos < text.length()) {
        tokens.push_back(text.substr(prev_pos, tstring<Elem>::npos));
    }

    return tokens;
}

int main() {
    vector<string> expected {"this", "is", "a", "sample"};
    assert(expected == split("this is a sample"s, ' '));
    assert(expected == split("this,is a.sample!!"s, ",.! "s));
    auto words = split(".漢字もOK ああ,くくく こ!!"s, ",.! "s);

    for (auto w: words) {
        cout << w << endl;
    }
    return 0;
}
