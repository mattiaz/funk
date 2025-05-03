#include "ast/expression/PipeNode.h"

namespace funk
{

PipeNode::PipeNode(const SourceLocation& location, ExpressionNode* source, ExpressionNode* target) :
    ExpressionNode(location), source(source), target(target)
{
}

PipeNode::~PipeNode()
{
    delete source;
    delete target;
}

Node* PipeNode::evaluate() const
{
    // Evaluate the source expression
    ExpressionNode* current{dynamic_cast<ExpressionNode*>(source->evaluate())};
    if (!current) { throw RuntimeError(location, "Pipe source did not evaluate to an expression"); }

    // Create a list of arguments for the target function, starting with the source expression
    Vector<ExpressionNode*> args{current};

    if (auto call = dynamic_cast<CallNode*>(target))
    {
        // Get the function's name and original arguments
        const String name = call->get_identifier().get_lexeme();
        const Vector<ExpressionNode*> call_args = call->get_args();

        // Add the original call arguments after the piped value
        args.insert(args.end(), call_args.begin(), call_args.end());

        // Create a new call node with the updated arguments
        CallNode* new_call{new CallNode(call->get_identifier(), args)};

        // Evaluate the new call node
        return new_call->evaluate();
    }
    else if (auto func = dynamic_cast<FunctionNode*>(target)) { return func->call(args); }
    else { throw RuntimeError(location, "Pipe target must be a function or function identifier"); }
}

String PipeNode::to_s() const
{
    return source->to_s() + " >> " + target->to_s();
}

NodeValue PipeNode::get_value() const
{
    return target->get_value();
}

ExpressionNode* PipeNode::get_source() const
{
    return source;
}

ExpressionNode* PipeNode::get_target() const
{
    return target;
}

} // namespace funk
