#include <iostream>
#include <vector>

using namespace std;

template <class T>
class circular_buffer_iterator;

template<class T>
class circular_buffer {
    using const_iterator = circular_buffer_iterator<T>;

public:
    circular_buffer() = delete;
    explicit circular_buffer(const size_t size): data_(size) {}

    void clear() noexcept {
        head_ = 1;
        size_ = 0;
    }

    bool empty() const noexcept { return size_ == 0; }
    bool full() const noexcept { return size_ == data_.size(); }
    size_t capacity() const noexcept { return data_.size(); }
    size_t size() const noexcept { return size_; }

    void push(const T item) {
        head_ = next_pos();
        data_[head_] = item;
        if (size_ < data_.size()) size_++;
    }

    T pop() {
        if (empty()) throw runtime_error("empty buffer");

        auto pos = first_pos();
        size_--;
        return data_[pos];
    }

    const_iterator begin() const {
        return const_iterator(*this, first_pos(), empty());
    }

    const_iterator end() const {
        return const_iterator(*this, next_pos(), true);
    }

private:
    vector<T> data_;
    size_t head_ = -1;
    size_t size_ = 0;

    size_t next_pos() const noexcept {
        return size_ == 0 ? 0 : (head_ + 1) % data_.size();
    }

    size_t first_pos() const noexcept {
        return size_ == 0 ? 0 : (head_ + data_.size() - size_ + 1) % data_.size();
    }

    friend class circular_buffer_iterator<T>;
};

template <class T>
class circular_buffer_iterator {
    using self_type = circular_buffer_iterator;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator_category = random_access_iterator_tag;
    using difference_type = ptrdiff_t;
public:
    circular_buffer_iterator(const circular_buffer<T> &buf, const size_t pos, const bool last)
        : buffer_(buf), index_(pos), last_(last) {}

    self_type& operator++() {
        if (last_) {
            throw out_of_range("Iterator cannot be incremented past the end of range.");
        }

        index_ = (index_ + 1) % buffer_.data_.size();
        last_ = index_ == buffer_.next_pos();
        return *this;
    };

    self_type operator++(int) {
        self_type tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const self_type &other) const {
        assert(compatible(other));
        return index_ == other.index_ && last_ == other.last_;
    }

    bool operator!=(const self_type &other) const {
        return !(*this == other);
    }

    const_reference operator*() const {
        return buffer_.data_[index_];
    }

    const_pointer operator->() const {
        return addressof(operator*());
    }

private:
    bool compatible(const self_type &other) const {
        return &buffer_ == &other.buffer_;
    }

    const circular_buffer<T> &buffer_;
    size_t index_;
    bool last_;
};

int main() {
    circular_buffer<int> buffer(5);
    buffer.push(1);
    buffer.push(2);
    buffer.push(3);

    for (auto i: buffer) {
        cout << i << " ";
    }
    cout << endl;

    auto item = buffer.pop();
    cout << item << endl;

    buffer.push(4);
    buffer.push(5);
    buffer.push(6);
    buffer.push(7);
    buffer.push(8);

    item = buffer.pop();
    cout << item << endl;
    item = buffer.pop();
    cout << item << endl;
    item = buffer.pop();
    cout << item << endl;
    item = buffer.pop();
    cout << item << endl;
    item = buffer.pop();
    cout << item << endl;

    cout << "is empty:" << buffer.empty() << endl;

    buffer.push(9);
    cout << buffer.size() << endl;

    return 0;
}
