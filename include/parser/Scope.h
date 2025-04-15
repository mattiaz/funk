#pragma once

#include "ast/Node.h"
#include "logging/LogMacros.h"
#include "utils/Common.h"
#include "utils/Exception.h"
#include "BuiltIn.h"

namespace funk
{

class Scope
{
public:
    static Scope& instance();
    static const int MAX_DEPTH = 1000;

    void push();
    void pop();

    void add(const String& name, Node* node);
    Node* get(const String& name) const;
    bool contains(const String& name) const;
    bool contains_in_current_scope(const String& name) const;

private:
    Scope();
    ~Scope();
    Vector<HashMap<String, Node*>> scopes;
    int depth{0};
};

} // namespace funk
