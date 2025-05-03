#include "ast/expression/VariableNode.h"

namespace funk
{
VariableNode::VariableNode(
    const SourceLocation& location, const String& identifier, bool is_mutable, TokenType type, ExpressionNode* value) :
    ExpressionNode{location}, identifier{identifier}, is_mutable{is_mutable}, type{type}, value{value}
{
}

VariableNode::VariableNode(const SourceLocation& location, const String& identifier) :
    ExpressionNode{location}, identifier{identifier}, is_mutable{false}, type{TokenType::NONE}, value{nullptr}
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

    return value->evaluate();
}

String VariableNode::to_s() const
{
    if (value == nullptr) { return "Variable: " + identifier; }
    return "Variable: " + identifier + " = " + value->to_s();
}

NodeValue VariableNode::get_value() const
{
    ExpressionNode* result{dynamic_cast<ExpressionNode*>(evaluate())};
    if (!result) { throw RuntimeError(location, "Variable did not evaluate to an expression."); }

    return result->get_value();
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
