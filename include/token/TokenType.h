#pragma once
#include "utils/Common.h"

namespace funk
{

enum class TokenType
{
    // Keywords
    FUNK,
    DATA,
    MUT,
    IF,
    ELSE,
    WHILE,
    MATCH,
    CASE,
    NONE,
    RETURN,

    // Literals
    NUMB, // Whole number
    REAL, // Decimal number
    BOOL, // True or false
    CHAR, // Single character
    TEXT, // String of characters

    // Types
    NUMB_TYPE, // numb
    REAL_TYPE, // real
    BOOL_TYPE, // bool
    CHAR_TYPE, // char
    TEXT_TYPE, // text

    // Identifiers
    IDENTIFIER, // Identifier for variables, functions, etc.

    // Operators
    PLUS,     // +
    MINUS,    // -
    MULTIPLY, // *
    DIVIDE,   // /
    PERCENT,  // %

    // Assignment operators
    ASSIGN,          // =
    PLUS_ASSIGN,     // +=
    MINUS_ASSIGN,    // -=
    MULTIPLY_ASSIGN, // *=
    DIVIDE_ASSIGN,   // /=

    // Comparison operators
    EQUAL,         // ==
    NOT_EQUAL,     // !=
    LESS,          // <
    GREATER,       // >
    LESS_EQUAL,    // <=
    GREATER_EQUAL, // >=

    // Logical operators
    OR,  // ||
    AND, // &&
    NOT, // !

    // Pipe operator
    PIPE, // >>

    // Delimiters
    L_PAR,     // (
    R_PAR,     // )
    L_BRACE,   // {
    R_BRACE,   // }
    L_BRACKET, // [
    R_BRACKET, // ]
    COMMA,     // ,
    DOT,       // .
    COLON,     // :
    SEMICOLON, // ;
    QUESTION,  // ?

    COMMENT,       // # Comment
    BLOCK_COMMENT, // ## Mumtiline comment

    EOF_TOKEN, // End of File
    ERROR,     // Error
};

String token_type_to_string(TokenType token);
} // namespace funk
