#include "utils/Common.h"

namespace funk
{

String read_file(const String& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) { throw std::runtime_error("Failed to open file: " + filename); }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

} // namespace funk
