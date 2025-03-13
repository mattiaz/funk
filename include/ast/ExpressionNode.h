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

    /**
     * @brief Checks if the expression's value is of a specific type.
     * @tparam T The type to check for
     * @return True if the value is of type T
     */
    template <typename T> bool is_a() const;

    /**
     * @brief Gets the expression's value as a specific type.
     * @tparam T The type to retrieve
     * @return The value as type T
     * @throws TypeError if the value is not of type T
     */
    template <typename T> T get() const;

    /**
     * @brief Casts the expression's value to a specific type.
     * @tparam T The type to cast to
     * @return The value cast to type T
     * @throws TypeError if the value cannot be cast to type T
     */
    template <typename T> T cast() const;

    /**
     * @brief Checks if the expression's value is numeric (int or double).
     * @return True if the value is numeric
     */
    bool is_numeric() const;

    /**
     * @brief Checks if the expression's value is Nothing (None).
     * @return True if the value is Nothing
     */
    bool is_nothing() const;
};

} // namespace funk
