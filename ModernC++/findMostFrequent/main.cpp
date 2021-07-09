#include <iostream>
#include <vector>
#include <map>
#include <random>

using namespace std;

template<typename T>
vector<pair<T, size_t>> find_most_frequent(const vector<T> &range) {
    map<T, size_t> counts;

    for (const auto &e : range) counts[e]++;

    auto maxElement = max_element(begin(counts), end(counts),
        [](const auto &e1, const auto &e2) {
            return e1.second < e2.second;
        });

    vector<pair<T, size_t>> result;
    copy_if(begin(counts), end(counts),
        back_inserter(result),
        [maxElement](const auto &kvp) {
            return kvp.second == maxElement->second;
        });

    return result;
}

int main() {
    //auto range = vector<int> {1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5};
    vector<int> range;
    //非決定的な乱数生成器を生成
    random_device rnd;
    //メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    mt19937 mt(rnd());
    uniform_int_distribution<> rand(1, 25);
    for (int i = 0; i < 100; i++) {
        range.push_back(rand(mt));
    }

    auto result = find_most_frequent(range);
    for (const auto &[n, count]: result) {
        cout << "value: " << n << '\t' << "count: " << count << endl;
    }
    return 0;
}
