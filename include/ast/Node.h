#pragma once

#include "utils/Common.h"

namespace funk
{

// TODO: This is a idea to simplify node values, implementing a generic literal type
// not separate it in different classes.
// using NodeValue = std::variant<std::monostate, int, double, bool, char, String, Node*>;

class Node
{
public:
    Node(const SourceLocation& loc);
    virtual ~Node() = default;

    virtual Node* evaluate() = 0;
    virtual String to_s() const = 0;

    SourceLocation get_location() const;

protected:
    SourceLocation location;
};

} // namespace funk
