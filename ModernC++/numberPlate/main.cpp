#include <iostream>
#include <regex>
#include <vector>

using namespace std;

bool validate_number_plate(const string &str) {
    regex rx(R"([A-Z]{3}-[A-Z]{2} \d{3,4})");
    return regex_match(str.c_str(), rx);
}

vector<string> extract_number_plate(const string &str) {
    regex rx(R"(([A-Z]{3}-[A-Z]{2} \d{3,4})*)");
    smatch match;
    vector<string> results;

    for (auto i = sregex_iterator(cbegin(str), cend(str), rx);
        i != sregex_iterator(); i++) {

        if ((*i)[1].matched)
            results.push_back(i->str());
    }

    return results;
}

int main() {
    assert(validate_number_plate("ABC-DE 123"));
    assert(validate_number_plate("ABC-DE 1234"));
    assert(!validate_number_plate("ABC-DE 12345"));
    assert(!validate_number_plate("abc-de 123"));

    vector<string> expected {"AAA-AA 123", "ABC-DE 1234", "XYZ-WW 0001"};
    string text("AAA-AA 123qwe-ty 1234  ABC-DE 123456..XYZ-WW 0001XYz-WW-0001");
    assert(extract_number_plate(text) == expected);

    for (auto word: extract_number_plate(text)) {
        cout << word << endl;
    }

    return 0;
}
