#include "parser/BuiltIn.h"

namespace funk
{

Node* BuiltIn::print(const CallNode& call, const Vector<ExpressionNode*>& args)
{
    for (ExpressionNode* arg : args)
    {
        ExpressionNode* result{dynamic_cast<ExpressionNode*>(arg->evaluate())};
        if (!result) { throw RuntimeError(arg->get_location(), "Print argument did not evaluate to an expression"); }
        cout << result->get_value().cast<String>() << " ";
    }
    cout << endl;
    return new LiteralNode(call.get_location(), None{});
}

Node* BuiltIn::read(const CallNode& call, const Vector<ExpressionNode*>& args)
{
    if (!args.empty()) { print(call, args); }
    String input;
    getline(cin, input);
    return new LiteralNode(call.get_location(), input);
}

Node* BuiltIn::fast_exit(const CallNode& call [[maybe_unused]], const Vector<ExpressionNode*>& args)
{
    int status{0};
    if (!args.empty()) { status = dynamic_cast<LiteralNode*>(args[0]->evaluate())->get_value().cast<int>(); }

    exit(status);
}

HashMap<String, Node* (*)(const CallNode&, const Vector<ExpressionNode*>&)> BuiltIn::functions{
    {"print", print}, {"read", read}, {"exit", fast_exit}};

} // namespace funk
