#include "ast/operators/BinaryOpNode.h"
#include "ast/literals/NumbNode.h"

namespace funk
{

BinaryOpNode::BinaryOpNode(const SourceLocation& loc, TokenType op, Node* left, Node* right) :
    Node(loc), op(op), left(left), right(right)
{
}

Node* BinaryOpNode::evaluate()
{
    Node* l_result = left->evaluate();
    Node* r_result = right->evaluate();
    NumbNode* l_numb = dynamic_cast<NumbNode*>(l_result);
    NumbNode* r_numb = dynamic_cast<NumbNode*>(r_result);

    if (l_numb && r_numb)
    {
        double l_value = l_numb->get_value();
        double r_value = r_numb->get_value();

        switch (op)
        {
        case TokenType::PLUS: return new NumbNode(location, l_value + r_value);
        case TokenType::MINUS: return new NumbNode(location, l_value - r_value);
        case TokenType::MULTIPLY: return new NumbNode(location, l_value * r_value);
        case TokenType::DIVIDE: return new NumbNode(location, l_value / r_value);
        case TokenType::PERCENT: throw std::runtime_error("Real node is not yet implemented");
        default: throw std::runtime_error("Invalid binary operator");
        }
    }

    throw std::runtime_error("Invalid binary operation");
}

String BinaryOpNode::to_s() const
{
    return "(" + left->to_s() + " " + token_type_to_string(op) + " " + right->to_s() + ")";
}

Node* BinaryOpNode::get_left() const
{
    return left;
}

Node* BinaryOpNode::get_right() const
{
    return right;
}

} // namespace funk
