#include <iostream>

using namespace std;

class role {
public:
    virtual double approval_limit() const noexcept = 0;
    virtual ~role() = default;
};

class employee_role: public role {
public:
    virtual double approval_limit() const noexcept override {
        return 1000.0;
    }
};

class team_manager_role: public role {
public:
    virtual double approval_limit() const noexcept override {
        return 10000.0;
    }
};

class department_manager_role: public role {
public:
    virtual double approval_limit() const noexcept override {
        return 100000.0;
    }
};

class president_role: public role {
public:
    virtual double approval_limit() const noexcept override {
        return numeric_limits<double>::max();
    }
};

struct expense {
    double const amount;
    string const description;

    expense(double const amount, string_view desc)
        : amount(amount), description(desc) {}
};

class employee {
public:
    employee(string_view name, unique_ptr<role> own_role)
        :name(name), own_role(move(own_role)) {}

    void set_direct_manager(shared_ptr<employee> manager) {
        direct_manager = manager;
    }

    void approve(expense const & e) {
        if (e.amount <= own_role->approval_limit())
            cout << name << " approved expense '" << e.description << "', cost=" << e.amount << endl;
        else if (direct_manager != nullptr)
            direct_manager->approve(e);
    }

private:
    string const name;
    unique_ptr<role> const own_role;
    shared_ptr<employee> direct_manager;
};

int main() {
    auto john = make_shared<employee>("john smith", make_unique<employee_role>());
    auto robert = make_shared<employee>("robert booth", make_unique<team_manager_role>());
    auto david = make_shared<employee>("david jones", make_unique<department_manager_role>());
    auto cecil = make_shared<employee>("cecil williams", make_unique<president_role>());

    john->set_direct_manager(robert);
    robert->set_direct_manager(david);
    david->set_direct_manager(cecil);

    john->approve(expense{500, "magazines"});
    john->approve(expense{5000, "hotel accommodation"});
    john->approve(expense{50000, "conference costs"});
    john->approve(expense{200000, "new lorry"});

    return 0;
}
