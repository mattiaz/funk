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
     * @brief Checks if an input file was provided.
     * @return True if an input file was provided
     */
    bool has_file() const;

    /**
     * @brief Gets the path to the input file.
     * @return Path to the input file, empty if no file was provided
     */
    String get_file() const;

    /**
     * @brief Gets the list of arguments passed to the program.
     * @return Vector of argument strings, excluding the program name and input file
     */
    Vector<String> get_args() const;

private:
    HashMap<String, String> options; ///< Map of options and their values
    String file;                     ///< Path to the input file
    Vector<String> args;             ///< List of arguments passed to the program
};

} // namespace funk
