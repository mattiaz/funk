#include "lexer/Lexer.h"

namespace funk
{

static const HashMap<String, TokenType> keywords = {
    {"funk", TokenType::FUNK},
    {"data", TokenType::DATA},
    {"mut", TokenType::MUT},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"match", TokenType::MATCH},
    {"case", TokenType::CASE},
    {"none", TokenType::NONE},
    {"return", TokenType::RETURN},
    {"include", TokenType::INCLUDE},

    {"numb", TokenType::NUMB_TYPE},
    {"real", TokenType::REAL_TYPE},
    {"bool", TokenType::BOOL_TYPE},
    {"char", TokenType::CHAR_TYPE},
    {"text", TokenType::TEXT_TYPE},

    {"true", TokenType::BOOL},
    {"false", TokenType::BOOL},
};

Lexer::Lexer(const String& source, const String& filename) : source(source), filename(filename) {}

Vector<Token> Lexer::tokenize()
{
    Vector<Token> tokens{};
    while (!done()) { tokens.push_back(next_token()); }
    return tokens;
}

Token Lexer::next_token()
{
    skip_whitespace();
    token_start_col = column;

    if (done()) { return make_token("", TokenType::EOF_TOKEN); }

    char c{peek()};

    if (is_digit(c)) { return get_number(); }
    else if (is_alpha(c)) { return get_identifier(); }
    else if (c == '"') { return get_text(); }
    else if (c == '\'') { return get_char(); }
    else if (c == '#') { return get_comment(); }

    next();
    String lexeme{c};

    switch (c)
    {
    case '(': return make_token(lexeme, TokenType::L_PAR);
    case ')': return make_token(lexeme, TokenType::R_PAR);
    case '{': return make_token(lexeme, TokenType::L_BRACE);
    case '}': return make_token(lexeme, TokenType::R_BRACE);
    case '[': return make_token(lexeme, TokenType::L_BRACKET);
    case ']': return make_token(lexeme, TokenType::R_BRACKET);
    case ',': return make_token(lexeme, TokenType::COMMA);
    case '.': return make_token(lexeme, TokenType::DOT);
    case ';': return make_token(lexeme, TokenType::SEMICOLON);
    case '%': return make_token(lexeme, TokenType::MODULO);
    case '^': return make_token(lexeme, TokenType::POWER);

    case '+':
        if (match('=')) { return make_token(lexeme + '=', TokenType::PLUS_ASSIGN); }
        return make_token(lexeme, TokenType::PLUS);

    case '-':
        if (match('=')) { return make_token(lexeme + '=', TokenType::MINUS_ASSIGN); }
        return make_token(lexeme, TokenType::MINUS);

    case '*':
        if (match('=')) { return make_token(lexeme + '=', TokenType::MULTIPLY_ASSIGN); }
        return make_token(lexeme, TokenType::MULTIPLY);

    case '/':
        if (match('=')) { return make_token(lexeme + '=', TokenType::DIVIDE_ASSIGN); }
        return make_token(lexeme, TokenType::DIVIDE);

    case '!':
        if (match('=')) { return make_token(lexeme + '=', TokenType::NOT_EQUAL); }
        return make_token(lexeme, TokenType::NOT);

    case '=':
        if (match('=')) { return make_token(lexeme + '=', TokenType::EQUAL); }
        return make_token(lexeme, TokenType::ASSIGN);

    case '<':
        if (match('=')) { return make_token(lexeme + '=', TokenType::LESS_EQUAL); }
        return make_token(lexeme, TokenType::LESS);

    case '>':
        if (match('=')) { return make_token(lexeme + '=', TokenType::GREATER_EQUAL); }
        if (match('>')) { return make_token(lexeme + '>', TokenType::PIPE); }
        return make_token(lexeme, TokenType::GREATER);

    case '&':
        if (match('&')) { return make_token(lexeme + '&', TokenType::AND); }
        return error_token(lexeme, "Expected '&' after '&'");

    case '|':
        if (match('|')) { return make_token(lexeme + '|', TokenType::OR); }
        return error_token(lexeme, "Expected '|' after '|'");
    }

    return error_token(lexeme, "Unexpected character");
}

void Lexer::reset()
{
    index = 0;
    line = 1;
    column = 1;
}

void Lexer::reset_line()
{
    index -= column - 1;
    column = 1;
}

char Lexer::next()
{
    index++;
    column++;
    return source[index - 1];
}

char Lexer::peek() const
{
    if (done()) { return '\0'; }
    return source[index];
}

