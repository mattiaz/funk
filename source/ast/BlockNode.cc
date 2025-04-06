#include "ast/BlockNode.h"

namespace funk
{
BlockNode::BlockNode(const SourceLocation& loc) : Node(loc), statements{} {}

BlockNode::BlockNode(const SourceLocation& loc, const Vector<Node*>& statements) : Node(loc), statements{statements} {}

BlockNode::~BlockNode()
{
    for (Node* statement : statements) { delete statement; }
}

void BlockNode::add(Node* statement)
{
    if (statement == nullptr)
    {
        LOG_WARN("Attempted to add null statement to block");
        return;
    }
    statements.push_back(statement);
}

Vector<Node*> BlockNode::get_statements() const
{
    return statements;
}

Node* BlockNode::evaluate() const
{
    Scope::instance().push();
    Node* result{};
    for (Node* statement : statements) { result = statement->evaluate(); }
    Scope::instance().pop();
    return result;
}

String BlockNode::to_s() const
{
    String repr{};

    for (Node* statement : statements)
    {
        repr += statement->to_s();
        repr += '\n';
    }

    return repr;
}
} // namespace funk
