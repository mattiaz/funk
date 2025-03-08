#pragma once

#include "logging/Logger.h"

//
//  Macros for logging, using the singleton instance of the Logger class.
//  Converts the given object to a string using an ostringstream.
//

#define FUNK_LOG_STREAM(obj) (static_cast<std::ostringstream&>(std::ostringstream().flush() << obj).str())

#define LOG_DEBUG(message) funk::logger().log(funk::LogLevel::DEBUG, FUNK_LOG_STREAM(message))

#define LOG_INFO(message) funk::logger().log(funk::LogLevel::INFO, FUNK_LOG_STREAM(message))

#define LOG_WARN(message) funk::logger().log(funk::LogLevel::WARN, FUNK_LOG_STREAM(message))

#define LOG_ERROR(message) funk::logger().log(funk::LogLevel::ERROR, FUNK_LOG_STREAM(message))

#define LOG_FATAL(message) funk::logger().log(funk::LogLevel::FATAL, FUNK_LOG_STREAM(message))
