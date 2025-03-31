/**
 * @file UnaryOpNode.h
 * @brief Defines the UnaryOpNode class for representing unary operations in the Funk AST.
 */
#pragma once

#include "ast/ExpressionNode.h"
#include "ast/LiteralNode.h"
#include "token/Token.h"

namespace funk
{

/**
 * @brief Class representing a unary operation in the Funk AST.
 *
 * UnaryOpNode represents operations that require one operand and
 * an operator. These include arithmetic negation and logical NOT.
 */
class UnaryOpNode : public ExpressionNode
{
public:
    /**
     * @brief Constructs a unary operation node with an expression and an operator.
     * @param op The unary operator to apply
     * @param expr The expression to apply the operator to
     */
    UnaryOpNode(const Token& op, ExpressionNode* expr);

    /**
     * @brief Virtual destructor for proper cleanup of resources.
     */
    ~UnaryOpNode() override;

    /**
     * @brief Evaluates the unary operation.
     * @return A node representing the result of applying the operator to the operand
     */
    Node* evaluate() const override;

    /**
     * @brief Converts the unary operation to a string representation.
     * @return String representation of the unary operation
     */
    String to_s() const override;

    /**
     * @brief Gets the value that this unary operation evaluates to.
     * @return The evaluated value of this unary operation
     */
    NodeValue get_value() const override;

    /**
     * @brief Gets the unary operator used in this operation.
     * @return The unary operator
     */
    Token get_op() const;

    /**
     * @brief Gets the expression that the operator is applied to.
     * @return Pointer to the expression
     */
    ExpressionNode* get_expr() const;

private:
    Token op;             ///< The unary operator
    ExpressionNode* expr; ///< The expression to apply the operator to
};

} // namespace funk
