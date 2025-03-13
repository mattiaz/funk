/**
 * @file LogMacros.h
 * @brief Defines logging macros for the Funk programming language.
 * This file provides a set of convenient macros that simplify logging throughout the Funk interpreter.
 */
#pragma once

#include "logging/Logger.h"

/**
 * @brief Helper macro that converts any streamable object to a string.
 * Creates a temporary ostringstream, streams the object into it, and returns the resulting string.
 * @param obj Any object that can be streamed to an ostringstream
 */
#define FUNK_LOG_STREAM(obj) (static_cast<std::ostringstream&>(std::ostringstream().flush() << obj).str())

/**
 * @brief Logs a debug message.
 * @param message The message to log (can be any streamable object)
 */
#define LOG_DEBUG(message) funk::logger().log(funk::LogLevel::DEBUG, FUNK_LOG_STREAM(message))

/**
 * @brief Logs an informational message.
 * @param message The message to log (can be any streamable object)
 */
#define LOG_INFO(message) funk::logger().log(funk::LogLevel::INFO, FUNK_LOG_STREAM(message))

/**
 * @brief Logs a warning message.
 * @param message The message to log (can be any streamable object)
 */
#define LOG_WARN(message) funk::logger().log(funk::LogLevel::WARN, FUNK_LOG_STREAM(message))

/**
 * @brief Logs an error message.
 * @param message The message to log (can be any streamable object)
 */
#define LOG_ERROR(message) funk::logger().log(funk::LogLevel::ERROR, FUNK_LOG_STREAM(message))

/**
 * @brief Logs a fatal error message.
 * @param message The message to log (can be any streamable object)
 */
#define LOG_FATAL(message) funk::logger().log(funk::LogLevel::FATAL, FUNK_LOG_STREAM(message))
