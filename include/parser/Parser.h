/**
 * @file Parser.h
 * @brief Definition of the Parser class for syntactic analysis in the Funk language
 * This file defines the Parser class which performs syntactic analysis on
 * a stream of tokens, converting them into an Abstract Syntax Tree (AST).
 */
#pragma once

#include "lexer/Lexer.h"
#include "parser/Scope.h"
#include "token/Token.h"
#include "utils/Common.h"

#include "ast/BlockNode.h"
#include "ast/Node.h"
#include "ast/declaration/DeclarationNode.h"
#include "ast/expression/BinaryOpNode.h"
#include "ast/expression/LiteralNode.h"
#include "ast/expression/UnaryOpNode.h"

namespace funk
{
/**
 * @brief Class responsible for syntactic analysis in the Funk language
 * The Parser analyzes a stream of tokens according to the grammar rules
 * of the Funk language and builds an Abstract Syntax Tree (AST) that
 * represents the structure and semantics of the program.
 */
class Parser
{
public:
    /**
     * @brief Constructs a parser for the given token stream
     * @param tokens The tokens to parse
     * @param filename The name of the file being processed (for error reporting)
     */
    Parser(const Vector<Token>& tokens, const String& filename);

    /**
     * @brief Destructor for the Parser class
     */
    ~Parser();

    /**
     * @brief Parses the token stream and returns the root AST node
     * @return Node* The root node of the parsed AST
     */
    Node* parse();

    /**
     * @brief Creates a parser from a file
     * @param filename The path to the file to parse
     * @return Parser A parser initialized with tokens from the file
     */
    static Parser load(String filename);

private:
    Vector<Token> tokens; ///< The token stream to parse
    String filename;      ///< The name of the source file
    int index{0};         ///< Current index in the token stream

    /**
     * @brief Advances the index and returns the token at the new index
     * @return Token The next token
     */
    Token next();

    /**
     * @brief Returns the token at the current index without advancing
     * @return Token The current token
     */
    Token peek() const;

    /**
     * @brief Returns the token at the next index without advancing
     * @return Token The next token
     */
    Token peek_next() const;

    /**
     * @brief Returns the token at the previous index
     * @return Token The previous token
     */
    Token peek_prev() const;

    /**
     * @brief Checks if the end of the token stream has been reached
     * @return bool True if the parser has reached the end of the tokens
     */
    bool done() const;

    /**
     * @brief Checks if the current token is of the expected type
     * @param type The token type to check for
     * @return bool True if the current token matches the expected type
     */
    bool check(TokenType type) const;

    /**
     * @brief Checks if the current token matches the expected type, and advances if it does
     * @param expected The token type to check for
     * @return bool True if the current token matched and the index was advanced
     */
    bool match(TokenType expected);

    /**
     * @brief Parses a statement
     * @return Node* The AST node representing the statement
     */
    Node* parse_statement();

    /**
     * @brief Parses a declaration
     * @return Node* The AST node representing the declaration
     */
    Node* parse_declaration();

    /**
     * @brief Parses an expression
     * @return Node* The AST node representing the expression
     */
    Node* parse_expression();

    /**
     * @brief Parses an assignment expression
     * @return Node* The AST node representing the assignment
     */
    Node* parse_assignment();

    /**
     * @brief Parses a logical OR expression
     * @return Node* The AST node representing the logical OR expression
     */
    Node* parse_logical_or();

    /**
     * @brief Parses a logical AND expression
     * @return Node* The AST node representing the logical AND expression
     */
    Node* parse_logical_and();

    /**
     * @brief Parses an equality expression
     * @return Node* The AST node representing the equality expression
     */
    Node* parse_equality();

    /**
     * @brief Parses a comparison expression
     * @return Node* The AST node representing the comparison expression
     */
    Node* parse_comparison();

    /**
     * @brief Parses an additive expression
     * @return Node* The AST node representing the additive expression
     */
    Node* parse_additive();

    /**
     * @brief Parses a multiplicative expression
     * @return Node* The AST node representing the multiplicative expression
     */
    Node* parse_multiplicative();

    /**
     * @brief Parses a unary expression
     * @return Node* The AST node representing the unary expression
     */
    Node* parse_unary();

    /**
     * @brief Parses a factor expression
     * @return Node* The AST node representing the factor expression
     */
    Node* parse_factor();

    /**
     * @brief Parses a literal value
     * @return Node* The AST node representing the literal value
     */
    Node* parse_literal();

    /**
     * @brief Parses an identifier
     * @return Node* The AST node representing the identifier
     */
    Node* parse_identifier();
};
} // namespace funk
