#pragma once

#include "token/Token.h"
#include "utils/Common.h"

namespace funk
{
class Lexer
{
public:
    Lexer(const String& source, const String& filename);
    Vector<Token> tokenize();
    Token next_token();

    void reset();
    void reset_line();

private:
    const String source;
    const String filename;

    int index{0};
    int line{1};
    int column{1};

    char next();               // Advance the index and return the character at the new index
    char peek() const;         // Return the character at the current index
    char peek_next() const;    // Return the character at the next index
    char peek_prev() const;    // Return the character at the previous index
    bool done() const;         // Return true if the index is at the end of the source
    bool match(char expected); // Return true if the next character matches the expected character

    void skip_whitespace(); // Advance the index until the character is not a whitespace
    Token get_number();     // Return the next number token
    Token get_identifier(); // Return the next identifier token
    Token get_text();       // Return the next text token
    Token get_char();       // Return the next char token
    Token get_comment();    // Return the next comment token

    bool is_digit(char c) const;        // Return true if the character is a digit
    bool is_alpha(char c) const;        // Return true if the character is alphabetic
    bool is_alphanumeric(char c) const; // Return true if the character is alphanumeric

    Token make_token(const String& lexeme, TokenType type) const;
    Token make_token(const String& lexeme, TokenType type, TokenValue value) const;
    Token error_token(const String& lexeme, const String& message) const;
};
} // namespace funk
