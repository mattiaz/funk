#pragma once

#include "ast/Node.h"
#include "ast/expression/ExpressionNode.h"
#include "token/TokenType.h"

namespace funk
{

class VariableNode : public ExpressionNode
{
public:
    VariableNode(const SourceLocation& location, const String& identifier, bool is_mutable, TokenType type,
        ExpressionNode* value);
    ~VariableNode() override;

    Node* evaluate() const override;
    String to_s() const override;
    NodeValue get_value() const override;

    bool get_mutable() const;
    TokenType get_type() const;
    const String& get_identifier() const;
    ExpressionNode* get_value_node() const;
    void set_value(ExpressionNode* new_value);

private:
    String identifier;
    bool is_mutable;
    TokenType type;
    ExpressionNode* value;
};

} // namespace funk