#include <iostream>
#include <vector>
#include "logger.h"
#include <thread>
#include <random>

int main() {
    std::vector<std::thread> modules;

    for (int id = 1; id <= 5; id++) {
        modules.emplace_back([id]() {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> ud(500, 3000);
            logger::instance().log("modules " + std::to_string(id) + " started");
            std::this_thread::sleep_for(std::chrono::milliseconds(ud(mt)));
            logger::instance().log("modules " + std::to_string(id) + " finished");
        });
    }

    for (auto & m : modules) {
        m.join();
    }

    return 0;
}
