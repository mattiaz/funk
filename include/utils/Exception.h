#pragma once

#include "utils/Common.h"
#include <sstream>
#include <stdexcept>

namespace funk
{

class FunkError : public std::runtime_error
{
public:
    FunkError(const SourceLocation& loc, const String& type, const String& message);
    const SourceLocation& get_location() const;
    String trace() const;

protected:
    String type;
    SourceLocation location;
};

class FileError : public FunkError
{
public:
    FileError(const SourceLocation& loc, const String& message) : FunkError(loc, "File error", message) {}
};

class LexerError : public FunkError
{
public:
    LexerError(const SourceLocation& loc, const String& message) : FunkError(loc, "Lexer error", message) {}
};

class SyntaxError : public FunkError
{
public:
    SyntaxError(const SourceLocation& loc, const String& message) : FunkError(loc, "Syntax error", message) {}
};

class TypeError : public FunkError
{
public:
    TypeError(const SourceLocation& loc, const String& message) : FunkError(loc, "Type error", message) {}
};

class RuntimeError : public FunkError
{
public:
    RuntimeError(const SourceLocation& loc, const String& message) : FunkError(loc, "Runtime error", message) {}
};

} // namespace funk
