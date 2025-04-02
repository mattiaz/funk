#include "ast/control/IfNode.h"

namespace funk
{
IfNode::IfNode(ExpressionNode* condition, BlockNode* body, Node* else_branch) :
    ControlNode(condition->get_location()), condition(condition), body(body), else_branch(else_branch)
{
}

IfNode::~IfNode()
{
    delete condition;
    delete body;

    if (else_branch) { delete else_branch; }
}

Node* IfNode::evaluate() const
{
    LOG_DEBUG("Evaluating if statement");
    if (dynamic_cast<ExpressionNode*>(condition->evaluate())->get_value().cast<bool>()) { return body->evaluate(); }
    else if (else_branch) { return else_branch->evaluate(); }
    return nullptr;
}

String IfNode::to_s() const
{
    String result{"if ( " + condition->to_s() + " ) {\n" + body->to_s() + "}"};
    if (else_branch) { result += "\n} else {\n" + else_branch->to_s() + "}"; }
    return result;
}
} // namespace funk
