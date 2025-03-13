#pragma once

#include "ast/ExpressionNode.h"

namespace funk
{

class LiteralNode : public ExpressionNode
{
public:
    LiteralNode(const SourceLocation& loc, NodeValue value);
    ~LiteralNode() override = default;

    Node* evaluate() override;
    String to_s() const override;

    NodeValue get_value() const;

private:
    NodeValue value;
};

} // namespace funk
