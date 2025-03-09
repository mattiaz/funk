#pragma once

#include "utils/Common.h"

namespace funk
{

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
