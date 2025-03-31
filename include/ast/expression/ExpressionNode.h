/**
 * @file ExpressionNode.h
 * @brief Defines the ExpressionNode class for representing expressions in the Funk AST.
 */
#pragma once

#include "ast/Node.h"

namespace funk
{

/**
 * @brief Abstract base class for all expression nodes in the Funk AST.
 * ExpressionNode extends Node to add functionality for evaluating to a value and performing type checking operations.
 */
class ExpressionNode : public Node
{
public:
    /**
     * @brief Constructs an expression node with source location information.
     * @param loc Source location information
     */
    ExpressionNode(const SourceLocation& loc);

    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    ~ExpressionNode() override = default;

    /**
     * @brief Gets the value that this expression evaluates to.
     * @return The evaluated value of this expression
     */
    virtual NodeValue get_value() const = 0;
};

} // namespace funk
