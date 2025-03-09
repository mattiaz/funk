#include "utils/ArgParser.h"

namespace funk
{

ArgParser::ArgParser(int argc, char* argv[])
{
    for (int i{1}; i < argc; ++i)
    {
        String arg{argv[i]};

        if (arg.substr(0, 2) == "--")
        {
            if (i + 1 < argc && argv[i + 1][0] != '-')
            {
                options[arg] = argv[i + 1];
                ++i;
            }
            else { options[arg] = ""; }
        }
        else { files.push_back(arg); }
    }
}

String ArgParser::help(const String& usage, const HashMap<String, String>& arguments)
{
    std::ostringstream message;
    message << "Usage: " << usage << "\n";

    int max_length{0};
    for (const auto& [arg, desc] : arguments) { max_length = std::max(max_length, static_cast<int>(arg.length())); }
    for (const auto& [arg, desc] : arguments)
    {
        message << "  " << arg << std::string(max_length - arg.length() + 2, ' ') << desc << "\n";
    }

    return message.str();
}

bool ArgParser::has_option(const String& option) const
{
    return options.find(option) != options.end();
}

bool ArgParser::has_value(const String& option) const
{
    return !options.at(option).empty();
}

String ArgParser::get_option(const String& option) const
{
    return options.at(option);
}

bool ArgParser::has_files() const
{
    return !files.empty();
}

Vector<String> ArgParser::get_files() const
{
    return files;
}

} // namespace funk
