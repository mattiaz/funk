/**
 * @file TokenType.h
 * @brief Definition of token types
 *
 * This file defines all the token types used in the lexical analysis phase.
 */

#pragma once
#include "utils/Common.h"

namespace funk
{

/**
 * @brief Enumeration of all possible token types in the Funk language
 *
 * TokenType represents all possible tokens that can be recognized by
 * the Funk lexer, including keywords, literals, operators and delimiters.
 */
enum class TokenType
{
    // Keywords
    FUNK,   ///< The 'funk' keyword used for function declaration
    DATA,   ///< The 'data' keyword used for data structure declaration
    MUT,    ///< The 'mut' keyword used for mutable variable declaration
    IF,     ///< The 'if' keyword
    ELSE,   ///< The 'else' keyword
    WHILE,  ///< The 'while' keyword
    MATCH,  ///< The 'match' keyword
    CASE,   ///< The 'case' keyword
    NONE,   ///< The 'none' keyword
    RETURN, ///< The 'return' keyword

    // Literals
    NUMB, ///< Whole number literal (integer)
    REAL, ///< Decimal number literal (double)
    BOOL, ///< Boolean literal (bool)
    CHAR, ///< Single character literal (char)
    TEXT, ///< String literal (std::string)

    // Types
    NUMB_TYPE, ///< The 'numb' type keyword
    REAL_TYPE, ///< The 'real' type keyword
    BOOL_TYPE, ///< The 'bool' type keyword
    CHAR_TYPE, ///< The 'char' type keyword
    TEXT_TYPE, ///< The 'text' type keyword

    // Identifiers
    IDENTIFIER, ///< Identifier for variables, functions, etc.

    // Operators
    PLUS,     ///< Addition operator (+)
    MINUS,    ///< Subtraction operator (-)
    MULTIPLY, ///< Multiplication operator (*)
    DIVIDE,   ///< Division operator (/)
    MODULO,   ///< Modulo operator (%)
    POWER,    ///< Power operator (^)

    // Assignment operators
    ASSIGN,          ///< Assignment operator (=)
    PLUS_ASSIGN,     ///< Add and assign operator (+=)
    MINUS_ASSIGN,    ///< Subtract and assign operator (-=)
    MULTIPLY_ASSIGN, ///< Multiply and assign operator (*=)
    DIVIDE_ASSIGN,   ///< Divide and assign operator (/=)
    MODULO_ASSIGN,   ///< Modulo and assign operator (%=)
    POWER_ASSIGN,    ///< Power and assign operator (^=)

    // Comparison operators
    EQUAL,         ///< Equality operator (==)
    NOT_EQUAL,     ///< Inequality operator (!=)
    LESS,          ///< Less than operator (<)
    GREATER,       ///< Greater than operator (>)
    LESS_EQUAL,    ///< Less than or equal operator (<=)
    GREATER_EQUAL, ///< Greater than or equal operator (>=)

    // Logical operators
    OR,  ///< Logical OR operator (||)
    AND, ///< Logical AND operator (&&)
    NOT, ///< Logical NOT operator (!)

    // Pipe operator
    PIPE, ///< Pipe operator (>>)

    // Delimiters
    L_PAR,     ///< Left parenthesis (
    R_PAR,     ///< Right parenthesis )
    L_BRACE,   ///< Left brace {
    R_BRACE,   ///< Right brace }
    L_BRACKET, ///< Left bracket [
    R_BRACKET, ///< Right bracket ]
    COMMA,     ///< Comma ,
    DOT,       ///< Dot .
    COLON,     ///< Colon :
    SEMICOLON, ///< Semicolon ;
    QUESTION,  ///< Question mark ?

    COMMENT,       ///< Single line comment (#)
    BLOCK_COMMENT, ///< Multi-line comment (##)

    EOF_TOKEN, ///< End of file token
    ERROR,     ///< Error token
};

/**
 * @brief Converts a TokenType to its string representation
 * @param token The token type to convert
 * @return A string representation of the token type
 */
String token_type_to_s(TokenType token);

/**
 * @brief Converts a TokenType to its corresponding value token type
 * @param token The token type to convert
 * @return The corresponding value token type
 */
TokenType type_token_to_value_token(TokenType token);
} // namespace funk
