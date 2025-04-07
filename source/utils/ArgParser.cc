#include "utils/ArgParser.h"

namespace funk
{

ArgParser::ArgParser(int argc, char* argv[])
{
    for (int i{1}; i < argc; ++i)
    {
        String arg{argv[i]};

        if (!file.empty())
        {
            args.push_back(arg);
            continue;
        }

        if (arg.substr(0, 2) == "--")
        {
            size_t eq_pos = arg.find('=');
            if (eq_pos != String::npos) { options[arg.substr(0, eq_pos)] = arg.substr(eq_pos + 1); }
            else { options[arg] = ""; }
        }
        else { file = arg; }
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

bool ArgParser::has_file() const
{
    return !file.empty();
}

String ArgParser::get_file() const
{
    return file;
}

Vector<String> ArgParser::get_args() const
{
    return args;
}

} // namespace funk
