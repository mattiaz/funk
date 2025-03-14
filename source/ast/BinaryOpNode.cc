#include "ast/BinaryOpNode.h"

namespace funk
{

BinaryOpNode::BinaryOpNode(ExpressionNode* left, BinaryOp op, ExpressionNode* right) :
    ExpressionNode(left->get_location()), op(op), left(left), right(right)
{
}

BinaryOpNode::~BinaryOpNode()
{
    delete left;
    delete right;
}

Node* BinaryOpNode::evaluate() const
{
    if (cached_eval) { return cached_eval; }

    NodeValue left_value{left->get_value()};
    NodeValue right_value{right->get_value()};

    NodeValue result{};

    try
    {
        switch (op)
        {
        case BinaryOp::PLUS: result = left_value + right_value; break;
        case BinaryOp::MINUS: result = left_value - right_value; break;
        case BinaryOp::MULTIPLY: result = left_value * right_value; break;
        case BinaryOp::DIVIDE: result = left_value / right_value; break;
        case BinaryOp::MODULO: result = left_value % right_value; break;
        case BinaryOp::POWER: result = pow(left_value, right_value); break;
        case BinaryOp::EQUAL: result = left_value == right_value; break;
        case BinaryOp::NOT_EQUAL: result = left_value != right_value; break;
        case BinaryOp::LESS: result = left_value < right_value; break;
        case BinaryOp::LESS_EQUAL: result = left_value <= right_value; break;
        case BinaryOp::GREATER: result = left_value > right_value; break;
        case BinaryOp::GREATER_EQUAL: result = left_value >= right_value; break;
        case BinaryOp::AND: result = left_value && right_value; break;
        case BinaryOp::OR: result = left_value || right_value; break;
        default: throw RuntimeError(location, "Invalid binary operator");
        }
    }
    catch (const TypeError& e)
    {
        throw TypeError(location, e.what());
    }
    catch (const RuntimeError& e)
    {
        throw RuntimeError(location, e.what());
    }

    return cached_eval = new LiteralNode(location, result);
}

String BinaryOpNode::to_s() const
{
    return "(" + left->to_s() + " " + op_to_s(op) + " " + right->to_s() + ")";
}

NodeValue BinaryOpNode::get_value() const
{
    ExpressionNode* result{dynamic_cast<ExpressionNode*>(evaluate())};
    if (!result) { throw RuntimeError(location, "Binary operation did not evaluate to an expression"); }

    return result->get_value();
}

BinaryOp BinaryOpNode::get_op() const
{
    return op;
}

ExpressionNode* BinaryOpNode::get_left() const
{
    return left;
}

ExpressionNode* BinaryOpNode::get_right() const
{
    return right;
}

String op_to_s(BinaryOp op)
{
    switch (op)
    {
    case BinaryOp::PLUS: return "+";
    case BinaryOp::MINUS: return "-";
    case BinaryOp::MULTIPLY: return "*";
    case BinaryOp::DIVIDE: return "/";
    case BinaryOp::MODULO: return "%";
    case BinaryOp::POWER: return "^";
    case BinaryOp::EQUAL: return "==";
    case BinaryOp::NOT_EQUAL: return "!=";
    case BinaryOp::LESS: return "<";
    case BinaryOp::LESS_EQUAL: return "<=";
    case BinaryOp::GREATER: return ">";
    case BinaryOp::GREATER_EQUAL: return ">=";
    case BinaryOp::AND: return "&&";
    case BinaryOp::OR: return "||";
    default: return "UNKNOWN";
    }
}

} // namespace funk
