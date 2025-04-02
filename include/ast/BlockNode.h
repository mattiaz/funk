#pragma once

#include "ast/Node.h"
#include "parser/Scope.h"

namespace funk
{

class BlockNode : public Node
{
public:
    BlockNode(const SourceLocation& loc);
    BlockNode(const SourceLocation& loc, const Vector<Node*>& statements);
    ~BlockNode();

    void add(Node* statement);
    Vector<Node*> get_statements() const;

    Node* evaluate() const override;
    String to_s() const override;

private:
    Vector<Node*> statements;
};

} // namespace funk
