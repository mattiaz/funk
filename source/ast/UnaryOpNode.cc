#include "ast/UnaryOpNode.h"

namespace funk
{

UnaryOpNode::UnaryOpNode(UnaryOp op, ExpressionNode* expr) :
    ExpressionNode(expr->get_location()), op(op), expr(expr) {

    };

UnaryOpNode::~UnaryOpNode()
{
    delete expr;
}

Node* UnaryOpNode::evaluate() const
{
    if (cached_eval) { return cached_eval; }

    NodeValue expr_value{expr->get_value()};
    NodeValue result{};

    try
    {
        switch (op)
        {
        case UnaryOp::NEGATE: result = -expr_value; break;
        case UnaryOp::NOT: result = !expr_value; break;
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

    return cached_eval = new LiteralNode(location, result);
}

String UnaryOpNode::to_s() const
{
    return "(" + op_to_s(op) + expr->to_s() + ")";
}

NodeValue UnaryOpNode::get_value() const
{
    ExpressionNode* result{dynamic_cast<ExpressionNode*>(evaluate())};
    if (!result) { throw RuntimeError(location, "Unary operation did not evaluate to an expression"); }

    return result->get_value();
}

UnaryOp UnaryOpNode::get_op() const
{
    return op;
}

ExpressionNode* UnaryOpNode::get_expr() const
{
    return expr;
}

String op_to_s(UnaryOp op)
{
    switch (op)
    {
    case UnaryOp::NEGATE: return "-";
    case UnaryOp::NOT: return "!";
    default: return "UNKNOWN";
    }
}

}; // namespace funk