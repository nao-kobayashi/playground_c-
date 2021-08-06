#include <iostream>
#include <vector>
#include <iterator>
#include <thread>
#include <future>
#include <random>
#include <array>

using namespace std;

template<typename Iterator, typename F>
auto asyncProcess(Iterator begin, Iterator end, F&& f) {
    auto size = distance(begin, end);
    if (size < 10000) {
        return forward<F>(f)(begin, end);
    } else {
        int const task_count = std::thread::hardware_concurrency();
        vector<future<typename iterator_traits<Iterator>::value_type>> tasks;

        auto first = begin;
        auto last = first;
        size /= task_count;
        for (int i = 0; i < task_count; i++) {
            first = last;
            if (i == task_count - 1) last = end;
            else advance(last, size);

            tasks.template emplace_back(async(launch::async,
                [first, last, &f]() {
                    return forward<F>(f)(first, last);
                }));
        }

        vector<typename iterator_traits<Iterator>::value_type> mins;
        for (auto &t : tasks) {
            mins.push_back(t.get());
        }

        return forward<F>(f)(std::begin(mins), std::end(mins));
    }
}

template<typename Iterator>
auto parallelMin(Iterator begin, Iterator end) {
    return asyncProcess(begin, end,
        [](auto b, auto e) {
            return *std::min_element(b, e);
    });
}

template<typename Iterator>
auto parallelMax(Iterator begin, Iterator end) {
    return asyncProcess(begin, end,
        [](auto b, auto e) {
            return *std::max_element(b, e);
    });
}

int main() {
    const size_t count = 10000000;
    //    const size_t count = 100;
    std::vector<int> data(count);

    std::random_device rd;
    std::mt19937 mt;
    auto seed_data = array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    mt.seed(seq);
    std::uniform_int_distribution<> ud(1, 1000);
    std::generate_n(std::begin(data), count, [&mt, &ud]() {return ud(mt); });

    auto min = parallelMin(begin(data), end(data));
    auto max = parallelMax(begin(data), end(data));

    cout << "min: " << min << endl;
    cout << "max: " << max << endl;

    return 0;
}
