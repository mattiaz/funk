#include "token/Token.h"

namespace funk
{

Token::Token(const SourceLocation& loc, const String& lexeme, TokenType type) :
    location(loc), lexeme(lexeme), type(type)
{
}

Token::Token(const SourceLocation& loc, const String& lexeme, TokenType type, TokenValue value) :
    location(loc), lexeme(lexeme), type(type), value(value)
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

SourceLocation Token::get_location() const
{
    return location;
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

    oss << "line=" << location.line << ", ";
    oss << "column=" << location.column << ", ";
    oss << "file=\"" << location.filename << "\"";
    oss << ")";

    return oss.str();
}

} // namespace funk
