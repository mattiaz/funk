#pragma once

#include "token/TokenType.h"
#include "utils/Common.h"

namespace funk
{
using TokenValue = std::variant<std::monostate, int, double, bool, char, String>;

class Token
{
public:
    Token(const String& filename, int line, int column, const String& lexeme, TokenType type);
    Token(const String& filename, int line, int column, const String& lexeme, TokenType type, TokenValue value);

    TokenType get_type() const;
    String get_lexeme() const;
    TokenValue get_value() const;

    int get_line() const;
    int get_column() const;
    String get_filename() const;

    String to_s() const;

private:
    TokenType type;
    String lexeme;
    TokenValue value;

    int line;
    int column;
    String filename;

    String get_value_str() const;
};

inline std::ostream& operator<<(std::ostream& os, const Token& token)
{
    os << token.to_s();
    return os;
}

} // namespace funk
