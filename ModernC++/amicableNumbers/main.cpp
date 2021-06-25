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

void print_amicables(const int limit) {
    for (int num = 4; num < limit; ++num) {
        if (auto sum1 = sum_proper_divisors(num); sum1 < limit) {
            if (auto sum2 = sum_proper_divisors(sum1); sum2 == num && num != sum1 && num < sum1) {
                cout << num << "," << sum1 << endl;
            }
        }
    }
}

int main() {
    int limit = 0;
    cout << "Upper limit: ";
    cin >> limit;

    print_amicables(limit);
}