#include "ast/Node.h"

namespace funk
{

Node::Node(const SourceLocation& loc) : location(loc) {}

SourceLocation Node::get_location() const
{
    return location;
}

} // namespace funk
