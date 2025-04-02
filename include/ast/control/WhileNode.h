#pragma once

#include "ast/BlockNode.h"
#include "ast/control/ControlNode.h"
#include "ast/expression/ExpressionNode.h"

namespace funk
{
class WhileNode : public ControlNode
{
public:
    WhileNode(ExpressionNode* condition, BlockNode* body);
    ~WhileNode() override;
    Node* evaluate() const override;
    String to_s() const override;

private:
    ExpressionNode* condition;
    BlockNode* body;
};
} // namespace funk
