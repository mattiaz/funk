#include "parser/Parser.h"
#include "logging/LogMacros.h"

namespace funk
{
Parser::Parser(const Vector<Token>& tokens, const String& filename) : tokens(tokens), filename(filename) {}

Parser::~Parser() {}

Node* Parser::parse()
{
    LOG_DEBUG("Parse program");
    return parse_statement();
}

Parser Parser::load(String filename)
{
    Lexer lexer{read_file(filename), filename};
    return Parser(lexer.tokenize(), filename);
}

Token Parser::next()
{
    if (!done()) index++;
    return peek_prev();
}

Token Parser::peek() const
{
    return tokens.at(index);
}

Token Parser::peek_prev() const
{
    return tokens.at(index > 0 ? index - 1 : 0);
}

Token Parser::peek_next() const
{
    return tokens.at(!done() ? index + 1 : tokens.size() - 1);
}

bool Parser::done() const
{
    return index >= static_cast<int>(tokens.size());
}

bool Parser::check(TokenType type) const
{
    return tokens.at(index).get_type() == type;
}

bool Parser::match(TokenType expected)
{
    if (!check(expected)) return false;
    next();
    return true;
}

BinaryOp Parser::to_binary_op(const Token& token) const
{
    switch (token.get_type())
    {
    case TokenType::PLUS: return BinaryOp::PLUS;
    case TokenType::MINUS: return BinaryOp::MINUS;
    case TokenType::MULTIPLY: return BinaryOp::MULTIPLY;
    case TokenType::DIVIDE: return BinaryOp::DIVIDE;
    case TokenType::MODULO: return BinaryOp::MODULO;
    case TokenType::POWER: return BinaryOp::POWER;
    case TokenType::EQUAL: return BinaryOp::EQUAL;
    case TokenType::NOT_EQUAL: return BinaryOp::NOT_EQUAL;
    case TokenType::LESS: return BinaryOp::LESS;
    case TokenType::LESS_EQUAL: return BinaryOp::LESS_EQUAL;
    case TokenType::GREATER: return BinaryOp::GREATER;
    case TokenType::GREATER_EQUAL: return BinaryOp::GREATER_EQUAL;
    case TokenType::AND: return BinaryOp::AND;
    case TokenType::OR: return BinaryOp::OR;

    default: throw SyntaxError(token.get_location(), "Invalid binary operator: " + token.get_lexeme());
    }
}

UnaryOp Parser::to_unary_op(const Token& token) const
{
    switch (token.get_type())
    {
    case TokenType::MINUS: return UnaryOp::NEGATE;
    case TokenType::NOT: return UnaryOp::NOT;

    default: throw SyntaxError(token.get_location(), "Invalid unary operator: " + token.get_lexeme());
    }
}

Node* Parser::parse_statement()
{
    LOG_DEBUG("Parse statement");
    Node* expr{parse_expression()};
    if (!match(TokenType::SEMICOLON)) throw SyntaxError(peek_prev().get_location(), "Expected ';'");
    return expr;
}

Node* Parser::parse_expression()
{
    LOG_DEBUG("Parse expression");
    return parse_assignment();
}

Node* Parser::parse_assignment()
{
    LOG_DEBUG("Parse assignment");
    return parse_logical_or();
}

Node* Parser::parse_logical_or()
{
    LOG_DEBUG("Parse logical or");
    ExpressionNode* left{dynamic_cast<ExpressionNode*>(parse_logical_and())};

    while (match(TokenType::OR))
    {
        Token op{peek_prev()};
        ExpressionNode* right{dynamic_cast<ExpressionNode*>(parse_logical_and())};
        left = new BinaryOpNode(left, to_binary_op(op), right);
    }

    return left;
}

Node* Parser::parse_logical_and()
{
    LOG_DEBUG("Parse logical and");
    ExpressionNode* left{dynamic_cast<ExpressionNode*>(parse_equality())};

    while (match(TokenType::AND))
    {
        Token op{peek_prev()};
        ExpressionNode* right{dynamic_cast<ExpressionNode*>(parse_equality())};
        left = new BinaryOpNode(left, to_binary_op(op), right);
    }

    return left;
}

Node* Parser::parse_equality()
{
    LOG_DEBUG("Parse equality");
    ExpressionNode* left{dynamic_cast<ExpressionNode*>(parse_comparison())};

    while (match(TokenType::EQUAL) || match(TokenType::NOT_EQUAL))
    {
        Token op{peek_prev()};
        ExpressionNode* right{dynamic_cast<ExpressionNode*>(parse_comparison())};
        left = new BinaryOpNode(left, to_binary_op(op), right);
    }

    return left;
}

Node* Parser::parse_comparison()
{
    LOG_DEBUG("Parse comparison");
    ExpressionNode* left{dynamic_cast<ExpressionNode*>(parse_additive())};

    while (match(TokenType::LESS) || match(TokenType::LESS_EQUAL) || match(TokenType::GREATER) ||
           match(TokenType::GREATER_EQUAL))
    {
        Token op{peek_prev()};
        ExpressionNode* right{dynamic_cast<ExpressionNode*>(parse_additive())};
        left = new BinaryOpNode(left, to_binary_op(op), right);
    }

    return left;
}

Node* Parser::parse_additive()
{
    LOG_DEBUG("Parse addative");
    ExpressionNode* left{dynamic_cast<ExpressionNode*>(parse_multiplicative())};

    while (match(TokenType::PLUS) || match(TokenType::MINUS))
    {
        Token op{peek_prev()};
        ExpressionNode* right{dynamic_cast<ExpressionNode*>(parse_multiplicative())};
        left = new BinaryOpNode(left, to_binary_op(op), right);
    }

    return left;
}

Node* Parser::parse_multiplicative()
{
    LOG_DEBUG("Parse multiplicative");
    ExpressionNode* left{dynamic_cast<ExpressionNode*>(parse_unary())};

    while (
        match(TokenType::MULTIPLY) || match(TokenType::DIVIDE) || match(TokenType::MODULO) || match(TokenType::POWER))
    {
        Token op{peek_prev()};
        ExpressionNode* right{dynamic_cast<ExpressionNode*>(parse_unary())};
        left = new BinaryOpNode(left, to_binary_op(op), right);
    }

    return left;
}

Node* Parser::parse_unary()
{
    LOG_DEBUG("Parse unary");
    if (match(TokenType::MINUS) || match(TokenType::NOT))
    {
        Token op{peek_prev()};
        ExpressionNode* right{dynamic_cast<ExpressionNode*>(parse_factor())};
        return new UnaryOpNode(to_unary_op(op), right);
    }

    return parse_factor();
}

Node* Parser::parse_factor()
{
    LOG_DEBUG("Parse factor");
    if (check(TokenType::IDENTIFIER))
        return parse_identifier();
    else if (check(TokenType::NUMB) || check(TokenType::REAL) || check(TokenType::BOOL) || check(TokenType::CHAR) ||
             check(TokenType::TEXT))
    {
        return parse_literal();
    }
    else if (match(TokenType::L_PAR))
    {
        Node* expr{parse_expression()};
        if (!match(TokenType::R_PAR)) throw SyntaxError(peek_prev().get_location(), "Expected ')'");
        return expr;
    }

    throw SyntaxError(peek().get_location(), "???");
}

Node* Parser::parse_literal()
{
    LOG_DEBUG("Parse literal");
    Token literal{next()};
    return new LiteralNode(literal.get_location(), NodeValue(literal.get_value()));
}

Node* Parser::parse_identifier()
{
    return nullptr;
}

} // namespace funk
