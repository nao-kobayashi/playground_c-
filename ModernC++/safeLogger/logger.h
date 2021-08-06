#ifndef SAFELOGGER_LOGGER_H
#define SAFELOGGER_LOGGER_H

#include <string_view>
#include <mutex>

class logger {
protected:
    logger() = default;
public:
    static logger& instance();

    logger(logger const &) = delete;
    logger& operator=(logger const &) = delete;

    void log(std::string_view const & message);
private:
    std::mutex mt;
};

#endif //SAFELOGGER_LOGGER_H
