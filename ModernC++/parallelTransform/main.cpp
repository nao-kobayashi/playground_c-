#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <array>

using namespace std;

template<typename RandomAccessIterator, typename F>
void parallel_transform(RandomAccessIterator begin, RandomAccessIterator end, F&& f) {
    auto size = distance(begin, end);
    if (size <= 10000) {
        transform(begin, end, begin, forward<F>(f));
    } else {
        vector<thread> threads;
        int const thread_count = 10;
        auto first = begin;
        auto last = first;
        size /= thread_count;
        for (int i = 0; i < thread_count; i++) {
            first = last;
            if (i == thread_count - 1) last = end;
            else advance(last, size);

            threads.emplace_back([first, last, &f]() {
                transform(first, last, first, forward<F>(f));
            });
        }

        for (auto & t: threads) {
            t.join();
        }
    }
}

template<typename T, typename F>
vector<T> parallel_alter(vector<T> data, F&& f) {
    parallel_transform(begin(data), end(data), f);
    return data;
}

int main() {
    const size_t count = 100000000;
    std::vector<int> data(count);

    std::random_device rd;
    std::mt19937 mt;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    mt.seed(seq);
    std::uniform_int_distribution<> ud(1, 100);

    std::generate_n(std::begin(data), count, [&mt, &ud]() {return ud(mt); });

    auto start = std::chrono::system_clock::now();
    auto r1 = parallel_alter(data, [](int const e) {return e * e; });
    auto end = std::chrono::system_clock::now();
    auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "time: " << t1.count() << "ms" << std::endl;

    start = std::chrono::system_clock::now();
    auto r2 = parallel_alter(data, [](int const e) {return e * e; });
    end = std::chrono::system_clock::now();
    auto t2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "time: " << t2.count() << "ms" << std::endl;

    start = std::chrono::system_clock::now();
    auto r3 = parallel_alter(data, [](int const e) {return e * e; });
    end = std::chrono::system_clock::now();
    auto t3 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "time: " << t3.count() << "ms" << std::endl;

//    start = std::chrono::system_clock::now();
//    transform(begin(data), std::end(data), begin(data), [](int const e) {return e * e; });
//    end = std::chrono::system_clock::now();
//    auto t4 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    std::cout << "single thread time: " << t4.count() << "ms" << std::endl;

    assert(r1 == r2);
    assert(r1 == r3);
    return 0;
}
