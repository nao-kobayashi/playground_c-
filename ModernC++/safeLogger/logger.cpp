#include <iostream>
#include "logger.h"

logger &logger::instance() {
    static logger lg;
    return lg;
}

void logger::log(const std::string_view &message) {
    std::lock_guard<std::mutex> lock(mt);
    std::cout << "LOG: " << message << std::endl;
}