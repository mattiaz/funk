#include "ast/ProgramNode.h"

namespace funk
{
ProgramNode::ProgramNode(const SourceLocation& loc) : Node(loc), statements{} {}

ProgramNode::~ProgramNode()
{
    for (Node* statement : statements) { delete statement; }
}

void ProgramNode::add(Node* statement)
{
    statements.push_back(statement);
}

Node* ProgramNode::evaluate() const
{
    if (cached_eval) { return cached_eval; }

    Node* result{};
    for (Node* statement : statements) { result = statement->evaluate(); }
    return cached_eval = result;
}

String ProgramNode::to_s() const
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
