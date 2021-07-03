#include <iostream>
#include <filesystem>
#include <chrono>

using namespace std;
using namespace filesystem;
using namespace chrono;

template<typename Duration>
bool is_older_than(const path &path, const Duration duration) {
    auto f_time_duration = last_write_time(path).time_since_epoch();
    auto now_duration = (system_clock::now() - duration).time_since_epoch();
    return duration_cast<Duration>(now_duration - f_time_duration).count() > 0;
}

template<typename Duration>
void remove_files_older_than(const path &path, const Duration duration) {
    try {
        if (exists(path)) {
            if (is_regular_file(path) && is_older_than(path, duration)) {
                //remove(path);
                cout << "remove file: " << path << endl;
            } else if (is_directory(path)) {
                for (auto const &entry : directory_iterator(path)) {
                    remove_files_older_than(entry, duration);
                }
            }
        }
    } catch (const exception &ex) {
        cerr << ex.what() << endl;
    }
}

int main() {
    auto path = R"(/Users/masanao/src/C++)";
    remove_files_older_than(path, 720h);
    return 0;
}
