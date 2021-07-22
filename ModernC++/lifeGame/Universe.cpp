#include <array>
#include <thread>
#include "Universe.h"

using namespace chrono_literals;

Universe::Universe(const size_t width, const size_t height)
    : rows(height), columns(width), grid(width * height), dist(0, 4)
{
    random_device rd;
    auto seed_data = array<int, mt19937::state_size> {};
    generate(begin(seed_data), end(seed_data), ref(rd));
    seed_seq seq(cbegin(seed_data), cend(seed_data));
    mt.seed(seq);
}

void Universe::run(const Seed s, const int generations, const chrono::milliseconds ms) {
    reset();
    initialize(s);
    display();

    int i = 0;
    do {
        next_generation();
        display();

        this_thread::sleep_for(ms);
    } while(i++ < generations || generations == 0);
}

void Universe::next_generation() {
    vector<unsigned char> new_grid(grid.size());

    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < columns; c++) {
            auto count = count_neighbors(r, c);

            if (cell(c, r) == alive) {
                new_grid[r * columns + c] = (count == 2 || count == 3) ? alive : dead;
            } else {
                new_grid[r * columns + c] = (count == 3) ? alive : dead;
            }
        }
    }

    grid.swap(new_grid);
}

void Universe::reset_display() const {
    system("clear");
}

void Universe::display() {
    reset_display();
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < columns; c++) {
            cout << (cell(c, r) ? '*' : ' ');
        }
        cout << endl;
    }
}

void Universe::initialize(Seed const s) {
    if (s == Seed::ten_cell_row) {
        for (size_t c = columns / 2 - 5; c < columns / 2 + 5; c++) {
            cell(c, rows / 2) = alive;
        }
    } else {
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < columns; c++) {
                cell(c, r) = dist(mt) == 0 ? alive : dead;
            }
        }
    }
}

void Universe::reset() {
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < columns; c++) {
            cell(c, r) = dead;
        }
    }
}

int Universe::count_alive() const {
    return 0;
}


template<typename T1, typename... T>
auto Universe::count_alive(T1 s, T... ts) const {
    return s + count_alive(ts...);
}

int Universe::count_neighbors(const size_t row, const size_t col) {
    if (row == 0 && col == 0)
        return count_alive(cell(1,0), cell(1,1), cell(0,1));
    if (row == 0 && col == columns - 1)
        return count_alive(cell(columns - 2, 0), cell(columns - 2, 1), cell(columns - 1, 1));
    if (row == rows - 1 && col == 0)
        return count_alive(cell(0, rows - 2), cell(1, rows - 2), cell(1, rows - 1));
    if (row == rows - 1 && col == columns - 1)
        return count_alive(cell(columns - 1, rows - 2), cell(columns - 2, rows - 2), cell(columns - 2, rows - 1));
    if (row == 0 && col > 0 && col < columns - 1)
        return count_alive(cell(col - 1, 0), cell(col - 1, 1), cell(col, 1), cell(col + 1, 1), cell(col + 1, 0));
    if (row == rows - 1 && col > 0 && col < columns - 1)
        return count_alive(cell(col - 1, row), cell(col - 1, row - 1), cell(col, row - 1), cell(col + 1, row - 1), cell(col + 1, row));
    if (col == 0 && row > 0 && row < rows - 1)
        return count_alive(cell(0, row - 1), cell(1, row - 1), cell(1, row), cell(1, row + 1), cell(0, row + 1));
    if (col == columns - 1 && row > 0 && row < rows - 1)
        return count_alive(cell(col, row - 1), cell(col - 1, row - 1), cell(col - 1, row), cell(col - 1, row + 1), cell(col, row + 1));

    return count_alive(cell(col - 1, row - 1), cell(col, row - 1),
                       cell (col + 1, row - 1), cell(col + 1, row),
                       cell(col + 1, row + 1), cell(col, row + 1),
                       cell (col - 1, row + 1), cell(col - 1, row));
}

unsigned char & Universe::cell(const size_t col, const size_t row) {
    return grid[row * columns + col];
}