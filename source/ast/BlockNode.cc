#include "ast/BlockNode.h"

namespace funk
{
BlockNode::BlockNode(const SourceLocation& loc) : Node(loc), statements{} {}

BlockNode::~BlockNode()
{
    for (Node* statement : statements) { delete statement; }
}

void BlockNode::add(Node* statement)
{
    statements.push_back(statement);
}

Vector<Node*> BlockNode::get_statements() const
{
    return statements;
}

Node* BlockNode::evaluate() const
{
    Node* result{};
    for (Node* statement : statements) { result = statement->evaluate(); }
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
