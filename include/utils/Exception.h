/**
 * @file Exception.h
 * @brief Defines the exception hierarchy for the Funk programming language.
 */
#pragma once

#include "utils/Common.h"
#include <sstream>
#include <stdexcept>

namespace funk
{

/**
 * @brief Base exception class for all Funk language errors.
 * Extends std::runtime_error with additional information about the error location and type.
 */
class FunkError : public std::runtime_error
{
public:
    /**
     * @brief Constructs a FunkError with location, type, and message.
     * @param loc Source location where the error occurred
     * @param type Type of the error
     * @param message Description of the error
     */
    FunkError(const SourceLocation& loc, const String& type, const String& message);

    /**
     * @brief Gets the source location of the error.
     * @return Reference to the source location
     */
    const SourceLocation& get_location() const;

    /**
     * @brief Generates a formatted trace message for the error.
     * @return Error trace as a string
     */
    String trace() const;

protected:
    String type;             ///< Type of the error
    SourceLocation location; ///< Location where the error occurred
};

/**
 * @brief Exception class for lexical analysis errors.
 * Thrown when the lexer encounters invalid tokens or other lexical issues.
 */
class LexerError : public FunkError
{
public:
    /**
     * @brief Constructs a LexerError with location and message.
     * @param loc Source location where the error occurred
     * @param message Description of the error
     */
    LexerError(const SourceLocation& loc, const String& message) : FunkError(loc, "Lexer error", message) {}
    LexerError(const String& message) : FunkError(SourceLocation{"", 0, 0}, "Lexer error", message) {}
};

/**
 * @brief Exception class for syntax errors.
 * Thrown when the parser encounters invalid syntax in the input program.
 */
class SyntaxError : public FunkError
{
public:
    /**
     * @brief Constructs a SyntaxError with location and message.
     * @param loc Source location where the error occurred
     * @param message Description of the error
     */
    SyntaxError(const SourceLocation& loc, const String& message) : FunkError(loc, "Syntax error", message) {}
    SyntaxError(const String& message) : FunkError(SourceLocation{"", 0, 0}, "Syntax error", message) {}
};

/**
 * @brief Exception class for type errors.
 * Thrown when an operation is performed on incompatible types.
 */
class TypeError : public FunkError
{
public:
    /**
     * @brief Constructs a TypeError with location and message.
     * @param loc Source location where the error occurred
     * @param message Description of the error
     */
    TypeError(const SourceLocation& loc, const String& message) : FunkError(loc, "Type error", message) {}
    TypeError(const String& message) : FunkError(SourceLocation{"", 0, 0}, "Type error", message) {}
};

/**
 * @brief Exception class for runtime errors.
 * Thrown when errors occur during program execution.
 */
class RuntimeError : public FunkError
{
public:
    /**
     * @brief Constructs a RuntimeError with location and message.
     * @param loc Source location where the error occurred
     * @param message Description of the error
     */
    RuntimeError(const SourceLocation& loc, const String& message) : FunkError(loc, "Runtime error", message) {}
    RuntimeError(const String& message) : FunkError(SourceLocation{"", 0, 0}, "Runtime error", message) {}
};

} // namespace funk
