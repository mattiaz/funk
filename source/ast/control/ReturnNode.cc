#include "ast/control/ReturnNode.h"
#include "utils/Common.h"

namespace funk
{

ReturnNode::ReturnNode(const SourceLocation& location, ExpressionNode* value) : ControlNode(location), value(value) {}

ReturnNode::~ReturnNode()
{
    delete value;
}

Node* ReturnNode::evaluate() const
{
    return value ? value->evaluate() : nullptr;
}

String ReturnNode::to_s() const
{
    if (!value) { return "return"; }
    return "return " + value->to_s();
}

ExpressionNode* ReturnNode::get_value() const
{
    return value;
}

} // namespace funk
