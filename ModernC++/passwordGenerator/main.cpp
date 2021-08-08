#include <iostream>
#include <random>
#include <array>

using namespace std;

class password_generator {
public:
    virtual string generate() = 0;

    virtual string allowed_chars() const = 0;
    virtual size_t length() const = 0;
    virtual void add(unique_ptr<password_generator> generator) = 0;

    virtual ~password_generator() = default;
};

class basic_password_generator: public password_generator {
    size_t const len;
public:
    explicit basic_password_generator(size_t const len) noexcept : len(len) {}
    virtual string generate() override {
        throw runtime_error("not implemented");
    }

    virtual void add(unique_ptr<password_generator> generator) override {
        throw runtime_error("not implemented");
    }

    virtual size_t length() const noexcept override final {
        return len;
    }
};

class digit_generator: public basic_password_generator {
public:
    digit_generator(size_t const len) noexcept: basic_password_generator(len) {}
    virtual string allowed_chars() const override {
        return "0123456789";
    }
};

class symbol_generator: public basic_password_generator {
public:
    symbol_generator(size_t const len) noexcept: basic_password_generator(len) {}
    virtual string allowed_chars() const override {
        return "!@#$%^&*(){}[]?<>";
    }
};

class upper_letter__generator: public basic_password_generator {
public:
    upper_letter__generator(size_t const len) noexcept: basic_password_generator(len) {}
    virtual string allowed_chars() const override {
        return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
};

class lower_letter__generator: public basic_password_generator {
public:
    lower_letter__generator(size_t const len) noexcept: basic_password_generator(len) {}
    virtual string allowed_chars() const override {
        return "abcdefghijklmnopqrstuvwxyz";
    }
};

class composite_password_generator: public password_generator {
    virtual string allowed_chars() const override {
        throw runtime_error("not implemented");
    }

    virtual size_t length() const override {
        throw runtime_error("not implemented");
    }

public:
    composite_password_generator() {
        auto seed_data = array<int, mt19937::state_size> {};
        ::generate(begin(seed_data), end(seed_data), ref(rd));
        seed_seq seq(cbegin(seed_data), cend(seed_data));
        eng.seed(seq);
    }

    virtual string generate() override {
        string password;
        for (auto & generator: generators) {
            string chars = generator->allowed_chars();
            uniform_int_distribution<> ud(0, static_cast<int>(chars.length() - 1));

            for (size_t i = 0; i < generator->length(); i++) {
                password += chars[ud(eng)];
            }
        }

        cout << "temp password: " << password << endl;

        shuffle(begin(password), end(password), eng);
        return password;
    }

    virtual void add(unique_ptr<password_generator> generator) override {
        generators.push_back(move(generator));
    }

private:
    random_device rd;
    mt19937 eng;
    vector<unique_ptr<password_generator>> generators;
};

int main() {
    composite_password_generator generator;
    generator.add(make_unique<symbol_generator>(2));
    generator.add(make_unique<digit_generator>(2));
    generator.add(make_unique<upper_letter__generator>(2));
    generator.add(make_unique<lower_letter__generator>(4));

    auto const password = generator.generate();
    cout << "real password: " << password << endl;
    return 0;
}
