#pragma once
#include "ast/expression/ExpressionNode.h"
#include "logging/LogMacros.h"
#include "token/Token.h"

namespace funk
{
class ListNode : public ExpressionNode
{
public:
    ListNode(const SourceLocation& location, const TokenType& type, const Vector<ExpressionNode*>& elements);
    ~ListNode() override;

    Node* evaluate() const override;
    String to_s() const override;
    NodeValue get_value() const override;

    size_t length() const;

private:
    const TokenType type;
    Vector<ExpressionNode*> elements;
};
} // namespace funk
