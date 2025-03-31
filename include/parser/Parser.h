#pragma once

#include "lexer/Lexer.h"
#include "token/Token.h"
#include "utils/Common.h"

#include "ast/BinaryOpNode.h"
#include "ast/LiteralNode.h"
#include "ast/Node.h"
#include "ast/UnaryOpNode.h"

namespace funk
{
class Parser
{
public:
    Parser(const Vector<Token>& tokens, const String& filename);
    ~Parser();
    Node* parse();

    static Parser load(String filename);

private:
    Vector<Token> tokens;
    String filename;
    int index{0};

    Token next();
    Token peek() const;
    Token peek_next() const;
    Token peek_prev() const;

    bool done() const;
    bool check(TokenType type) const;
    bool match(TokenType expected);

    BinaryOp to_binary_op(const Token& token) const;
    UnaryOp to_unary_op(const Token& token) const;

    Node* parse_statement();
    Node* parse_expression();
    Node* parse_assignment();

    Node* parse_logical_or();
    Node* parse_logical_and();
    Node* parse_equality();
    Node* parse_comparison();
    Node* parse_additive();
    Node* parse_multiplicative();
    Node* parse_unary();
    Node* parse_factor();
    Node* parse_literal();
    Node* parse_identifier();
};
} // namespace funk
