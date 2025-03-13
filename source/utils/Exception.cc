#include "utils/Exception.h"

namespace funk
{

FunkError::FunkError(const SourceLocation& loc, const String& type, const String& message) :
    std::runtime_error(message), type(type), location(loc)
{
}

const SourceLocation& FunkError::get_location() const
{
    return location;
}

String FunkError::trace() const
{
    std::ostringstream os;
    os << type << " in file " << location.filename << " at line " << location.line << ", column " << location.column
       << '\n';

    String source = read_file(location.filename);
    std::istringstream stream(source);
    String line;

    for (int i = 1; i < location.line && std::getline(stream, line); i++) {}

    if (std::getline(stream, line))
    {
        os << "    " << line << '\n' << "    " << String(location.column - 1, ' ') << "^\n";
    }

    os << what() << '\n';

    return os.str();
}
} // namespace funk
