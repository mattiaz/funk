#include "ast/IncludeNode.h"

namespace funk
{
IncludeNode::IncludeNode(const Token& module) : Node(module.get_location()), module(module) {}

IncludeNode::~IncludeNode() {}

Node* IncludeNode::evaluate() const {}

String IncludeNode::to_s() const
{
    return "include " + module.to_s();
}
} // namespace funk
