#include "ast/expression/UnaryOpNode.h"

namespace funk
{

UnaryOpNode::UnaryOpNode(const Token& op, ExpressionNode* expr) :
    ExpressionNode(op.get_location()), op(op), expr(expr) {

    };

UnaryOpNode::~UnaryOpNode()
{
    delete expr;
}

Node* UnaryOpNode::evaluate() const
{
    NodeValue expr_value{expr->get_value()};
    NodeValue result{};

    try
    {
        switch (op.get_type())
        {
        case TokenType::MINUS: result = -expr_value; break;
        case TokenType::NOT: result = !expr_value; break;
        default: throw RuntimeError(location, "Invalid unary operator");
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

    return new LiteralNode(location, result);
}

String UnaryOpNode::to_s() const
{
    return "(" + op.get_lexeme() + expr->to_s() + ")";
}

NodeValue UnaryOpNode::get_value() const
{
    ExpressionNode* result{dynamic_cast<ExpressionNode*>(evaluate())};
    if (!result) { throw RuntimeError(location, "Unary operation did not evaluate to an expression"); }

    return result->get_value();
}

Token UnaryOpNode::get_op() const
{
    return op;
}

ExpressionNode* UnaryOpNode::get_expr() const
{
    return expr;
}

}; // namespace funk
