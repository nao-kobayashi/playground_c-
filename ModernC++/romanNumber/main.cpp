#include <iostream>
#include <vector>
#include <string>

using namespace std;

string to_roman(unsigned int num) {
    const vector<pair<unsigned int, const char*>> roman {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        { 10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    string result;
    for (const auto elm : roman) {
        while (num >= elm.first) {
            result += elm.second;
            num -= elm.first;
        }
    }

    return result;
}

int main() {
    for (int i = 1; i <= 100; i++) {
        cout << i << "\t" << to_roman(i) << endl;
    }
}
