#include <iostream>
#include "Weasel.h"

int main() {
//    string s = "METHINKS IT IS LIKE A WEASEL";
    string s = "uniform real distribution is Produces random floating point values x uniformly distributed on the interval a to b";
    transform(begin(s), end(s), begin(s), ::toupper);
    Weasel w(s);
    w.run(1000);
    return 0;
}
