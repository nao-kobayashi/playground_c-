#include <iostream>
#include <regex>

using namespace std;

string transform_date(const string &text) {
    auto rx = regex { R"((\d{2})(\.|-)(\d{2})(\.|-)(\d{4}))" };
    return regex_replace(text, rx, "$5-$3-$1");
}

int main() {
    assert(transform_date("today is 01.12.2017!"s) == "today is 2017-12-01!"s);
    cout << transform_date("今日は、29.06.2021です。"s) << endl;
    return 0;
}
