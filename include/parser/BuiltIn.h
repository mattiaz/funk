#pragma once

#include "ast/expression/CallNode.h"
#include "ast/expression/LiteralNode.h"
#include "logging/LogMacros.h"

namespace funk
{
/**
 * @brief Forward declaration of CallNode.
 */
class CallNode;

class BuiltIn
{
public:
    static Node* print(const CallNode& call, const Vector<ExpressionNode*>& args);
    static Node* read(const CallNode& call, const Vector<ExpressionNode*>& args);

    static HashMap<String, Node* (*)(const CallNode&, const Vector<ExpressionNode*>&)> functions;
};
} // namespace funk
