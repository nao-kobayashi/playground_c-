#include <iostream>
#include "include/uuid.h"
#include <filesystem>
#include <fstream>
#include <random>

using namespace std;
using namespace uuids;
using namespace filesystem;

class logger {
    path log_path;
    std::ofstream log_file;
public:
    logger() {
        random_device seed_gen;
        mt19937 mt(seed_gen());
        auto name = to_string(uuid_random_generator(mt)());
        log_path = temp_directory_path() / (name + ".tmp");
        cout << log_path << endl;
        log_file.open(log_path.c_str(), ios::out | ios::trunc);
    }

    ~logger() noexcept {
        try {
            if (log_file.is_open())
                log_file.close();

            if (log_path.empty())
                remove(log_path);

        } catch (...) {
        }
    }

    void persist(const path &path) {
        log_file.close();
        rename(log_path, path);
        log_path.clear();
    }

    logger& operator<<(const string &message) {
        log_file << message << '\n';
        return *this;
    }
};

int main() {
    logger log;
    try {
        log << "This is a line." << "and this is another one.";
        throw runtime_error("error");
    } catch (...) {
        log.persist(R"(./last.log)");
    }
}
