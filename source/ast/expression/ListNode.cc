#include "ast/expression/ListNode.h"

namespace funk
{
ListNode::ListNode(const SourceLocation& location, const TokenType& type, const Vector<ExpressionNode*>& elements) :
    ExpressionNode(location), type(type), elements(elements)
{
}

ListNode::~ListNode()
{
    for (Node* element : elements) { delete element; }
}

Node* ListNode::evaluate() const
{
    return const_cast<ListNode*>(this);
}

String ListNode::to_s() const
{
    String result{"[ "};
    for (size_t i{0}; i < elements.size(); i++)
    {
        result += elements[i]->to_s();
        if (i < elements.size() - 1) { result += ", "; }
    }
    result += " ]";
    return result;
}

NodeValue ListNode::get_value() const
{
    ExpressionNode* result{dynamic_cast<ExpressionNode*>(evaluate())};
    if (!result) { throw RuntimeError(location, "List did not evaluate to an expression"); }
    return NodeValue(result->to_s());
}

size_t ListNode::length() const
{
    return elements.size();
}
} // namespace funk
