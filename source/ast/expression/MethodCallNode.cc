#include "ast/expression/MethodCallNode.h"

namespace funk
{
MethodCallNode::MethodCallNode(ExpressionNode* object, const Token& method, const Vector<ExpressionNode*>& args) :
    CallNode(method, args), object(object)
{
}

MethodCallNode::~MethodCallNode()
{
    delete object;
    CallNode::~CallNode();
}

Node* MethodCallNode::evaluate() const
{
    LOG_DEBUG("Evaluating method call " + identifier.get_lexeme() + " on " + object->to_s());

    Node* evaluated_object{object->evaluate()};
    if (!evaluated_object) { throw RuntimeError(location, "Failed to evaluate object for method call"); }

    if (auto list_node = dynamic_cast<ListNode*>(evaluated_object))
    {
        if (identifier.get_lexeme() == "length")
        {
            return new LiteralNode(location, static_cast<int>(list_node->length()));
        }
    }

    throw RuntimeError(
        location, "Unknown method '" + identifier.get_lexeme() + "' for object " + evaluated_object->to_s());
}

String MethodCallNode::to_s() const
{
    String result{object->to_s()};
    result += "." + identifier.get_lexeme() + "( ";

    for (size_t i{0}; i < args.size(); i++)
    {
        result += args[i]->to_s();
        if (i < args.size() - 1) { result += ", "; }
    }

    result += " )";
    return result;
}

NodeValue MethodCallNode::get_value() const
{
    ExpressionNode* result{dynamic_cast<ExpressionNode*>(evaluate())};
    if (!result) { throw RuntimeError(location, "Method call did not evaluate to an expression"); }

    return result->get_value();
}
} // namespace funk
