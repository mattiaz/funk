#pragma once

#include "ast/BlockNode.h"
#include "ast/declaration/VariableNode.h"
#include "ast/expression/ExpressionNode.h"
#include "parser/BuiltIn.h"
#include "parser/Registry.h"
#include "parser/Scope.h"
#include "token/Token.h"

namespace funk
{

class FunctionNode : public Node
{
public:
    FunctionNode(const SourceLocation& location, bool is_mutable, const String& identifier,
        const Vector<Pair<TokenType, String>>& parameters, BlockNode* body);

    FunctionNode(const SourceLocation& location, bool is_mutable, const String& identifier,
        const Vector<ExpressionNode*>& pattern_values, BlockNode* body);

    ~FunctionNode() override;

    Node* evaluate() const override;
    String to_s() const override;

    Node* call(const Vector<ExpressionNode*>& arguments) const;

    bool is_mutable_function() const;
    String get_identifier() const;
    const Vector<Pair<TokenType, String>>& get_parameters() const;
    BlockNode* get_body() const;

    bool is_pattern_matching() const;
    bool matches(const Vector<ExpressionNode*>& arguments) const;

private:
    bool is_mutable;
    bool is_pattern;
    String identifier;
    Vector<Pair<TokenType, String>> parameters;
    Vector<ExpressionNode*> pattern_values;
    BlockNode* body;

    void init_param_scope(const Vector<ExpressionNode*>& arguments) const;
};
} // namespace funk
