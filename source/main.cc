#include "lexer/Lexer.h"
#include "logging/LogMacros.h"
#include "utils/ArgParser.h"
#include "utils/Common.h"

using namespace funk;

HashMap<String, String> options{
    {"--help", "Display this help message"},
    {"--log <file>", "Set the log file"},
};

int main(int argc, char* argv[])
{
    ArgParser parser(argc, argv);

    // Print help message
    if (argc == 1 || parser.has_option("--help"))
    {
        cout << ArgParser::help("funk [options] <file>", options) << "\n";
        return 0;
    }

    // Set log file if specified
    if (parser.has_option("--log"))
    {
        if (!parser.has_value("--log"))
        {
            cerr << "No log file specified!\n";
            return 1;
        }

        logger().set_file(parser.get_option("--log"));
    }

    // Check if any files were specified
    if (!parser.has_files())
    {
        cerr << "No files specified!\n";
        return 1;
    }

    // Lex each file
    for (const auto& file : parser.get_files())
    {
        LOG_INFO("Lexing file: " + file);
        Lexer lexer(read_file(file), file);
        for (const auto& token : lexer.tokenize()) { LOG_DEBUG(token); }
        LOG_INFO("Finished lexing file: " + file);
    }

    return 0;
}
