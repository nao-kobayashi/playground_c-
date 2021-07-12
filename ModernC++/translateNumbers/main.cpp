#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

bool starts_with(string_view str, string_view prefix) {
    return str.find(prefix) == 0;
}

void normalize_phone_numbers(vector<string> &numbers, const string &countryCode) {
    transform(cbegin(numbers), cend(numbers), begin(numbers), [countryCode](const string &number) {
        string result;

        if (number.size() > 0) {
            if (number[0] == '0') {
                result = "+" + countryCode + number.substr(1);
            } else if (starts_with(number, countryCode)) {
                result = "+" + number;
            } else if (starts_with(number, "+" + countryCode)) {
                result = number;
            } else {
                result = "+" + countryCode + number;
            }
        }

        result.erase(remove_if(begin(result), end(result), [](const char ch) {return isspace(ch);}),
                end(result));

        return result;
    });
}

int main() {
    vector<string> numbers {
            "0744909080",
            "44 7520 112233",
            "+44 7555 123456",
            "40 3219 1238932",
            "7555 123456"
    };

    normalize_phone_numbers(numbers, "44");
    for (auto s: numbers) {
        cout << s << endl;
    }

    return 0;
}
