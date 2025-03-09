#pragma once

#include "ast/Node.h"

namespace funk
{

class NumbNode : public Node
{
public:
    NumbNode(const SourceLocation& loc, double value);
    ~NumbNode() override = default;

    Node* evaluate() override;
    String to_s() const override;

    double get_value() const;

private:
    double value;
};

} // namespace funk
