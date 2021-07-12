#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

bool starts_with(string_view str, string_view prefix) {
    return str.find(prefix) == 0;
}

template<typename T>
vector<string> filter_numbers(T begin, T end, const string &countryCode) {
    vector<string> result;

    copy_if(begin, end, back_inserter(result), [countryCode](const auto &number) {
        return starts_with(number, countryCode) || starts_with(number, "+" + countryCode);
    });

    return result;
}

vector<string> filter_numbers(const vector<string> &numbers, const string &countryCode) {
    return filter_numbers(cbegin(numbers), cend(numbers), countryCode);
}


int main() {
    vector<string> numbers {
        "+40744909080",
        "44 7520 112233",
        "+44 7555 123456",
        "40 3219 1238932",
        "7555 123456"
    };

    auto result = filter_numbers(numbers, "44");

    for (auto s: result) {
        cout << s << endl;
    }

    return 0;
}
