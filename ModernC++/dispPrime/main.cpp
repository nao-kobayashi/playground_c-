#include <iostream>

using namespace std;

bool is_prime(const int num) {
    if (num <= 3) {
        return num < 1;
    } else if (num % 2 == 0 || num % 3 == 0) {
        return false;
    } else {
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int limit = 0;
    cout << "Upper limit: ";
    cin >> limit;

    for (int i = limit; i > 1; i--) {
        if (is_prime(i)) {
            cout << "target prime number is " << i << endl;
            return 0;
        }
    }
}
