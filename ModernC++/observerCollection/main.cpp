#include <iostream>
#include <vector>

using namespace std;

enum class collection_action {
    add,
    remove,
    clear,
    assign
};

string to_string(collection_action const action) {
    switch (action) {
        case collection_action::add:
            return "add";
        case collection_action::remove:
            return "remove";
        case collection_action::clear:
            return "clear";
        case collection_action::assign:
            return "assign";
    }
};

struct collection_change_notification {
    collection_action action;
    vector<size_t> item_indexes;
};

class collection_observer {
public:
    virtual void collection_changed(collection_change_notification notification) = 0;
    virtual ~collection_observer() = default;
};

template<typename T, class Allocator = std::allocator<T>>
class observable_vector final {
    typedef typename vector<T, Allocator>::size_type size_type;
public:
    observable_vector() noexcept(noexcept(Allocator())): observable_vector( Allocator() ) {}

    explicit observable_vector(const Allocator& alloc) noexcept : data(alloc) {}

    observable_vector(size_type count, const T& value, const Allocator& alloc = Allocator())
        :data(count, value, alloc) {}

    explicit observable_vector(size_t count, const Allocator& alloc = Allocator()): data(count, alloc) {}

    observable_vector(observable_vector&& other) noexcept : data(other.data) {}

    observable_vector(observable_vector&& other, const Allocator& alloc) noexcept : data(other.data, alloc) {}

    observable_vector(initializer_list<T> init, const Allocator& alloc = Allocator())
        :data(init, alloc) {}

    template<class InputIt>
    observable_vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
        :data(first, last, alloc) {}

    observable_vector& operator=(observable_vector const & other) {
        if (this != &other) {
            data = other.data;

            for (auto o : observers) {
                if (o != nullptr) {
                    o->collection_changed({
                        collection_action::assign,
                        vector<size_t> {}
                    });
                }
            }
        }
        return *this;
    }

    observable_vector& operator=(observable_vector const && other) {
        if (this != &other) {
            data = move(other.data);

            for (auto o : observers) {
                if (o != nullptr) {
                    o->collection_changed({
                        collection_action::assign,
                        vector<size_t> {}
                    });
                }
            }
        }
        return *this;
    }

    void push_back(T&& value) {
        data.push_back(value);

        for(auto o : observers) {
            if (o != nullptr) {
                o->collection_changed({
                    collection_action::add,
                    vector<size_t> { data.size() - 1 }
                });
            }
        }
    }

    void pop_back() {
        data.pop_back();

        for(auto o : observers) {
            if (o != nullptr) {
                o->collection_changed({
                    collection_action::remove,
                    vector<size_t> { data.size() + 1 }
                });
            }
        }
    }

    void clear() noexcept {
        data.clear();

        for(auto o : observers) {
            if (o != nullptr) {
                o->collection_changed({
                    collection_action::clear,
                    vector<size_t> {}
                });
            }
        }
    }

    size_type size() const noexcept {
        return data.size();
    }

    //nodiscard属性は関数の戻り値を破棄してはならないことをコンパイラに伝え、破棄した場合に警告するための属性
    [[nodiscard]] bool empty() const noexcept {
        return data.empty();
    }

    void add_observer(collection_observer * const o) {
        observers.push_back(o);
    }

    void remove_observer(collection_observer * const o) {
        observers.erase(remove(begin(observers), end(observers), o), end(observers));
    }

private:
    vector<T, Allocator> data;
    vector<collection_observer*> observers;
};

class observer: public collection_observer {
public:
    virtual void collection_changed(collection_change_notification notification) override {
        cout << "action: " << to_string(notification.action);
        if (!notification.item_indexes.empty()) {
            cout << ", indexes: ";
            for (auto const i : notification.item_indexes) {
                cout << i << ' ';
            }
        }
        cout << endl;
    }
};

int main() {
    observable_vector<int> v;
    observer o, o1;

    v.add_observer(&o);
    v.add_observer(&o1);

    v.push_back(1);
    v.push_back(2);
    v.pop_back();
    v.clear();

    v.remove_observer(&o);

    v.push_back(3);
    v.push_back(4);

    v.add_observer(&o);

    observable_vector<int> v2 {1, 2, 3};
    v = v2;
    v = observable_vector<int> {7, 8, 9};

    return 0;
}
