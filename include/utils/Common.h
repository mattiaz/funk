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
#include <stdexcept>

using std::cerr;
using std::cout;

namespace funk
{

using String = std::string;

template <typename T> using Vector = std::vector<T>;
template <typename K, typename V> using HashMap = std::unordered_map<K, V>;

struct SourceLocation
{
    String filename;
    int line;
    int column;

    SourceLocation(const String& filename, int line, int column) : filename(filename), line(line), column(column) {}
};

String read_file(const String& filename);

} // namespace funk
