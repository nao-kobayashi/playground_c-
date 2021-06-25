#include <iostream>

using namespace std;

unsigned int gcd(unsigned int a, unsigned int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

//#include <numeric>
//gcd()
int main() {
    unsigned int a, b;
    cout << "calc gcd(a, b) input a: ";
    cin >> a;
    cout << "input b: ";
    cin >> b;

    cout << "answer: " << gcd(a, b) << endl;
}
