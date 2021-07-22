#include <iostream>
#include <chrono>
#include "Universe.h"

using namespace std;
using namespace chrono;

int main() {
    int generations;
    int speed;
    cout << "input max generations:";
    cin >> generations;

    cout << "input life speed(ms):";
    cin >> speed;

    Universe u(60, 40);
    u.run(Universe::Seed::random, generations, chrono::milliseconds(speed));
    return 0;
}
