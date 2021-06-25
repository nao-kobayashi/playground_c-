#include <iostream>
#include <cmath>

using namespace std;

int sum_proper_divisors(const int num) {
    int result = 1;
    const int root = static_cast<int>(sqrt(num));
    for (int i = 2; i <= root; i++) {
        if (num % i == 0) {
            result += (i == (num / i)) ? i : (i + num / i);
        }
    }
    return result;
}

void print_abundant(const int limit) {
    for (int num = 10; num <= limit; ++num) {
        if (auto sum = sum_proper_divisors(num); sum > num) {
            cout << num << ", abundance=" << sum - num << endl;
        }
    }
}

int main() {
    int limit = 0;
    cout << "Upper limit: ";
    cin >> limit;

    print_abundant(limit);
}
