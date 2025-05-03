#pragma once
#include "ast/expression/ExpressionNode.h"
#include "ast/expression/LiteralNode.h"
#include "ast/expression/VariableNode.h"
#include "token/Token.h"

namespace funk
{

class AssignmentNode : public ExpressionNode
{
public:
    AssignmentNode(Node* left, const Token& op, ExpressionNode* right);

    Node* get_left() const;
    const Token& get_op() const;
    ExpressionNode* get_right() const;

    Node* evaluate() const override;
    String to_s() const override;
    NodeValue get_value() const override;

private:
    Node* left;
    Token op;
    ExpressionNode* right;
};

} // namespace funk