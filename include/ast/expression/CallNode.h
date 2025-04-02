#pragma once

#include "ast/expression/ExpressionNode.h"
#include "ast/expression/LiteralNode.h"
#include "logging/LogMacros.h"
#include "parser/BuiltIn.h"
#include "token/Token.h"

namespace funk
{
class CallNode : public ExpressionNode
{
public:
    CallNode(const Token& identifier, const Vector<ExpressionNode*>& args);
    ~CallNode() override;

    Node* evaluate() const override;

    String to_s() const override;

    NodeValue get_value() const override;

private:
    Token identifier;
    Vector<ExpressionNode*> args;
};
} // namespace funk
