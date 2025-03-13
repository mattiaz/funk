#pragma once

#include "token/TokenType.h"
#include "utils/Common.h"

namespace funk
{
using TokenValue = std::variant<int, double, bool, char, String, None>;

class Token
{
public:
    Token(const SourceLocation& loc, const String& lexeme, TokenType type);
    Token(const SourceLocation& loc, const String& lexeme, TokenType type, TokenValue value);

    TokenType get_type() const;
    String get_lexeme() const;
    TokenValue get_value() const;

    SourceLocation get_location() const;

    String to_s() const;

private:
    SourceLocation location;
    String lexeme;
    TokenType type;
    TokenValue value;

    String get_value_str() const;
};

inline std::ostream& operator<<(std::ostream& os, const Token& token)
{
    os << token.to_s();
    return os;
}

} // namespace funk
