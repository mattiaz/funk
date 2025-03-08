#pragma once

#include "utils/Common.h"
#include <chrono>

namespace funk
{

enum class LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class Logger
{
public:
    static Logger& instance();                            // Return a reference to the singleton instance
    void log(LogLevel level, const std::string& message); // Log a message with the given level
    void set_file(const std::string& filePath);           // Set the log file path
    std::string get_file() const;                         // Return the log file path

private:
    Logger();  // Private constructor to prevent instantiation
    ~Logger(); // Private destructor to prevent deletion

    Logger(const Logger&) = delete;            // Delete the copy constructor to prevent copying
    Logger& operator=(const Logger&) = delete; // Delete the copy assignment operator to prevent copying
    void file_open();                          // Open the log file

    std::string log_path;
    std::ofstream log_file;
};

inline Logger& logger()
{
    return Logger::instance(); // Return a reference to the singleton instance
}
} // namespace funk
