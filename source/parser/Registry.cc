#include "parser/Registry.h"

namespace funk
{

Registry& Registry::instance()
{
    static Registry registry;
    return registry;
}

bool Registry::add_function(FunctionNode* function)
{
    // TODO: Check for duplicate functions for the same identifier and arguments
    functions[function->get_identifier()].push_back(function);
    return true;
}

FunctionNode* Registry::get_function(const String& identifier, const Vector<ExpressionNode*>& arguments) const
{
    // Check if the function exists
    if (functions.find(identifier) == functions.end()) { return nullptr; }

    // Check if the function is a pattern matching function
    for (FunctionNode* function : functions.at(identifier))
    {
        if (function->is_pattern_matching() && function->matches(arguments)) { return function; }
    }

    // Check if the function is a regular function
    for (FunctionNode* function : functions.at(identifier))
    {
        if (!function->is_pattern_matching() && function->get_parameters().size() == arguments.size())
        {
            return function;
        }
    }

    return nullptr;
}

void Registry::remove_function(const String& identifier)
{
    functions.erase(identifier);
}

bool Registry::contains(const String& identifier) const
{
    return functions.find(identifier) != functions.end();
}

} // namespace funk
