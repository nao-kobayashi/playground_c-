#include <iostream>
#include <filesystem>
#include <numeric>

using namespace std;
using namespace filesystem;

uintmax_t get_directory_size(const path &dir, bool follow_symlinks = false) {
    auto iterator = recursive_directory_iterator(
            dir,
            follow_symlinks
                ? directory_options::follow_directory_symlink
                : directory_options::none
        );

    return accumulate(begin(iterator), end(iterator), 0ULL,
        [](const uintmax_t total, const directory_entry &entry) {
            return total + (is_regular_file(entry) ? file_size(entry.path()) : 0ULL);
        });
}

int main() {
    string dir;
    cout << "Path: ";
    cin >> dir;

    cout << "Size: " << get_directory_size(dir) << endl;
    return 0;
}
