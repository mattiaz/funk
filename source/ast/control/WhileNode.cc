#include "ast/control/WhileNode.h"

namespace funk
{
WhileNode::WhileNode(ExpressionNode* condition, BlockNode* body) :
    ControlNode(condition->get_location()), condition(condition), body(body)
{
}

WhileNode::~WhileNode()
{
    delete condition;
    delete body;
}

Node* WhileNode::evaluate() const
{
    LOG_DEBUG("Evaluating while loop");
    while (dynamic_cast<ExpressionNode*>(condition->evaluate())->get_value().cast<bool>()) { body->evaluate(); }
    return nullptr;
}

String WhileNode::to_s() const
{
    return "while ( " + condition->to_s() + " ) {\n" + body->to_s() + "}";
}
} // namespace funk
