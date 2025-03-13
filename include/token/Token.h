/**
 * @file Token.h
 * @brief Definition of the Token class.
 *
 * This file defines the Token class which represents lexical tokens with their metadata.
 */

#pragma once

#include "token/TokenType.h"
#include "utils/Common.h"

namespace funk
{

/**
 * @brief Variant type for storing different possible token values
 * TokenValue can hold any of the primitive types used in the Funk language aswell as the None type.
 */
using TokenValue = std::variant<int, double, bool, char, String, None>;

/**
 * @brief Class representing a lexical token in the Funk language
 * Each Token contains information about its type, lexeme (the actual text),
 * value (interpreted content), and location in the source code.
 */
class Token
{
public:
    /**
     * @brief Constructs a token without a value
     * @param loc Source location information
     * @param lexeme The actual text of the token
     * @param type The token's type
     */
    Token(const SourceLocation& loc, const String& lexeme, TokenType type);

    /**
     * @brief Constructs a token with a value
     * @param loc Source location information
     * @param lexeme The actual text of the token
     * @param type The token's type
     * @param value The interpreted value of the token
     */
    Token(const SourceLocation& loc, const String& lexeme, TokenType type, TokenValue value);

    /**
     * @brief Gets the token's type
     * @return TokenType The type of this token
     */
    TokenType get_type() const;

    /**
     * @brief Gets the token's lexeme
     * @return String The raw text of this token
     */
    String get_lexeme() const;

    /**
     * @brief Gets the token's value
     * @return TokenValue The interpreted value of this token
     */
    TokenValue get_value() const;

    /**
     * @brief Gets the token's source location
     * @return SourceLocation Information about where this token appeared in the source
     */
    SourceLocation get_location() const;

    /**
     * @brief Converts the token to a string representation
     * @return String A human-readable representation of the token
     */
    String to_s() const;

private:
    SourceLocation location; ///< The location of this token in the source code
    String lexeme;           ///< The actual text of this token
    TokenType type;          ///< The type of this token
    TokenValue value;        ///< The interpreted value of this token

    /**
     * @brief Helper method to convert the token's value to a string
     * @return String String representation of the token's value
     */
    String get_value_str() const;
};

/**
 * @brief Stream output operator for Token objects
 * @param os The output stream
 * @param token The token to output
 * @return std::ostream& Reference to the output stream
 */
inline std::ostream& operator<<(std::ostream& os, const Token& token)
{
    os << token.to_s();
    return os;
}

} // namespace funk
