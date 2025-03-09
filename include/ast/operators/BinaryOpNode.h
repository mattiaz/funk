#pragma once

#include "ast/Node.h"
#include "token/TokenType.h"

namespace funk
{

class BinaryOpNode : public Node
{
public:
    BinaryOpNode(const SourceLocation& loc, TokenType op, Node* left, Node* right);
    ~BinaryOpNode() override = default;

    Node* evaluate() override;
    String to_s() const override;

    Node* get_left() const;
    Node* get_right() const;

private:
    TokenType op;
    Node* left;
    Node* right;
};

} // namespace funk
