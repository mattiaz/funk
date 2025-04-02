#include "ast/control/ControlNode.h"

namespace funk
{
ControlNode::ControlNode(const SourceLocation& loc) : Node(loc) {}

ControlNode::~ControlNode() = default;
} // namespace funk
