#include "parser/Parser.h"
#include "logging/LogMacros.h"

namespace funk
{
Parser::Parser(const Vector<Token>& tokens, const String& filename) : tokens(tokens), filename(filename) {}

Parser::~Parser() {}

Node* Parser::parse()
{
    LOG_DEBUG("Parse program");

    BlockNode* block = new BlockNode(SourceLocation(filename, 0, 0));
    while (!done()) { block->add(parse_statement()); }
    return block;
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
    return peek().get_type() == TokenType::EOF_TOKEN;
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

Node* Parser::parse_statement()
{
    LOG_DEBUG("Parse statement");

    Node* decl{parse_declaration()};
    Node* expr{parse_expression()};

    if (!match(TokenType::SEMICOLON))
    {
        Token prev{peek_prev()};
        SourceLocation loc{prev.get_location()};
        SourceLocation error_loc(loc.filename, loc.line, static_cast<int>(loc.column + prev.get_lexeme().length()));
        throw SyntaxError(error_loc, "Expected ';'");
    }

    if (decl) { return decl; }
    return expr;
}

Node* Parser::parse_declaration()
{
    LOG_DEBUG("Parse declaration");

    bool mut{false};
    if (check(TokenType::MUT))
    {
        mut = true;
        next();
    }
    if (check(TokenType::NUMB_TYPE) || check(TokenType::REAL_TYPE) || check(TokenType::BOOL_TYPE) ||
        check(TokenType::CHAR_TYPE) || check(TokenType::TEXT_TYPE))
    {
        Token type{next()};
        if (check(TokenType::IDENTIFIER))
        {
            Token identifier{next()};

            if (match(TokenType::ASSIGN))
            {
                // needs to be parse_statement otherwise whines about semicolon dunno if I do it correctly
                Node* expr{parse_statement()};
                if (!expr) { throw SyntaxError(peek_prev().get_location(), "Expected expression after '='"); }

                ExpressionNode* expr_node = dynamic_cast<ExpressionNode*>(expr);

                return new DeclarationNode(
                    type.get_location(), mut, type.get_type(), identifier.get_lexeme(), expr_node);
            }
            return new DeclarationNode(type.get_location(), mut, type.get_type(), identifier.get_lexeme());
        }
    }

    return nullptr;
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
        left = new BinaryOpNode(left, op, right);
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
        left = new BinaryOpNode(left, op, right);
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
        left = new BinaryOpNode(left, op, right);
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
        left = new BinaryOpNode(left, op, right);
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
        left = new BinaryOpNode(left, op, right);
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
        left = new BinaryOpNode(left, op, right);
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
        return new UnaryOpNode(op, right);
    }

    return parse_factor();
}

Node* Parser::parse_factor()
{
    LOG_DEBUG("Parse factor");
    if (check(TokenType::IDENTIFIER)) { return parse_identifier(); }
    else if (check(TokenType::NUMB) || check(TokenType::REAL) || check(TokenType::BOOL) || check(TokenType::CHAR) ||
             check(TokenType::TEXT))
    {
        return parse_literal();
    }
    else if (match(TokenType::L_PAR))
    {
        Node* expr{parse_expression()};

        if (!match(TokenType::R_PAR))
        {
            Token prev{peek_prev()};
            SourceLocation loc{prev.get_location()};
            SourceLocation error_loc(loc.filename, loc.line, static_cast<int>(loc.column + prev.get_lexeme().length()));
            throw SyntaxError(error_loc, "Expected ')'");
        }

        return expr;
    }

    throw SyntaxError(peek_prev().get_location(), "Expected expression, got " + token_type_to_s(peek().get_type()));
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
