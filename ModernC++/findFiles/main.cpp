#include <iostream>
#include <vector>
#include <filesystem>
#include <regex>

using namespace std;
using namespace filesystem;

vector<directory_entry> find_files(const path &path, const string &s_regex) {
    vector<directory_entry> result;
    regex rx(s_regex.c_str());

    copy_if(
        recursive_directory_iterator(path),
        recursive_directory_iterator(),
        back_inserter(result),
        [&rx](const directory_entry &entry) {
            return is_regular_file(entry.path()) && regex_match(entry.path().filename().string(), rx);
        });

    return result;
}

int main() {
    path dir = R"(/Users/masanao/src/C++)";
    auto pattern = R"(.*cpp)";

    try {
        auto result = find_files(dir, pattern);
        for (auto const &entry : result) {
            cout << entry.path().string() << endl;
        }
    } catch (filesystem_error ex) {
        cout << "Exception occur" << endl;
        cout << ex.what() << endl;
    }

    return 0;
}
