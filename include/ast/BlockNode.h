#pragma once

#include "ast/Node.h"

namespace funk
{

class BlockNode : public Node
{
public:
    BlockNode(const SourceLocation& loc);
    ~BlockNode();

    void add(Node* statement);
    Vector<Node*> get_statements() const;

    Node* evaluate() const override;
    String to_s() const override;

private:
    Vector<Node*> statements;
};

} // namespace funk
