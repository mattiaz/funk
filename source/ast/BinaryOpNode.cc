#include "ast/BinaryOpNode.h"

namespace funk
{

BinaryOpNode::BinaryOpNode(ExpressionNode* left, const Token& op, ExpressionNode* right) :
    ExpressionNode(op.get_location()), op(op), left(left), right(right)
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
        switch (op.get_type())
        {
        case TokenType::PLUS: result = left_value + right_value; break;
        case TokenType::MINUS: result = left_value - right_value; break;
        case TokenType::MULTIPLY: result = left_value * right_value; break;
        case TokenType::DIVIDE: result = left_value / right_value; break;
        case TokenType::MODULO: result = left_value % right_value; break;
        case TokenType::POWER: result = pow(left_value, right_value); break;
        case TokenType::EQUAL: result = left_value == right_value; break;
        case TokenType::NOT_EQUAL: result = left_value != right_value; break;
        case TokenType::LESS: result = left_value < right_value; break;
        case TokenType::LESS_EQUAL: result = left_value <= right_value; break;
        case TokenType::GREATER: result = left_value > right_value; break;
        case TokenType::GREATER_EQUAL: result = left_value >= right_value; break;
        case TokenType::AND: result = left_value && right_value; break;
        case TokenType::OR: result = left_value || right_value; break;
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
    return "(" + left->to_s() + " " + token_type_to_s(op.get_type()) + " " + right->to_s() + ")";
}

NodeValue BinaryOpNode::get_value() const
{
    ExpressionNode* result{dynamic_cast<ExpressionNode*>(evaluate())};
    if (!result) { throw RuntimeError(location, "Binary operation did not evaluate to an expression"); }

    return result->get_value();
}

Token BinaryOpNode::get_op() const
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

} // namespace funk
