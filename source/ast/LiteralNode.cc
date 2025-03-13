#include "ast/LiteralNode.h"

namespace funk
{

LiteralNode::LiteralNode(const SourceLocation& loc, NodeValue value) : ExpressionNode(loc), value(value) {}

Node* LiteralNode::evaluate()
{
    return this;
}

String LiteralNode::to_s() const
{
    return cast<String>();
}

NodeValue LiteralNode::get_value() const
{
    return value;
}

} // namespace funk
