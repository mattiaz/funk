#pragma once
#include "ast/Node.h"

namespace funk
{
class ProgramNode : public Node
{
public:
    ProgramNode(const SourceLocation& loc);
    ~ProgramNode();

    void add(Node* statement);

    Node* evaluate() const override;
    String to_s() const override;

private:
    Vector<Node*> statements;
};
} // namespace funk
