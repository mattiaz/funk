#pragma once

#include "ast/BlockNode.h"
#include "ast/control/ControlNode.h"
#include "ast/expression/ExpressionNode.h"

namespace funk
{
class IfNode : public ControlNode
{
public:
    IfNode(ExpressionNode* condition, BlockNode* body, Node* else_branch = nullptr);
    ~IfNode() override;
    Node* evaluate() const override;
    String to_s() const override;

private:
    ExpressionNode* condition;
    BlockNode* body;
    Node* else_branch;
};
} // namespace funk
