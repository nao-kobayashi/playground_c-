#include <iostream>

unsigned long long numDivisors(unsigned long long n) {
    unsigned int result = 1;
    auto reduce = n;

    for (unsigned long long divisor = 2; divisor <= reduce; divisor++) {
        if (divisor % 2 == 0 && divisor > 2)
            divisor++;

        if (divisor > 100)
            break;

        unsigned exponent = 0;
        while (reduce % divisor == 0) {
            exponent++;
            reduce /= divisor;
        }

        result *= exponent + 1;
    }

    return result;
}

int main() {
    unsigned  long long  n = 1;
    unsigned  long long threshold = 1000;

    while(true) {
        auto divisors = numDivisors(n * n);
        auto half = (divisors + 1) / 2;
        if (half >= threshold) {
            std::cout << n << std::endl;
            std::cout << half << std::endl;
            break;
        }
        n++;
    }
    return 0;
}
