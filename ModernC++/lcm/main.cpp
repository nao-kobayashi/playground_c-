#include <iostream>
#include "stdlib.h"

using namespace std;

unsigned int gcd(unsigned int a, unsigned int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

unsigned int lcm(unsigned int a, unsigned int b) {
    unsigned int h = gcd(a, b);
    int c = a * b;
    return h ?  abs(c) / h : 0;
}

//#include <numeric>
//accumulate()
int main() {
    unsigned int a, b;
    cout << "calc lcm(a, b) input a: ";
    cin >> a;
    cout << "input b: ";
    cin >> b;

    cout << "answer: " << lcm(a, b) << endl;
}
