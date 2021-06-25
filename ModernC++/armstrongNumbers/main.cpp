#include <iostream>
using namespace std;

void print_armstrongNumbers1() {
    for (int a = 1; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            for (int c = 0; c <= 9; c++) {
                int abc = a * 100 + b * 10 + c;
                int arm = a * a * a + b * b * b + c * c * c;
                if (abc == arm)
                    cout << arm << endl;
            }
        }
    }
}
int main() {
    print_armstrongNumbers1();
    return 0;
}
