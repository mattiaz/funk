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
    if (!statement)
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
    bool push_scope{false};

    for (Node* statement : statements)
    {
        if (dynamic_cast<DeclarationNode*>(statement) || dynamic_cast<FunctionNode*>(statement))
        {
            push_scope = true;
            break;
        }
    }

    if (push_scope) { Scope::instance().push(); }
    Node* result{};

    for (Node* statement : statements)
    {
        result = statement->evaluate();
        if (dynamic_cast<ReturnNode*>(statement)) { break; }
        result = nullptr;
    }

    if (push_scope) { Scope::instance().pop(); }
    return result;
}

Node* BlockNode::evaluate_same_scope() const
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
