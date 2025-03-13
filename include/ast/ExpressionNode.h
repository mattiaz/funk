#pragma once

#include "ast/Node.h"

namespace funk
{

class ExpressionNode : public Node
{
public:
    ExpressionNode(const SourceLocation& loc);
    ~ExpressionNode() override = default;

    virtual NodeValue get_value() const = 0;

    template <typename T> bool is_a() const;
    template <typename T> T get() const;
    template <typename T> T cast() const;

    bool is_numeric() const;
    bool is_nothing() const;
};

} // namespace funk
