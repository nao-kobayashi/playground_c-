#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<unsigned long long> prime_factors(unsigned long long n) {
    vector<unsigned long long> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n = n / 2;
    }

    const int root = static_cast<int>(sqrt(n));
    for (unsigned long long i = 3; i <= root; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n = n / i;
        }
    }

    if (n > 2) {
        factors.push_back(n);
    }

    return factors;
}

int main() {
    unsigned long long num = 0;
    cout << "number: ";
    cin >> num;

    auto factors = prime_factors(num);
    copy(cbegin(factors), cend(factors), ostream_iterator<unsigned long long>(cout, " "));
}
