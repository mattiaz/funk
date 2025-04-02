#pragma once
#include "ast/expression/CallNode.h"
#include "ast/expression/ListNode.h"
#include "logging/LogMacros.h"

namespace funk
{
class MethodCallNode : public CallNode
{
public:
    MethodCallNode(ExpressionNode* object, const Token& method, const Vector<ExpressionNode*>& args);
    ~MethodCallNode() override;

    Node* evaluate() const override;
    String to_s() const override;
    NodeValue get_value() const override;

private:
    ExpressionNode* object;
};
} // namespace funk
