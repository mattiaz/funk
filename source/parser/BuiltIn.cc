#include "parser/BuiltIn.h"

namespace funk
{

Node* BuiltIn::print(const CallNode& call, const Vector<ExpressionNode*>& args)
{
    LOG_DEBUG("Executing print");
    if (args.empty()) { cout << "\n"; }
    for (ExpressionNode* arg : args)
    {
        ExpressionNode* result{dynamic_cast<ExpressionNode*>(arg->evaluate())};
        if (!result) { throw RuntimeError(arg->get_location(), "Print argument did not evaluate to an expression"); }
        cout << result->get_value().cast<String>() << "\n";
    }
    return new LiteralNode(call.get_location(), None{});
}

Node* BuiltIn::read(const CallNode& call, const Vector<ExpressionNode*>& args)
{
    LOG_DEBUG("Executing read");
    if (!args.empty()) { print(call, args); }
    String input;
    getline(cin, input);
    return new LiteralNode(call.get_location(), input);
}

HashMap<String, Node* (*)(const CallNode&, const Vector<ExpressionNode*>&)> BuiltIn::functions{
    {"print", print}, {"read", read}};

} // namespace funk
