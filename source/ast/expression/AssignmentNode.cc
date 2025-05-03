#include "ast/expression/AssignmentNode.h"

namespace funk
{

AssignmentNode::AssignmentNode(Node* left, const Token& op, ExpressionNode* right) :
    ExpressionNode(left->get_location()), left(left), op(op), right(right)
{
}

Node* AssignmentNode::get_left() const
{
    return left;
}
const Token& AssignmentNode::get_op() const
{
    return op;
}
ExpressionNode* AssignmentNode::get_right() const
{
    return right;
}

Node* AssignmentNode::evaluate() const
{
    NodeValue value{right->get_value()};
    auto var = dynamic_cast<VariableNode*>(left->evaluate());
    if (var->get_mutable())
    {
        if (var->get_type() != right->get_value().get_token_type())
        {
            throw TypeError(get_location(), "Cannot assign " + token_type_to_s(right->get_value().get_token_type()) +
                                                " to " + token_type_to_s(var->get_type()));
        }
        var->set_value(new LiteralNode(get_location(), value));
    }
    else { throw RuntimeError(get_location(), "Cannot assign to immutable variable '" + var->get_identifier() + "'"); }
    return new LiteralNode(get_location(), value);
}
String AssignmentNode::to_s() const
{
    return String();
}
NodeValue AssignmentNode::get_value() const
{
    return NodeValue();
}

} // namespace funk