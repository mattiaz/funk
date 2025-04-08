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
    scopes.push_back({});
    depth++;
}

void Scope::pop()
{
    LOG_DEBUG("Popping scope at depth " + to_str(depth) + " -> " + to_str(depth - 1));
    scopes.pop_back();
    depth--;
}

void Scope::add(const String& name, Node* node)
{
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

} // namespace funk
