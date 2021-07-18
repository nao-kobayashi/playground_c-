#include <array>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Weasel.h"

Weasel::Weasel(string_view t)
    : target(t), chardist(0, 26), ratedist(0, 100) {
    random_device rd;
    auto seed_data = array<int, mt19937::state_size> {};
    generate(begin(seed_data), end(seed_data), ref(rd));
    seed_seq seq(cbegin(seed_data), cend(seed_data));
    mt.seed(seq);
}

void Weasel::run(const int copies) {
    auto parent = make_random();
    int step = 1;
    cout << left << setw(5) << setfill(' ') << step << parent << endl;

    do {
        vector<string> children;
        generate_n(back_inserter(children), copies,
            [parent, this]() { return mutate(parent, 5); }
        );

//        cout << "dump children" << endl;
//        for (auto c : children) {
//            cout << c;
//        }
//        cout << endl;

        parent = *max_element(cbegin(children), cend(children),
            [this](string_view c1, string_view c2) {
                return fitness(c1) < fitness(c2);
            }
        );
        cout << setw(5) << setfill(' ') << step << parent << endl;
        step++;
    } while (parent != target);
}

int Weasel::fitness(string_view candidate) {
    int score = 0;
    for (size_t i = 0; i < candidate.size(); i++) {
        if (candidate[i] == target[i])
            score++;
    }
    return score;
}

string Weasel::mutate(string_view parent, const double rate) {
    stringstream ss;
    for (const auto c: parent) {
        auto nc = ratedist(mt) > rate ? c: allowed_chars[chardist(mt)];
        ss << nc;
    }

    return ss.str();
}

string Weasel::make_random() {
    stringstream ss;
    for(size_t i = 0; i < target.size(); i++) {
        ss << allowed_chars[chardist(mt)];
    }
    return ss.str();
}