#pragma once

#include "ast/Node.h"
#include "token/Token.h"
#include "utils/Common.h"

namespace funk
{
class IncludeNode : public Node
{
public:
    IncludeNode(const Token& module);
    ~IncludeNode() override;

    Node* evaluate() const override;

    String to_s() const override;

private:
    Token module;
};
} // namespace funk
