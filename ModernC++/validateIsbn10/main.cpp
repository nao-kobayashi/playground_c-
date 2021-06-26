#include <iostream>
#include <numeric>

using namespace std;

bool validate_isbn_10(string_view isbn) {
    auto valid = false;
    if (isbn.size() == 10 && all_of(cbegin(isbn), cend(isbn), [](char c) { return isdigit(c);})) {
        auto w = 10;
        auto sum = accumulate(cbegin(isbn), cend(isbn), 0,
            [&w](const int total, const char c) {
                return total + w-- * (c - '0');
            });
        valid = !(sum % 11);
    }

    return valid;
}

int main() {
    string_view isbn("4839915660");
    auto result = validate_isbn_10(isbn);
    cout << "isbn:" << isbn << " " << (result ? "true" : "false");
    return 0;
}
