/**
 * @file Logger.h
 * @brief Definition of the Logger class
 * This file defines the Logger class which provides logging capabilities
 * throughout the Funk interpreter. It implements the singleton pattern to
 * ensure a single logging instance is used across the application.
 */
#pragma once

#include "utils/Common.h"
#include <chrono>

namespace funk
{

/**
 * @brief Enumeration of log severity levels
 * Defines the different severity levels for log messages, from
 * least severe (DEBUG) to most severe (FATAL).
 */
enum class LogLevel
{
    DEBUG, ///< Detailed information for debugging purposes
    INFO,  ///< General information about system operation
    WARN,  ///< Warning conditions that should be addressed
    ERROR, ///< Error conditions that prevent normal operation
    FATAL  ///< Critical errors that cause the application to terminate
};

/**
 * @brief Singleton logger class
 * The Logger class provides logging functionality throughout the Funk interpreter.
 * It implements the singleton pattern to ensure that only one logger instance
 * exists during the lifetime of the application.
 */
class Logger
{
public:
    /**
     * @brief Returns a reference to the singleton logger instance
     * @return Logger& Reference to the singleton logger instance
     */
    static Logger& instance();

    /**
     * @brief Logs a message with the specified severity level
     * @param level The severity level of the message
     * @param message The message to log
     */
    void log(LogLevel level, const std::string& message);

    /**
     * @brief Sets the log file path
     * @param filePath Path to the log file
     */
    void set_file(const std::string& filePath);

    /**
     * @brief Gets the current log file path
     * @return std::string The current log file path
     */
    std::string get_file() const;

private:
    /**
     * @brief Private constructor to prevent instantiation
     * Part of the singleton pattern implementation.
     */
    Logger();

    /**
     * @brief Private destructor to prevent deletion
     * Part of the singleton pattern implementation.
     */
    ~Logger();

    /**
     * @brief Deleted copy constructor to prevent copying
     * Part of the singleton pattern implementation.
     */
    Logger(const Logger&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying
     * Part of the singleton pattern implementation.
     */
    Logger& operator=(const Logger&) = delete;

    /**
     * @brief Opens the log file
     * Opens the file specified by log_path for writing log messages.
     */
    void file_open();

    std::string log_path;   ///< Path to the log file
    std::ofstream log_file; ///< Output stream for the log file
};

/**
 * @brief Convenience function to access the logger singleton
 * @return Logger& Reference to the singleton logger instance
 */
inline Logger& logger()
{
    return Logger::instance();
}
} // namespace funk
