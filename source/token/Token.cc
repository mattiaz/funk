#include "token/Token.h"

namespace funk
{

Token::Token(const String& filename, int line, int column, const String& lexeme, TokenType type) :
    type(type), lexeme(lexeme), value(std::monostate{}), line(line), column(column), filename(filename)
{
}

Token::Token(const String& filename, int line, int column, const String& lexeme, TokenType type, TokenValue value) :
    type(type), lexeme(lexeme), value(value), line(line), column(column), filename(filename)
{
}

TokenType Token::get_type() const
{
    return type;
}

String Token::get_lexeme() const
{
    return lexeme;
}

TokenValue Token::get_value() const
{
    return value;
}

int Token::get_line() const
{
    return line;
}

int Token::get_column() const
{
    return column;
}

String Token::get_filename() const
{
    return filename;
}

String Token::get_value_str() const
{
    std::ostringstream oss;

    if (std::holds_alternative<int>(value)) { oss << std::get<int>(value); }
    else if (std::holds_alternative<double>(value)) { oss << std::get<double>(value); }
    else if (std::holds_alternative<bool>(value)) { oss << (std::get<bool>(value) ? "true" : "false"); }
    else if (std::holds_alternative<char>(value)) { oss << "'" << std::get<char>(value) << "'"; }
    else if (std::holds_alternative<String>(value)) { oss << "\"" << std::get<String>(value) << "\""; }
    else { oss << "<no value>"; }

    return oss.str();
}

String Token::to_s() const
{
    std::ostringstream oss;
    oss << "Token(";
    oss << "type=" << token_type_to_string(type) << ", ";
    oss << "lexeme=\"" << lexeme << "\", ";

    // Include value if it's not monostate
    if (!std::holds_alternative<std::monostate>(value)) { oss << "value=" << get_value_str() << ", "; }

    oss << "line=" << line << ", ";
    oss << "column=" << column << ", ";
    oss << "file=\"" << filename << "\"";
    oss << ")";

    return oss.str();
}

} // namespace funk
