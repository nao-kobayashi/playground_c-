#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

double truncated_mean(vector<int> values, const double percentage) {
    sort(begin(values), end(values));
    auto remove_count = static_cast<size_t>(values.size() * percentage + 0.5);

    values.erase(begin(values), begin(values) + remove_count);
    values.erase(end(values) - remove_count, end(values));

    auto total = accumulate(cbegin(values), cend(values), 0ULL);

    cout << total << " " << values.size() << endl;
    return static_cast<double>(total / values.size());
}

struct Movie {
    int id;
    string title;
    vector<int> ratings;
};

void print_movie_ratings(const vector<Movie> &movies) {
    for (const auto &movie: movies) {
        cout << movie.title << '\t' << truncated_mean(movie.ratings, 0.05) << endl;
    }
}

int main() {
    vector<Movie> movies {
        {101, "The Matrix", {10, 9, 10, 9, 9, 8, 7, 10, 9, 9, 9, 8, 10}},
        {102, "Gladiator", {10, 5, 7, 8, 9, 8, 9, 9, 10, 5, 9, 8, 10}},
        {103, "Interstellar", {10, 5, 6, 9, 3, 8, 8, 9, 6, 4, 7, 10}}
    };

    print_movie_ratings(movies);
    return 0;
}
