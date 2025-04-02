/**
 * @file Common.h
 * @brief Common type definitions and utilities used throughout the Funk interpreter
 */
#pragma once

#include <iomanip>
#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

#include <unordered_map>
#include <variant>
#include <vector>

#include <algorithm>

using std::cerr;
using std::cout;

namespace funk
{

/**
 * @brief Alias for std::string.
 */
using String = std::string;

/**
 * @brief Represents an empty or "none" value using std::monostate.
 */
using None = std::monostate;

/**
 * @brief Template alias for std::vector.
 * @tparam T The type of elements stored in the vector
 */
template <typename T> using Vector = std::vector<T>;

/**
 * @brief Template alias for std::unordered_map.
 * @tparam K The key type
 * @tparam V The value type
 */
template <typename K, typename V> using HashMap = std::unordered_map<K, V>;

/**
 * @brief Macro for std::to_string.
 */
#define to_str(x) std::to_string(x)

/**
 * @brief Stores location information for source code elements.
 * Used for error reporting and debugging to identify where in the source code an element appears.
 */
struct SourceLocation
{
    String filename; ///< Source file name
    int line;        ///< Line number (1-based)
    int column;      ///< Column number (1-based)

    /**
     * @brief Constructs a source location.
     * @param filename Name of the source file
     * @param line Line number
     * @param column Column number
     */
    SourceLocation(const String& filename, int line, int column) : filename(filename), line(line), column(column) {}
};

/**
 * @brief Reads the contents of a file into a string.
 * @param filename Path to the file to read
 * @return String containing the file contents
 */
String read_file(const String& filename);

} // namespace funk
