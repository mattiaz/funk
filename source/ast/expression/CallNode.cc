#include "ast/expression/CallNode.h"

namespace funk
{
CallNode::CallNode(const Token& identifier, const Vector<ExpressionNode*>& args) :
    ExpressionNode(identifier.get_location()), identifier(identifier), args(args)
{
}

CallNode::~CallNode()
{
    for (Node* arg : args) { delete arg; }
}

Node* CallNode::evaluate() const
{
    LOG_DEBUG("Evaluating call to " + identifier.get_lexeme());

    // Check the registry first for pattern matching and overloaded functions
    FunctionNode* func{Registry::instance().get_function(identifier.get_lexeme(), args)};
    if (func)
    {
        LOG_DEBUG("Found function in registry: " + func->get_identifier());
        return func->call(args);
    }

    // // Check the current scope next for regular functions
    // func = dynamic_cast<FunctionNode*>(Scope::instance().get(identifier.get_lexeme()));
    // if (func)
    // {
    //     LOG_DEBUG("Found function in scope: " + func->get_identifier());
    //     return func->call(args);
    // }

    // Finally, check the built-in functions
    auto it = BuiltIn::functions.find(identifier.get_lexeme());
    if (it != BuiltIn::functions.end())
    {
        LOG_DEBUG("Found built-in function: " + identifier.get_lexeme());
        return it->second(*this, args);
    }

    throw RuntimeError(location, "Unknown function: " + identifier.get_lexeme());
}

String CallNode::to_s() const
{
    String result{identifier.get_lexeme()};
    result += "( ";
    for (size_t i{0}; i < args.size(); i++)
    {
        result += args[i]->to_s();
        if (i < args.size() - 1) { result += ", "; }
    }
    result += " )";
    return result;
}

NodeValue CallNode::get_value() const
{
    ExpressionNode* result{dynamic_cast<ExpressionNode*>(evaluate())};
    if (!result) { throw RuntimeError(location, "Call did not evaluate to an expression"); }

    return result->get_value();
}

const Token& CallNode::get_identifier() const
{
    return identifier;
}

const Vector<ExpressionNode*>& CallNode::get_args() const
{
    return args;
}

} // namespace funk
