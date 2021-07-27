#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>
#include <random>
#include <chrono>
#include <thread>
#include <assert.h>

using namespace std;

template<typename Iterator, typename F>
auto sequential_process(Iterator begin, Iterator end, F&& f) {
    return forward<F>(f)(begin, end);
}

template <typename Iterator>
auto sequential_min(Iterator begin, Iterator end) {
    return sequential_process(begin, end, [](auto b, auto e) { return *min_element(b, e); });
}

template <typename Iterator>
auto sequential_max(Iterator begin, Iterator end) {
    return sequential_process(begin, end, [](auto b, auto e) { return *max_element(b, e); });
}

template<typename Iterator, typename F>
auto parallel_process(Iterator begin, Iterator end, F&& f) {
    auto size = distance(begin, end);
    if (size <= 10000) {
        return std::forward<F>(f)(begin, end);
    } else {
        int const threads_count = thread::hardware_concurrency();
        vector<thread> threads;
        vector<typename iterator_traits<Iterator>::value_type> mins(threads_count);

        auto first = begin;
        auto last = first;
        size /= threads_count;

        for (int i = 0; i < threads_count;i++) {
            first = last;
            if (i == threads_count - 1) last = end;
            else advance(last, size);

            threads.emplace_back([first, last, &f, &r = mins[i]]() {
                r = forward<F>(f)(first, last);
            });
        }

        for (auto &t : threads) {
            t.join();
        }

        return forward<F>(f)(std::begin(mins), std::end(mins));
    }
}

template <typename Iterator>
auto parallel_min(Iterator begin, Iterator end) {
    return parallel_process(begin, end, [](auto b, auto e) { return *min_element(b, e); });
}

template <typename Iterator>
auto parallel_max(Iterator begin, Iterator end) {
    return parallel_process(begin, end, [](auto b, auto e) { return *max_element(b, e); });
}

int main() {
    const size_t count = 10000000;
//    const size_t count = 100;
    std::vector<int> data(count);

    std::random_device rd;
    std::mt19937 mt;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    mt.seed(seq);
    std::uniform_int_distribution<> ud(1, 1000);

    std::generate_n(std::begin(data), count, [&mt, &ud]() {return ud(mt); });

    {
        std::cout << "minimum element" << std::endl;

        auto start = std::chrono::system_clock::now();
        auto r1 = sequential_min(std::begin(data), std::end(data));
        auto end = std::chrono::system_clock::now();
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "seq time: " << t1.count() << "ms" << std::endl;

        start = std::chrono::system_clock::now();
        auto r2 = parallel_min(std::begin(data), std::end(data));
        end = std::chrono::system_clock::now();
        auto t2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "par time: " << t2.count() << "ms" << std::endl;

        assert(r1 == r2);
    }

    {
        std::cout << "maximum element" << std::endl;

        auto start = std::chrono::system_clock::now();
        auto r1 = sequential_max(std::begin(data), std::end(data));
        auto end = std::chrono::system_clock::now();
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "seq time: " << t1.count() << "ms" << std::endl;

        start = std::chrono::system_clock::now();
        auto r2 = parallel_max(std::begin(data), std::end(data));
        end = std::chrono::system_clock::now();
        auto t2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "par time: " << t2.count() << "ms" << std::endl;

        assert(r1 == r2);
    }
}
