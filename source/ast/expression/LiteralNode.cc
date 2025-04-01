#include "ast/expression/LiteralNode.h"

namespace funk
{

LiteralNode::LiteralNode(const SourceLocation& loc, NodeValue value) : ExpressionNode(loc), value(value) {}

Node* LiteralNode::evaluate() const
{
    return const_cast<LiteralNode*>(this);
}

String LiteralNode::to_s() const
{
    if (value.is_a<String>()) { return "\"" + value.get<String>() + "\""; }
    if (value.is_a<char>()) { return "'" + String(1, value.get<char>()) + "'"; }
    return value.cast<String>();
}

NodeValue LiteralNode::get_value() const
{
    return value;
}

} // namespace funk
