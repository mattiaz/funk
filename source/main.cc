/**
 * @file main.cc
 * @brief Main entry point for the Funk language interpreter
 * This file contains the main function and supporting code for the Funk
 * language interpreter, handling command-line arguments, file processing,
 * and from lexing to evaluation.
 */

#include "logging/LogMacros.h"
#include "parser/Parser.h"
#include "utils/ArgParser.h"
#include "utils/Common.h"

using namespace funk;

/**
 * @brief Available command line options with descriptions
 * Maps option flags to their help text descriptions
 */
HashMap<String, String> options{
    {"--help", "Display this help message"},
    {"--log <file>", "Set the log file"},
    {"--debug", "Enable debug logging"},
    {"--ast", "Log the AST representation"},
    {"--tokens", "Log the lexical tokens"},
};

/**
 * @brief Runtime configuration based on command line options
 * Stores boolean flags for various runtime behaviors
 */
struct Config
{
    bool debug{false};  ///< Enable debug level logging
    bool ast{false};    ///< Print AST representation
    bool tokens{false}; ///< Print lexical tokens
};

/**
 * @brief Process command line arguments and configure the interpreter
 * @param parser The argument parser containing command line options
 * @param config The configuration to populate
 * @return bool True if setup was successful, false otherwise
 */
bool setup(ArgParser& parser, Config& config)
{
    // Print help message
    if (parser.has_option("--help"))
    {
        cout << ArgParser::help("funk [options] <file>", options) << "\n";
        return false;
    }

    // Set log file if specified
    if (parser.has_option("--log"))
    {
        if (!parser.has_value("--log"))
        {
            cerr << "No log file specified!\n";
            return false;
        }
        logger().set_file(parser.get_option("--log"));
    }

    // Configure logging level
    if (parser.has_option("--debug"))
    {
        config.debug = true;
        logger().set_level(LogLevel::DEBUG);
    }

    // Check if any files were specified
    if (!parser.has_files())
    {
        cerr << "No files specified!\n";
        return false;
    }

    // Set other configuration options
    config.ast = parser.has_option("--ast");
    config.tokens = parser.has_option("--tokens");

    return true;
}

/**
 * @brief Process a single Funk source file
 * Handles the complete execution pipeline: lexing, parsing, and evaluation
 * @param file Path to the source file
 * @param config Runtime configuration options
 */
void process_file(const String& file, const Config& config)
{
    LOG_INFO("Processing file: " + file);

    try
    {
        LOG_DEBUG("Lexing file...");
        Lexer lexer{read_file(file), file};
        Vector<Token> tokens{lexer.tokenize()};
        LOG_DEBUG("Tokens lexed!");

        if (config.tokens)
        {
            LOG_INFO("Tokens:");
            for (const auto& token : tokens) { LOG_INFO(token); }
        }

        LOG_DEBUG("Parsing file...");
        Parser parser{tokens, file};
        Node* ast = parser.parse();
        LOG_DEBUG("File parsed!");

        if (config.ast)
        {
            LOG_INFO("Abstract Syntax Tree:");
            std::istringstream stream(ast->to_s());
            String line;
            while (getline(stream, line)) { LOG_INFO(line); }
        }

        LOG_DEBUG("Evaluating AST...");
        Node* res{ast->evaluate()};
        LOG_DEBUG("AST evaluated!");
        if (!res) { LOG_INFO("Result: nullptr"); }
        else { LOG_INFO("Result: " + res->to_s()); }
    }
    catch (const FunkError& e)
    {
        LOG_ERROR("Error processing file " + file + ": " + e.what());
        cerr << "Error: " << e.trace() << '\n';
    }
}

/**
 * @brief Main entry point for the Funk interpreter
 * Parses command line arguments and processes input files
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return int Exit code (0 for success, non-zero for errors)
 */
int main(int argc, char* argv[])
{
    ArgParser parser(argc, argv);
    Config config;

    // Show help if no arguments provided
    if (argc == 1)
    {
        cout << ArgParser::help("funk [options] <file>", options) << "\n";
        return 0;
    }

    // Setup and validate arguments
    if (!setup(parser, config)) { return 1; }

    // Process each file
    for (const auto& file : parser.get_files()) { process_file(file, config); }

    return 0;
}
