#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

template<typename T>
class QuickSelect {
public:
    T select(vector<T>& data, int begin, int end, int k) {
        if (data.size() % 2 == 0) {
            int first = start_select(data, begin, end, k);
            swap(data[k - 1], data[data.size() - 1]);
            int second = start_select(data, begin, end, k - 1);
            return (data[first] + data[second]) / 2;
        } else {
            auto result = start_select(data, begin, end, k - 1);
            return data[result];
        }
    }

private:
    int start_select(vector<T>& data, int begin, int end, int k) {
        auto p = partition(data, begin, end);

        int result = -1;
        if (p == k) {
            result = p;
        } else if (p < k) {
            result = start_select(data, p + 1, end, k);
        } else if (p > k) {
            result = start_select(data, begin, p - 1, k);
        }

        return result;
    }

    int partition(vector<T>& data, int begin, int end) {
        auto pivot = data[end];
        int pivot_index = begin;

        for (int i = begin; i <= end; i++) {
            if (data[i] < pivot) {
                swap(data[i], data[pivot_index]);
                pivot_index++;
            }
        }

        swap(data[end], data[pivot_index]);
        return pivot_index;
    }
};

int main() {
    int count;
    cout << "要素数を入力してください: ";
    cin >> count;
    cout << endl;

    vector<int> data(count);
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<> ud(1, count);
    generate_n(std::begin(data), count, [&mt, &ud]() { return ud(mt); });

    vector<int> data2;
    data2.reserve(count);
    copy(cbegin(data), cend(data), back_inserter(data2));


    auto start1 = chrono::system_clock::now();
    auto qs = QuickSelect<int>();
    auto ans1 = qs.select(data, 0, data.size() - 1, data.size() / 2);
    auto end1 = chrono::system_clock::now();
    auto t1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);
    cout << "quick select time: " << t1.count() << "ms answer: " << ans1 << endl;


    auto start2 = chrono::system_clock::now();
    sort(begin(data2), end(data2));
    auto ans2 = 0;
    if (data2.size() % 2 == 0) {
        int i = data2.size() / 2;
        ans2 = (data2[i] + data2[i - 1]) / 2;
    } else {
        ans2 = data[data2.size() / 2];
    }
    auto end2 = chrono::system_clock::now();
    auto t2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);
    cout << "naive select time: " << t2.count() << "ms answer: " << ans2 << endl;

}
