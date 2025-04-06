#include "ast/declaration/VariableNode.h"

namespace funk
{
VariableNode::VariableNode(
    const SourceLocation& location, const String& identifier, bool is_mutable, TokenType type, ExpressionNode* value) :
    ExpressionNode{location}, identifier{identifier}, is_mutable{is_mutable}, type{type}, value{value}
{
}

VariableNode::VariableNode(const SourceLocation& location, const String& identifier) :
    ExpressionNode{location}, identifier{identifier}
{
}

VariableNode::~VariableNode()
{
    if (value) { delete value; }
    value = nullptr;
}

Node* VariableNode::evaluate() const
{
    if (value == nullptr)
    {
        Node* result = Scope::instance().get(identifier);
        if (result == nullptr) { throw RuntimeError(get_location(), "Undefined variable '" + identifier + "'"); }
        return result;
    }
    return new VariableNode(get_location(), identifier, is_mutable, type, value);
}

String VariableNode::to_s() const
{
    return "Variable: " + identifier + " = " + value->to_s();
}

NodeValue VariableNode::get_value() const
{
    if (value)
    {
        NodeValue val = value->get_value();
        return val;
    }
    return NodeValue{};
}

bool VariableNode::get_mutable() const
{
    return is_mutable;
}

TokenType VariableNode::get_type() const
{
    return type;
}

const String& VariableNode::get_identifier() const
{
    return identifier;
}

ExpressionNode* VariableNode::get_value_node() const
{
    return value;
}

void VariableNode::set_value(ExpressionNode* new_value)
{
    if (is_mutable)
    {
        if (value) { delete value; }
        value = new_value;
    }
    else { throw RuntimeError(get_location(), "Cannot modify immutable variable '" + identifier + "'"); }
}
} // namespace funk