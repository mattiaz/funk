/**
 * @file Node.h
 * @brief Defines the base Node class for the Abstract Syntax Tree (AST) in the Funk language.
 */
#pragma once

#include "utils/Common.h"
#include "utils/Exception.h"

namespace funk
{

/**
 * @brief Variant type that can hold any of the primitive values in Funk.
 * Represents the possible runtime values that a node in the AST can evaluate to.
 */
using NodeValue = std::variant<int, double, bool, char, String, None>;

/**
 * @brief Abstract base class for all AST nodes in the Funk language.
 * Defines the common interface that all AST nodes must implement, including evaluation and string representation.
 */
class Node
{
public:
    /**
     * @brief Constructs a node with a source location.
     * @param loc Source location information
     */
    Node(const SourceLocation& loc);

    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Node() = default;

    /**
     * @brief Evaluates the node and returns the result.
     * @return Pointer to the node representing the evaluation result
     */
    virtual Node* evaluate() = 0;

    /**
     * @brief Converts the node to a string representation.
     * @return String representation of the node
     */
    virtual String to_s() const = 0;

    /**
     * @brief Gets the source location of the node.
     * @return Source location information
     */
    SourceLocation get_location() const;

protected:
    SourceLocation location; ///< Source location where this node appears in the code
};

} // namespace funk
