/**
 * @file Lexer.h
 * @brief Definition of the Lexer class for lexical analysis in the Funk language
 * This file defines the Lexer class which performs lexical analysis on
 * Funk source code, converting raw text into a stream of tokens.
 */
#pragma once

#include "token/Token.h"
#include "utils/Common.h"

namespace funk
{
/**
 * @brief Class responsible for lexical analysis in the Funk language
 * The Lexer breaks down source code into tokens by scanning the input
 * character by character and recognizing patterns defined by the language
 * syntax. It tracks source locations to provide context for error reporting.
 */
class Lexer
{
public:
    /**
     * @brief Constructs a lexer for the given source code
     * @param source The source code to tokenize
     * @param filename The name of the file being processed (for error reporting)
     */
    Lexer(const String& source, const String& filename);

    /**
     * @brief Tokenizes the entire source code into a vector of tokens
     * @return Vector<Token> All tokens found in the source
     */
    Vector<Token> tokenize();

    /**
     * @brief Advances the lexer and returns the next token
     * @return Token The next token in the source
     */
    Token next_token();

    /**
     * @brief Resets the lexer to the beginning of the source
     */
    void reset();

    /**
     * @brief Resets the current line and moves the index to the beginning of the line
     */
    void reset_line();

private:
    const String source;   ///< The source code being tokenized
    const String filename; ///< The name of the source file

    int index{0};  ///< Current index in the source string
    int line{1};   ///< Current line number
    int column{1}; ///< Current column number

    int token_start_col{1}; ///< Column where the current token starts

    /**
     * @brief Advances the index and returns the character at the new index
     * @return char The next character
     */
    char next();

    /**
     * @brief Returns the character at the current index without advancing
     * @return char The current character
     */
    char peek() const;

    /**
     * @brief Returns the character at the next index without advancing
     * @return char The next character
     */
    char peek_next() const;

    /**
     * @brief Returns the character at the previous index
     * @return char The previous character
     */
    char peek_prev() const;

    /**
     * @brief Checks if the end of the source has been reached
     * @return bool True if the lexer has reached the end of the source
     */
    bool done() const;

    /**
     * @brief Checks if the next character matches the expected one, and advances if it does
     * @param expected The character to check for
     * @return bool True if the next character matched and the index was advanced
     */
    bool match(char expected);

    /**
     * @brief Skips whitespace characters (spaces, tabs, newlines)
     */
    void skip_whitespace();

    /**
     * @brief Processes and returns a number token (numb or real)
     * @return Token The recognized number token
     */
    Token get_number();

    /**
     * @brief Processes and returns an identifier or keyword token
     * @return Token The recognized identifier or keyword token
     */
    Token get_identifier();

    /**
     * @brief Processes and returns a text (string) token
     * @return Token The recognized text token
     */
    Token get_text();

    /**
     * @brief Processes and returns a character token
     * @return Token The recognized character token
     */
    Token get_char();

    /**
     * @brief Processes and returns a comment token
     * @return Token The recognized comment token
     */
    Token get_comment();

    /**
     * @brief Checks if a character is a digit (0-9)
     * @param c The character to check
     * @return bool True if the character is a digit
     */
    bool is_digit(char c) const;

    /**
     * @brief Checks if a character is alphabetic (a-z, A-Z)
     * @param c The character to check
     * @return bool True if the character is alphabetic
     */
    bool is_alpha(char c) const;

    /**
     * @brief Checks if a character is alphanumeric (a-z, A-Z, 0-9)
     * @param c The character to check
     * @return bool True if the character is alphanumeric
     */
    bool is_alphanumeric(char c) const;

    /**
     * @brief Creates a new token with the given properties
     * @param lexeme The raw text of the token
     * @param type The token type
     * @return Token The created token
     */
    Token make_token(const String& lexeme, TokenType type) const;

    /**
     * @brief Creates a new token with the given properties and value
     * @param lexeme The raw text of the token
     * @param type The token type
     * @param value The interpreted value of the token
     * @return Token The created token
     */
    Token make_token(const String& lexeme, TokenType type, TokenValue value) const;

    /**
     * @brief Creates an error token with the given message
     * @param lexeme The lexeme that caused the error
     * @param message The error message
     * @return Token An error token with the relevant information
     */
    Token error_token(const String& lexeme, const String& message) const;
};
} // namespace funk
