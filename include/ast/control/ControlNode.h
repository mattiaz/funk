#pragma once

#include "ast/Node.h"

namespace funk
{
class ControlNode : public Node
{
public:
    ControlNode(const SourceLocation& loc);
    ~ControlNode() override;
};
} // namespace funk
