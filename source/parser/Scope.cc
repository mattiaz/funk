#include "parser/Scope.h"

namespace funk
{

Scope::Scope() {}
Scope::~Scope()
{
    for (auto& scope : scopes)
    {
        for (auto& [name, node] : scope) { delete node; }
    }
}

Scope& Scope::instance()
{
    static Scope instance;
    return instance;
}

void Scope::push()
{
    LOG_DEBUG("Pushing scope at depth " + to_str(depth) + " -> " + to_str(depth + 1));
    if (depth++ >= MAX_DEPTH) { throw RuntimeError("Scope stack overflow, max depth is " + to_str(MAX_DEPTH)); }
    scopes.push_back({});
}

void Scope::pop()
{
    LOG_DEBUG("Popping scope at depth " + to_str(depth) + " -> " + to_str(depth - 1));
    if (depth-- <= 0) { throw RuntimeError("Scope stack underflow, can't go below 0"); }
    scopes.pop_back();
}

void Scope::add(const String& name, Node* node)
{
    if (BuiltIn::functions.find(name) != BuiltIn::functions.end())
    {
        throw RuntimeError(node->get_location(), "Cannot overwrite built-in function: " + name);
    }
    if (contains_in_current_scope(name)) {
        LOG_DEBUG("Symbol '" + name + "' already declared in the current scope");
        throw RuntimeError(node->get_location(), "Variable '" + name + "' already declared in the current scope");
    }
    LOG_DEBUG("Registering symbol '" + name + "' with node " + node->to_s());
    scopes.back()[name] = node;
}

Node* Scope::get(const String& name) const
{
    for (int i = scopes.size() - 1; i >= 0; i--)
    {
        LOG_DEBUG("Searching for symbol '" + name + "' at depth " + to_str(i));
        auto it = scopes[i].find(name);
        if (it != scopes[i].end())
        {
            LOG_DEBUG("Found symbol '" + name + "' at depth " + to_str(i));
            return it->second;
        }
    }
    return nullptr;
}

bool Scope::contains(const String& name) const
{
    for (int i = scopes.size() - 1; i >= 0; i--)
    {
        if (scopes[i].find(name) != scopes[i].end()) { return true; }
    }
    return false;
}
bool Scope::contains_in_current_scope(const String& name) const
{
    if (scopes.empty()) return false;
    return scopes.back().find(name) != scopes.back().end();
}

} // namespace funk
