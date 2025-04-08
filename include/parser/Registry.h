#pragma once

#include "ast/declaration/FunctionNode.h"

namespace funk
{

/**
 * @brief Forward declaration of FunctionNode.
 */
class FunctionNode;

class Registry
{
public:
    static Registry& instance();

    bool add_function(FunctionNode* node);
    FunctionNode* get_function(const String& identifier, const Vector<ExpressionNode*>& arguments) const;
    void remove_function(const String& identifier);
    bool contains(const String& identifier) const;

private:
    Registry() = default;
    ~Registry() = default;

    HashMap<String, Vector<FunctionNode*>> functions;
};

} // namespace funk
