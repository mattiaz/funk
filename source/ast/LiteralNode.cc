#include "ast/LiteralNode.h"

namespace funk
{

LiteralNode::LiteralNode(const SourceLocation& loc, NodeValue value) : ExpressionNode(loc), value(value) {}

Node* LiteralNode::evaluate() const
{
    if (cached_eval) { return cached_eval; }
    return cached_eval = const_cast<LiteralNode*>(this);
}

String LiteralNode::to_s() const
{
    return value.cast<String>();
}

NodeValue LiteralNode::get_value() const
{
    return value;
}

} // namespace funk
