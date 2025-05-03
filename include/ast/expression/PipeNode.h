#pragma once

#include "ast/declaration/FunctionNode.h"
#include "ast/expression/CallNode.h"
#include "ast/expression/ExpressionNode.h"

namespace funk
{

class PipeNode : public ExpressionNode
{
public:
    PipeNode(const SourceLocation& location, ExpressionNode* source, ExpressionNode* target);
    ~PipeNode() override;

    Node* evaluate() const override;
    String to_s() const override;
    NodeValue get_value() const override;

    ExpressionNode* get_source() const;
    ExpressionNode* get_target() const;

private:
    ExpressionNode* source;
    ExpressionNode* target;
};
} // namespace funk
