#include <iostream>
#include <random>

using namespace std;

#ifndef WEASEL_WEASEL_H
#define WEASEL_WEASEL_H
class Weasel {
private:
    string target;
    uniform_int_distribution<> chardist;
    uniform_real_distribution<> ratedist;
    mt19937 mt;
    const string allowed_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

public :
    Weasel() = delete;
    explicit Weasel(string_view t);
    void run(const int copies);
    int fitness(string_view candidate);
    string mutate(string_view parent, const double rate);
    string make_random();
};
#endif //WEASEL_WEASEL_H
