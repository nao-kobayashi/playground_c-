#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

int main() {
    unsigned long long limit = 4000000;
    std::cin >> limit;

    const unsigned int NumPrimes = 12;
    unsigned int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    typedef std::vector<unsigned char> Exponents;
    std::map<long double, Exponents> todo = {{1, Exponents(NumPrimes, 0)}};

    while(true) {
        auto current = todo.begin();
        auto value = current->first;
        auto exponents = current->second;
        todo.erase(current);

        unsigned long long uniqueFactors = 1;
        for (auto x: exponents) {
            uniqueFactors *= 2 * x + 1;
        }
        uniqueFactors++;
        uniqueFactors /= 2;

        if (uniqueFactors >= limit) {
            std::cout << todo.size() << std::endl;
            std::cout << std::fixed << std::setprecision(0) << value << std::endl;
            break;
        }

        for (size_t i = 0; i < exponents.size(); i++) {
            if (exponents[i] == 1 && i > 3)
                break;

            exponents[i]++;
            value *= primes[i];
            todo[value] = exponents;
        }
    }

    return 0;
}
