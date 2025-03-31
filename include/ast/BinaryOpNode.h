/**
 * @file BinaryOpNode.h
 * @brief Defines the BinaryOpNode class for representing binary operations in the Funk AST.
 */
#pragma once

#include "ast/ExpressionNode.h"
#include "ast/LiteralNode.h"
#include "token/Token.h"

namespace funk
{

/**
 * @brief Class representing a binary operation in the Funk AST.
 *
 * BinaryOpNode represents operations that require two operands (left and right)
 * and an operator. These include arithmetic operations like addition and
 * multiplication, as well as comparison operations like equality and greater than.
 */
class BinaryOpNode : public ExpressionNode
{
public:
    /**
     * @brief Constructs a binary operation node with left and right expressions and an operator.
     * @param left The left-hand side expression
     * @param op The binary operator to apply
     * @param right The right-hand side expression
     */
    BinaryOpNode(ExpressionNode* left, const Token& op, ExpressionNode* right);

    /**
     * @brief Virtual destructor for proper cleanup of resources.
     */
    ~BinaryOpNode() override;

    /**
     * @brief Evaluates the binary operation.
     * @return A node representing the result of applying the operator to the operands
     */
    Node* evaluate() const override;

    /**
     * @brief Converts the binary operation to a string representation.
     * @return String representation of the binary operation
     */
    String to_s() const override;

    /**
     * @brief Gets the value that this binary operation evaluates to.
     * @return The evaluated value of this binary operation
     */
    NodeValue get_value() const override;

    /**
     * @brief Gets the binary operator used in this operation.
     * @return The binary operator
     */
    Token get_op() const;

    /**
     * @brief Gets the left-hand side expression of the binary operation.
     * @return Pointer to the left expression
     */
    ExpressionNode* get_left() const;

    /**
     * @brief Gets the right-hand side expression of the binary operation.
     * @return Pointer to the right expression
     */
    ExpressionNode* get_right() const;

private:
    Token op;              ///< The binary operator
    ExpressionNode* left;  ///< The left-hand side expression
    ExpressionNode* right; ///< The right-hand side expression
};

} // namespace funk