char Lexer::peek_next() const
{
    if (index + 1 >= static_cast<int>(source.length())) { return '\0'; }
    return source[index + 1];
}

char Lexer::peek_prev() const
{
    if (index - 1 < 0) { return '\0'; }
    return source[index - 1];
}

bool Lexer::done() const
{
    return index >= static_cast<int>(source.length());
}

bool Lexer::match(char expected)
{
    if (done() || source[index] != expected) { return false; }
    index++;
    column++;
    return true;
}

void Lexer::skip_whitespace()
{
    while (true)
    {
        switch (peek())
        {
        case ' ':
        case '\r':
        case '\t': next(); break;
        case '\n':
            line++;
            next();
            column = 1;
            break;
        default: return;
        }
    }
}

Token Lexer::get_number()
{
    String lexeme;
    // Check for digits
    while (is_digit(peek())) { lexeme += next(); }

    // Check if a decimal number
    if (peek() == '.' && is_digit(peek_next()))
    {
        // Add decimal point
        lexeme += next();
        // Check for digits after decimal point
        while (is_digit(peek())) { lexeme += next(); }
        // Convert to double as the value
        return make_token(lexeme, TokenType::REAL, std::stod(lexeme));
    }

    // Convert to int as the value
    return make_token(lexeme, TokenType::NUMB, std::stoi(lexeme));
}

Token Lexer::get_identifier()
{
    String lexeme;
    // Check for alphanumeric characters and underscores
    while (is_alphanumeric(peek())) { lexeme += next(); }

    // Check if found in list of keywords
    auto it = keywords.find(lexeme);
    if (it != keywords.end())
    {
        TokenType type = it->second;

        // Bool literals
        if (type == TokenType::BOOL) { return make_token(lexeme, TokenType::BOOL, lexeme == "true"); }

        return make_token(lexeme, type);
    }

    // Identifier
    return make_token(lexeme, TokenType::IDENTIFIER, lexeme);
}

Token Lexer::get_text()
{
    String lexeme;
    lexeme += next(); // Opening quote

    // Collect characters until closing quote, ignoring escape sequences
    while ((peek() != '"' || peek_prev() == '\\') && !done()) { lexeme += next(); }

    // Check for unterminated string
    if (done()) { return error_token(lexeme, "Unterminated string literal."); }

    lexeme += next(); // Closing quote

    // Remove quotes from value
    return make_token(lexeme, TokenType::TEXT, lexeme.substr(1, lexeme.length() - 2));
}

Token Lexer::get_char()
{
    String lexeme;
    lexeme += next(); // Opening quote

    if (done() || peek() == '\'') { return error_token(lexeme, "Empty character literal."); }

    char value = next();
    lexeme += value;

    if (done() || peek() != '\'') { return error_token(lexeme, "Unterminated character literal."); }

    lexeme += next(); // Closing quote
    return make_token(lexeme, TokenType::CHAR, value);
}

Token Lexer::get_comment()
{
    String lexeme;
    lexeme += next(); // Opening #

    // Multi-line comment
    if (peek() == '#')
    {
        lexeme += next(); // Add second #

        String content;
        while (!(peek() == '#' && peek_next() == '#') && !done())
        {
            content += next();
            lexeme += content.back();
        }

        if (done()) { return error_token(lexeme, "Unterminated multi-line comment."); }

        // Add closing ## to lexeme
        lexeme += next() + next();
        return make_token(lexeme, TokenType::COMMENT, content);
    }
    // Single-line comment
    else
    {
        String content;
        while (peek() != '\n' && !done())
        {
            content += next();
            lexeme += content.back();
        }
        return make_token(lexeme, TokenType::COMMENT, content);
    }
}

bool Lexer::is_digit(char c) const
{
    return c >= '0' && c <= '9';
}

bool Lexer::is_alpha(char c) const
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::is_alphanumeric(char c) const
{
    return is_digit(c) || is_alpha(c);
}

Token Lexer::make_token(const String& lexeme, TokenType type) const
{
    return Token(SourceLocation(filename, line, token_start_col), lexeme, type);
}

Token Lexer::make_token(const String& lexeme, TokenType type, TokenValue value) const
{
    return Token(SourceLocation(filename, line, token_start_col), lexeme, type, value);
}

Token Lexer::error_token(const String& lexeme, const String& message) const
{
    return Token(SourceLocation(filename, line, token_start_col), lexeme, TokenType::ERROR, message);
}
} // namespace funk
