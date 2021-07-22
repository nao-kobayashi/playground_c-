#ifndef LIFEGAME_UNIVERSE_H
#define LIFEGAME_UNIVERSE_H
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

class Universe {
public:
    enum class Seed { random, ten_cell_row };
    Universe(size_t const width, size_t const height);
    void run(Seed const s, int const generations, chrono::milliseconds const ms = chrono::milliseconds(100));
private:
    Universe() = delete;
    void next_generation();
    void reset_display() const;
    void display();
    void initialize(Seed const s);
    void reset();
    int count_alive() const;

    template<typename T1, typename... T>
    auto count_alive(T1 s, T... ts) const;

    int count_neighbors(size_t const row, size_t const col);
    unsigned char & cell(size_t const col, size_t const row);

    size_t const rows;
    size_t const columns;
    vector<unsigned char> grid;
    unsigned char const alive = 1;
    unsigned char const dead = 0;

    uniform_int_distribution<> dist;
    mt19937 mt;

};
#endif //LIFEGAME_UNIVERSE_H
