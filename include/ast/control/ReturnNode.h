#pragma once

#include "ast/control/ControlNode.h"
#include "ast/expression/ExpressionNode.h"

namespace funk
{

class ReturnNode : public ControlNode
{
public:
    ReturnNode(const SourceLocation& location, ExpressionNode* value);
    ~ReturnNode() override;

    Node* evaluate() const override;
    String to_s() const override;

    ExpressionNode* get_value() const;

private:
    ExpressionNode* value;
};

} // namespace funk
