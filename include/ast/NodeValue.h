#pragma once

#include "utils/Common.h"
#include "utils/Exception.h"
#include <cmath>

namespace funk
{

/**
 * @brief Class that wraps a variant to store any primitive value in Funk.
 * Provides type checking, conversion, and operator functionality.
 */
class NodeValue
{
public:
    /**
     * @brief Constructs a NodeValue with no value.
     */
    NodeValue() : value(None{}) {}
    /**
     * @brief Constructs a NodeValue with the given value.
     * @param v The value to initialize with
     */
    NodeValue(int v) : value(v) {}

    /**
     * @brief Constructs a NodeValue with the given value.
     * @param v The value to initialize with
     */
    NodeValue(double v) : value(v) {}

    /**
     * @brief Constructs a NodeValue with the given value.
     * @param v The value to initialize with
     */
    NodeValue(bool v) : value(v) {}

    /**
     * @brief Constructs a NodeValue with the given value.
     * @param v The value to initialize with
     */
    NodeValue(char v) : value(v) {}

    /**
     * @brief Constructs a NodeValue with the given value.
     * @param v The value to initialize with
     */
    NodeValue(const String& v) : value(v) {}

    /**
     * @brief Constructs a NodeValue with the given value.
     * @param v The value to initialize with
     */
    NodeValue(None v) : value(v) {}

    /**
     * @brief Constructs a NodeValue with the given variant.
     * @param v The variant to initialize with
     */
    NodeValue(const std::variant<int, double, bool, char, String, None>& v) : value(v) {}

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

    /**
     * @brief Gets the underlying variant.
     * @return Reference to the underlying variant
     */
    auto& get_variant() const { return value; }

private:
    std::variant<int, double, bool, char, String, None> value; ///< The stored value
};

template <typename Op> NodeValue numeric_op(const NodeValue& lhs, const NodeValue& rhs, Op op);
template <typename Op> NodeValue comparison(const NodeValue& lhs, const NodeValue& rhs, Op op);

// Arithmetic operators
NodeValue operator+(const NodeValue& lhs, const NodeValue& rhs);
NodeValue operator-(const NodeValue& lhs, const NodeValue& rhs);
NodeValue operator*(const NodeValue& lhs, const NodeValue& rhs);
NodeValue operator/(const NodeValue& lhs, const NodeValue& rhs);
NodeValue operator%(const NodeValue& lhs, const NodeValue& rhs);

// Comparison operators
NodeValue operator==(const NodeValue& lhs, const NodeValue& rhs);
NodeValue operator!=(const NodeValue& lhs, const NodeValue& rhs);
NodeValue operator<(const NodeValue& lhs, const NodeValue& rhs);
NodeValue operator<=(const NodeValue& lhs, const NodeValue& rhs);
NodeValue operator>(const NodeValue& lhs, const NodeValue& rhs);
NodeValue operator>=(const NodeValue& lhs, const NodeValue& rhs);

// Logical operators
NodeValue operator&&(const NodeValue& lhs, const NodeValue& rhs);
NodeValue operator||(const NodeValue& lhs, const NodeValue& rhs);

// Power operation
NodeValue pow(const NodeValue& lhs, const NodeValue& rhs);

// Unary operators
NodeValue operator-(const NodeValue& val);
NodeValue operator!(const NodeValue& val);

} // namespace funk
