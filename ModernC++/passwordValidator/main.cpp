#include <iostream>
#include <algorithm>
#include "ctype.h"

using namespace std;

class password_validator {
public:
    virtual bool validate(string_view password) = 0;
    virtual ~password_validator() {
        cout << "destruct" << endl;
    }
};

class length_validator final: public password_validator {
public:
    explicit length_validator(unsigned int min_length): length(min_length) {}

    virtual bool validate(string_view password) override {
        return password.length() >= length;
    }

private:
    unsigned int const length;
};

class password_validator_decorator: public password_validator {
public:
    explicit password_validator_decorator(unique_ptr<password_validator> validator): inner(move(validator)) {}

    virtual bool validate(string_view password) override {
        return inner->validate(password);
    }

private:
    unique_ptr<password_validator> inner;
};

class digit_password_validator final: public password_validator_decorator {
public:
    explicit digit_password_validator(unique_ptr<password_validator> validator):
        password_validator_decorator(move(validator)) {}

    virtual bool validate(string_view password) override {
        if (!password_validator_decorator::validate(password)) {
            return false;
        }

        return password.find_first_of("0123456789") != string::npos;
    }
};

class case_password_validator final: public password_validator_decorator {
public:
    explicit case_password_validator(unique_ptr<password_validator> validator):
    password_validator_decorator(move(validator)) {}

    virtual bool validate(string_view password) override {
        if (!password_validator_decorator::validate(password)) {
            return false;
        }

        bool const has_lower = std::any_of(std::cbegin(password), std::cend(password), [](const char c) { return islower(c); });
        bool const has_upper = std::any_of(std::cbegin(password), std::cend(password), [](const char c) { return isupper(c); });

        return has_lower && has_upper;
    }
};

class symbol_password_validator final: public password_validator_decorator {
public:
    explicit symbol_password_validator(unique_ptr<password_validator> validator):
    password_validator_decorator(move(validator)) {}

    virtual bool validate(string_view password) override {
        if (!password_validator_decorator::validate(password)) {
            return false;
        }

        return password.find_first_of(("!@#$%^&*(){}?<>")) != string::npos;
    }
};

int main() {
    auto validator1 = make_unique<digit_password_validator>(make_unique<length_validator>(8));
    assert(validator1->validate("abc123!@#"));
    assert(!validator1->validate("abcde!@#"));
    assert(!validator1->validate("abc1!@#"));

    auto validator2 = make_unique<symbol_password_validator>(
            make_unique<case_password_validator>(
                    make_unique<digit_password_validator>(
                            make_unique<length_validator>(8))));

    assert(validator2->validate("Abc123!@#"));
    assert(!validator2->validate("Abc1234567"));
    assert(!validator2->validate("abc123!@#"));

    auto validator3 = make_unique<case_password_validator>(make_unique<length_validator>(3));
    assert(validator3->validate("aBc"));
    assert(!validator3->validate("abc"));
    assert(!validator3->validate("ABC"));

    cout << "main finished" << endl;
    return 0;
}
