#include "ast/declaration/FunctionNode.h"

namespace funk
{

FunctionNode::FunctionNode(const SourceLocation& location, bool is_mutable, const String& identifier,
    const Vector<Pair<TokenType, String>>& parameters, BlockNode* body) :
    Node(location), is_mutable(is_mutable), is_pattern(false), identifier(identifier), parameters(parameters),
    body(body)
{
}

FunctionNode::FunctionNode(const SourceLocation& location, bool is_mutable, const String& identifier,
    const Vector<ExpressionNode*>& pattern_values, BlockNode* body) :
    Node(location), is_mutable(is_mutable), is_pattern(true), identifier(identifier), pattern_values(pattern_values),
    body(body)
{
}

FunctionNode::~FunctionNode()
{
    delete body;
    if (is_pattern)
    {
        for (ExpressionNode* pattern : pattern_values) { delete pattern; }
    }
}

Node* FunctionNode::evaluate() const
{
    // Check if the function is built-in
    if (BuiltIn::functions.find(identifier) != BuiltIn::functions.end())
    {
        throw RuntimeError(get_location(), "Cannot overwrite built-in function: " + identifier);
    }

    // Register the function in the registry
    Registry::instance().add_function(const_cast<FunctionNode*>(this));
    // Add the function to the current scope
    Scope::instance().add(identifier, const_cast<FunctionNode*>(this));

    return const_cast<FunctionNode*>(this);
}

String FunctionNode::to_s() const
{
    String repr{(is_mutable ? "mut " : "") + String("funk ") + identifier + " = ("};

    if (is_pattern)
    {
        for (size_t i{0}; i < pattern_values.size(); i++)
        {
            repr += pattern_values[i]->to_s();
            if (i < pattern_values.size() - 1) { repr += ", "; }
        }
    }
    else
    {
        for (size_t i{0}; i < parameters.size(); i++)
        {
            repr += token_type_to_s(parameters[i].first) + " " + parameters[i].second;
            if (i < parameters.size() - 1) { repr += ", "; }
        }
    }

    repr += ") {\n" + body->to_s() + "}";
    return repr;
}

Node* FunctionNode::call(const Vector<ExpressionNode*>& arguments) const
{
    // Push new scope
    Scope::instance().push();
    try
    {
        // Add parameters to current scope
        init_param_scope(arguments);
        // Evaluate body
        Node* result{body->evaluate()};
        // Pop scope
        Scope::instance().pop();
        return result;
    }
    catch (...)
    {
        // Pop scope even if an exception was thrown
        Scope::instance().pop();
        throw;
    }
}

bool FunctionNode::is_mutable_function() const
{
    return is_mutable;
}

String FunctionNode::get_identifier() const
{
    return identifier;
}

const Vector<Pair<TokenType, String>>& FunctionNode::get_parameters() const
{
    return parameters;
}

BlockNode* FunctionNode::get_body() const
{
    return body;
}

bool FunctionNode::is_pattern_matching() const
{
    return is_pattern;
}

bool FunctionNode::matches(const Vector<ExpressionNode*>& arguments) const
{
    // Only match if it's a pattern matching function and the number of arguments matches the number of pattern values
    if (!is_pattern || arguments.size() != pattern_values.size()) { return false; }

    for (size_t i{0}; i < arguments.size(); i++)
    {
        NodeValue pattern_value{pattern_values[i]->get_value()};
        NodeValue argument_value{arguments[i]->get_value()};
        // Check if the pattern value and argument value match
        if ((pattern_value != argument_value).cast<bool>()) { return false; }
    }

    return true;
}

void FunctionNode::init_param_scope(const Vector<ExpressionNode*>& arguments) const
{
    // For pattern matching functions, don't add parameters to the scope
    // Pattern is already checked in matches()
    if (is_pattern) { return; }

    size_t p_count{parameters.size()};
    size_t a_count{arguments.size()};

    // Check if the number of arguments matches the number of parameters
    if (a_count != p_count)
    {
        throw RuntimeError(location,
            "Function '" + identifier + "' expects " + to_str(p_count) + " arguments, but got " + to_str(a_count));
    }

    for (size_t i{0}; i < p_count; i++)
    {
        // Evaluate argument
        ExpressionNode* expr{dynamic_cast<ExpressionNode*>(arguments[i]->evaluate())};
        // Check if the argument is an expression
        if (!expr) { throw RuntimeError(location, "Argument " + to_str(i) + " did not evaluate to an expression"); }
        // Add argument to scope
        VariableNode* var{new VariableNode(location, parameters[i].second, false, parameters[i].first, expr)};
        Scope::instance().add(parameters[i].second, var);
    }
}

} // namespace funk
