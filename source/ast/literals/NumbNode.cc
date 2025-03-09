#include "ast/literals/NumbNode.h"

namespace funk
{

NumbNode::NumbNode(const SourceLocation& loc, double value) : Node(loc), value(value) {}

Node* NumbNode::evaluate()
{
    return this;
}

String NumbNode::to_s() const
{
    return std::to_string(value);
}

double NumbNode::get_value() const
{
    return value;
}

} // namespace funk
