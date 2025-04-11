#include "logging/Logger.h"

namespace funk
{

Logger::Logger() : log_path("funk.log"), log_level(LogLevel::INFO)
{
    file_open();
}

Logger::~Logger()
{
    if (log_file.is_open()) { log_file.close(); }
}

Logger& Logger::instance()
{
    static Logger instance;
    return instance;
}

void Logger::log(LogLevel level, const std::string& message)
{
    if (level < log_level) return;

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::string level_str;
    switch (level)
    {
    case LogLevel::DEBUG: level_str = "DEBUG"; break;
    case LogLevel::INFO: level_str = "INFO "; break;
    case LogLevel::WARN: level_str = "WARN "; break;
    case LogLevel::ERROR: level_str = "ERROR"; break;
    case LogLevel::FATAL: level_str = "FATAL"; break;
    }

    log_file << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << "] [" << level_str << "] "
             << message << std::endl;

    log_file.flush();

    if (level == LogLevel::FATAL)
    {
        log_file.close();
        std::exit(EXIT_FAILURE);
    }
}

void Logger::set_file(const std::string& path)
{
    if (log_file.is_open()) { log_file.close(); }
    log_path = path;
    file_open();
}

std::string Logger::get_file() const
{
    return log_path;
}

void Logger::set_level(LogLevel level)
{
    log_level = level;
}

LogLevel Logger::get_level() const
{
    return log_level;
}

void Logger::file_open()
{
    if (log_file.is_open()) return;
    log_file.open(log_path, std::ios::app);
    if (!log_file.is_open()) { std::cerr << "ERROR: Could not open log file '" << log_path << "'.\n"; }
}

} // namespace funk
