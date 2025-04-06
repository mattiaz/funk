#include "parser/Parser.h"

namespace funk
{
Parser::Parser(const Vector<Token>& tokens, const String& filename) : tokens(tokens), filename(filename) {}

Parser::~Parser() {}

Node* Parser::parse(const Vector<String>& args)
{
    LOG_DEBUG("Parse program");

    if (!args.empty())
    {
        String arg_list{};
        for (const String& arg : args) { arg_list += arg + ", "; }
        LOG_INFO("Arguments: " + arg_list.substr(0, arg_list.length() - 2));
    }

    // TODO: Handle arguments

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

    Node* control{parse_control()};
    if (control) { return control; }

    Node* decl{parse_declaration()};
    if (decl) { return decl; }

    Node* expr{parse_expression()};
    if (!expr) { throw SyntaxError(peek().get_location(), "Expected statement"); }

    if (!match(TokenType::SEMICOLON))
    {
        Token prev{peek_prev()};
        SourceLocation loc{prev.get_location()};
        SourceLocation error_loc(loc.filename, loc.line, static_cast<int>(loc.column + prev.get_lexeme().length()));
        throw SyntaxError(error_loc, "Expected ';'");
    }

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

Node* Parser::parse_block()
{
    LOG_DEBUG("Parse block");
    if (!match(TokenType::L_BRACE)) { throw SyntaxError(peek().get_location(), "Expected '{'"); }

    Vector<Node*> statements{};
    while (!check(TokenType::R_BRACE) && !done()) { statements.push_back(parse_statement()); }

    if (!match(TokenType::R_BRACE)) { throw SyntaxError(peek().get_location(), "Expected '}'"); }

    return new BlockNode(statements.at(0)->get_location(), statements);
}

Node* Parser::parse_control()
{
    LOG_DEBUG("Parse control flow");
    if (match(TokenType::IF)) { return parse_if(); }
    if (match(TokenType::WHILE)) { return parse_while(); }
    return nullptr;
}

Node* Parser::parse_if()
{
    LOG_DEBUG("Parse if");
    if (!match(TokenType::L_PAR)) { throw SyntaxError(peek().get_location(), "Expected '('"); }

    ExpressionNode* condition{dynamic_cast<ExpressionNode*>(parse_expression())};
    if (!match(TokenType::R_PAR)) { throw SyntaxError(peek().get_location(), "Expected ')'"); }

    BlockNode* body{dynamic_cast<BlockNode*>(parse_block())};
    Node* else_branch{nullptr};
    if (match(TokenType::ELSE))
    {
        if (match(TokenType::IF)) { else_branch = parse_if(); }
        else { else_branch = parse_block(); }
    }
    return new IfNode(condition, body, else_branch);
}

Node* Parser::parse_while()
{
    LOG_DEBUG("Parse while loop");
    if (!match(TokenType::L_PAR)) { throw SyntaxError(peek().get_location(), "Expected '('"); }
    ExpressionNode* condition{dynamic_cast<ExpressionNode*>(parse_expression())};
    if (!match(TokenType::R_PAR)) { throw SyntaxError(peek().get_location(), "Expected ')'"); }
    BlockNode* body{dynamic_cast<BlockNode*>(parse_block())};
    return new WhileNode(condition, body);
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
    Node* expr = nullptr;

    if (check(TokenType::IDENTIFIER)) { expr = parse_identifier(); }
    else if (check(TokenType::NUMB) || check(TokenType::REAL) || check(TokenType::BOOL) || check(TokenType::CHAR) ||
             check(TokenType::TEXT))
    {
        expr = parse_literal();
    }
    else if (match(TokenType::L_PAR))
    {
        expr = parse_expression();
        if (!match(TokenType::R_PAR)) { throw SyntaxError(peek().get_location(), "Expected ')'"); }
    }
    else if (check(TokenType::L_BRACKET)) { expr = parse_list(); }
    else { throw SyntaxError(peek().get_location(), "Expected expression, got " + token_type_to_s(peek().get_type())); }

    while (match(TokenType::DOT)) { expr = parse_method_call(dynamic_cast<ExpressionNode*>(expr)); }

    return expr;
}

Node* Parser::parse_literal()
{
    LOG_DEBUG("Parse literal");
    Token literal{next()};
    return new LiteralNode(literal.get_location(), NodeValue(literal.get_value()));
}

Node* Parser::parse_identifier()
{
    LOG_DEBUG("Parse identifier");
    Token identifier{next()};

    if (check(TokenType::L_PAR)) { return parse_call(identifier); }
    else if (match(TokenType::DOT))
    {
        return parse_method_call(
            new VariableNode(identifier.get_location(), identifier.get_lexeme(), false, TokenType::NONE, nullptr));
    }

    return new VariableNode(identifier.get_location(), identifier.get_lexeme());
}

Node* Parser::parse_call(const Token& identifier)
{
    LOG_DEBUG("Parse call");

    if (!match(TokenType::L_PAR)) { throw SyntaxError(peek().get_location(), "Expected '('"); }

    Vector<ExpressionNode*> arguments{};
    if (!check(TokenType::R_PAR))
    {
        do {
            arguments.push_back(dynamic_cast<ExpressionNode*>(parse_expression()));
        } while (match(TokenType::COMMA));
    }
    if (!match(TokenType::R_PAR)) { throw SyntaxError(peek().get_location(), "Expected ')'"); }
    return new CallNode(identifier, arguments);
}

Node* Parser::parse_method_call(ExpressionNode* object)
{
    LOG_DEBUG("Parse method call");
    if (!check(TokenType::IDENTIFIER)) { throw SyntaxError(peek().get_location(), "Expected method name after '.'"); }

    Token method{next()};

    if (!match(TokenType::L_PAR)) { throw SyntaxError(peek().get_location(), "Expected '(' after method name"); }

    Vector<ExpressionNode*> arguments{};
    if (!check(TokenType::R_PAR))
    {
        do {
            arguments.push_back(dynamic_cast<ExpressionNode*>(parse_expression()));
        } while (match(TokenType::COMMA));
    }

    if (!match(TokenType::R_PAR)) { throw SyntaxError(peek().get_location(), "Expected ')' after method arguments"); }

    return new MethodCallNode(object, method, arguments);
}

Node* Parser::parse_list()
{
    LOG_DEBUG("Parse list");
    if (!match(TokenType::L_BRACKET)) { throw SyntaxError(peek().get_location(), "Expected '['"); }

    Vector<ExpressionNode*> elements{};
    TokenType type{TokenType::NONE};

    if (!check(TokenType::R_BRACKET))
    {
        do {
            if (type == TokenType::NONE) { type = peek().get_type(); }
            else if (type != peek().get_type()) { throw SyntaxError(peek().get_location(), "Inconsistent list types"); }
            elements.push_back(dynamic_cast<ExpressionNode*>(parse_expression()));
        } while (match(TokenType::COMMA));
    }

    if (!match(TokenType::R_BRACKET)) { throw SyntaxError(peek().get_location(), "Expected ']'"); }
    return new ListNode(peek_prev().get_location(), type, elements);
}

} // namespace funk
