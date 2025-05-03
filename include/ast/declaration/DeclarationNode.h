#pragma once

#include "ast/Node.h"
#include "ast/expression/LiteralNode.h"
#include "ast/expression/VariableNode.h"
#include "parser/Scope.h"
#include "token/Token.h"

namespace funk
{
class DeclarationNode : public Node
{
public:
    DeclarationNode(const SourceLocation& location, bool is_mutable, TokenType type, const String& identifier,
        ExpressionNode* initializer);

    DeclarationNode(const SourceLocation& location, bool is_mutable, TokenType type, const String& identifier);

    ~DeclarationNode() override;

    String get_identifier() const;
    Node* get_initializer() const;
    String to_s() const override;

    String get_type() const;

    Node* evaluate() const override;

private:
    bool is_mutable;
    TokenType type;
    String identifier;
    ExpressionNode* initializer;
    bool has_initializer;
};

} // namespace funk
