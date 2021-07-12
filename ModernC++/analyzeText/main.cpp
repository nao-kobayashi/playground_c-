#include <iostream>
#include <string_view>
#include <map>
#include <numeric>
#include <iomanip>

using namespace std;

map<char, double> analyze_text(string_view text) {
    map<char, double> frequencies;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        frequencies[ch] = 0;
    }

    for (auto ch: text) {
        if (isalpha(ch))
            frequencies[tolower(ch)]++;
    }

    auto total = accumulate(
            begin(frequencies),
            end(frequencies),
            0ULL,
            [](const auto sum, const auto &kvp) {
                return sum + static_cast<unsigned long long>(kvp.second);
            });

    for_each(begin(frequencies), end(frequencies),
             [total](auto &kvp) {
                 kvp.second = (100.0 * kvp.second) / static_cast<double>(total);
             });

    return frequencies;
}

int main() {
    auto result = analyze_text(R"(If you have any questions about your bill, contact support. )"
            R"(This email confirms payment for the iCloud storage plan listed above. )"
            R"(You will be billed each plan period until you cancel by downgrading to the free storage plan from your iOS device, ")
            R"(Mac or PC.)");

    for (const auto &[ch, rate]: result) {
        cout << ch << ":" << setprecision(2) << rate << endl;
    }

    return 0;
}
