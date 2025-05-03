#include "ast/declaration/DeclarationNode.h"

namespace funk
{
DeclarationNode::DeclarationNode(const SourceLocation& location, bool is_mutable, TokenType type,
    const String& identifier, ExpressionNode* initializer) :
    Node{location}, is_mutable{is_mutable}, type{type_token_to_value_token(type)}, identifier{identifier},
    initializer{initializer}, has_initializer{true}
{
}

DeclarationNode::DeclarationNode(
    const SourceLocation& location, bool is_mutable, TokenType type, const String& identifier) :
    Node{location}, is_mutable{is_mutable}, type{type}, identifier{identifier}, initializer{nullptr},
    has_initializer{false}
{
}

DeclarationNode::~DeclarationNode()
{
    if (initializer) { delete initializer; }
}

String DeclarationNode::get_identifier() const
{
    return identifier;
}

Node* DeclarationNode::get_initializer() const
{
    return initializer;
}

String DeclarationNode::to_s() const
{
    if (has_initializer) { return "Declaration: " + identifier + " = " + initializer->to_s(); }
    return "Declaration: " + identifier;
}

String DeclarationNode::get_type() const
{
    return token_type_to_s(type);
}

Node* DeclarationNode::evaluate() const
{
    Node* result = has_initializer ? initializer->evaluate() : new LiteralNode(get_location(), NodeValue{});

    ExpressionNode* initial_value = dynamic_cast<ExpressionNode*>(result);
    if (!initial_value)
    {
        if (result) { delete result; }
        throw RuntimeError(get_location(), "Failed to evaluate initializer for '" + identifier + "'");
    }

    if (has_initializer)
    {
        TokenType value_type = initial_value->get_value().get_token_type();
        if (value_type != type)
        {
            throw RuntimeError(
                get_location(), "Initializer for '" + identifier + "' is not type " + token_type_to_s(type));
        }
    }

    VariableNode* var = new VariableNode(get_location(), identifier, is_mutable, type, initial_value);

    Scope::instance().add(identifier, var);
    return var;
}

} // namespace funk
