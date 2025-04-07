#include "utils/Common.h"
#include "utils/Exception.h"

namespace funk
{

String read_file(const String& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) { throw FileError("Failed to open file: " + filename); }
    std::stringstream buffer;
    buffer << file.rdbuf() << '\n';
    return buffer.str();
}

} // namespace funk
