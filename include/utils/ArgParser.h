/**
 * @file ArgParser.h
 * @brief Simple command-line argument parser for the Funk language.
 */
#pragma once
#include "utils/Common.h"

namespace funk
{

/**
 * @brief Parses and manages command-line arguments.
 * Provides functionality to access options, values, and input files from command-line arguments.
 */
class ArgParser
{
public:
    /**
     * @brief Constructs a parser from command-line arguments.
     * @param argc Number of arguments
     * @param argv Array of argument strings
     */
    ArgParser(int argc, char* argv[]);

    /**
     * @brief Default destructor.
     */
    ~ArgParser() = default;

    /**
     * @brief Generates a help message with program usage information.
     * @param usage Usage string to display
     * @param arguments Map of argument descriptions
     * @return Formatted help message
     */
    static String help(const String& usage, const HashMap<String, String>& arguments);

    /**
     * @brief Checks if an option was provided.
     * @param option The option to check for
     * @return True if the option was provided
     */
    bool has_option(const String& option) const;

    /**
     * @brief Checks if an option has an associated value.
     * @param option The option to check
     * @return True if the option has a value
     */
    bool has_value(const String& option) const;

    /**
     * @brief Gets the value of an option.
     * @param option The option to get the value for
     * @return The option's value
     */
    String get_option(const String& option) const;

    /**
     * @brief Checks if any input files were provided.
     * @return True if input files were provided
     */
    bool has_files() const;

    /**
     * @brief Gets the list of input files.
     * @return Vector of input file paths
     */
    Vector<String> get_files() const;

private:
    HashMap<String, String> options; ///< Map of options and their values
    Vector<String> files;            ///< List of input files
};

} // namespace funk
