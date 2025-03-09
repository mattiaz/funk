#pragma once
#include "utils/Common.h"

namespace funk
{

class ArgParser
{
public:
    ArgParser(int argc, char* argv[]);
    ~ArgParser() = default;

    static String help(const String& usage, const HashMap<String, String>& arguments);

    bool has_option(const String& option) const;
    bool has_value(const String& option) const;
    String get_option(const String& option) const;
    bool has_files() const;
    Vector<String> get_files() const;

private:
    HashMap<String, String> options;
    Vector<String> files;
};

} // namespace funk
