#include <iostream>
#include <vector>
#include <thread>
#include <numeric>

using namespace std;
using namespace chrono_literals;

template<typename T>
class double_buffer {
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
public:
    explicit double_buffer(const size_t size) : read_buf(size), write_buf(size) {}
    size_t size() const noexcept { return read_buf.size(); }

    void write(const T *const ptr, const size_t size) {
        unique_lock<mutex> lock(mt);
        auto length = min(size, write_buf.size());
        copy(ptr, ptr + length, begin(write_buf));
        write_buf.swap(read_buf);
    }

    template<class Output>
    void read(Output it) const  {
        unique_lock<mutex> lock(mt);
        copy(cbegin(read_buf), cend(read_buf), it);
    }

    pointer data() const {
        unique_lock<mutex> lock(mt);
        return read_buf.data();
    }

    const_reference operator[](const size_t pos) const {
        unique_lock<mutex> lock(mt);
        return read_buf[pos];
    }

    reference operator[](const size_t pos) {
        unique_lock<mutex> lock(mt);
        return read_buf[pos];
    }

    void swap(double_buffer other) {
        swap(read_buf, other.read_buf);
        swap(write_buf, other.write_buf);
    }

private:
    vector<T> read_buf;
    vector<T> write_buf;
    mutable mutex mt;
};

template<typename T>
void print_buffer(const double_buffer<T> &buf) {
    buf.read(ostream_iterator<T>(cout, " "));
    cout << endl;
}

int main() {
    double_buffer<int> buf(10);

    thread t([&buf](){
       for (int i = 1; i < 1000; i += 10) {
           int data[10] = {};
           iota(begin(data), end(data), i);
           buf.write(data, size(data));

           this_thread::sleep_for(100ms);
       }
    });

    auto start = chrono::system_clock::now();
    do {
        print_buffer(buf);

        this_thread::sleep_for(150ms);
    } while (chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - start).count() < 12);

    t.join();
    return 0;
}
