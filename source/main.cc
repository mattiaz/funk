#include "logging/LogMacros.h"
#include "parser/Parser.h"
#include "utils/ArgParser.h"
#include "utils/Common.h"

using namespace funk;

// Command line options
HashMap<String, String> options{
    {"--help", "Display this help message"},
    {"--log <file>", "Set the log file"},
    {"--debug", "Enable debug logging"},
    {"--ast", "Log the AST representation"},
    {"--tokens", "Log the lexical tokens"},
};

// Configuration for command line options
struct Config
{
    bool debug{false};
    bool ast{false};
    bool tokens{false};
};

// Process command line arguments and set up logging
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

// Process a single file
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

        if (config.ast) { LOG_INFO("AST: " + ast->to_s()); }

        LOG_DEBUG("Evaluating AST...");
        Node* res{ast->evaluate()};
        LOG_DEBUG("AST evaluated!");
        LOG_INFO("Result: " + res->to_s());
    }
    catch (const FunkError& e)
    {
        LOG_ERROR("Error processing file " + file + ": " + e.what());
        cerr << "Error: " << e.trace() << '\n';
    }
}

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
