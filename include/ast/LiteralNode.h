/**
 * @file LiteralNode.h
 * @brief Defines the LiteralNode class for representing literal values in the Funk AST.
 */
#pragma once

#include "ast/ExpressionNode.h"

namespace funk
{

/**
 * @brief Node representing a literal value in the Funk AST.
 * LiteralNode represents constant values like numbers, strings, booleans, etc. that appear directly in the source code.
 */
class LiteralNode : public ExpressionNode
{
public:
    /**
     * @brief Constructs a literal node with source location and value.
     * @param loc Source location information
     * @param value The literal value
     */
    LiteralNode(const SourceLocation& loc, NodeValue value);

    /**
     * @brief Evaluates the literal node.
     * @return Pointer to the node representing the evaluation result (self for literals)
     */
    Node* evaluate() override;

    /**
     * @brief Converts the literal to a string representation.
     * @return String representation of the literal value
     */
    String to_s() const override;

    /**
     * @brief Gets the value of this literal.
     * @return The literal value
     */
    NodeValue get_value() const;

private:
    NodeValue value; ///< The actual value of this literal
};

} // namespace funk
