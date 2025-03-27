#include "ast/NodeValue.h"

namespace funk
{

template <typename T> bool NodeValue::is_a() const
{
    return std::holds_alternative<T>(value);
}

template <typename T> T NodeValue::get() const
{
    if (!is_a<T>()) { throw TypeError("Unexpected type"); }
    return std::get<T>(value);
}

template <typename T> T NodeValue::cast() const
{
    if (is_a<T>()) { return get<T>(); }
    if constexpr (std::is_same_v<T, None>) { throw TypeError("Cannot cast 'none' to type"); }

    if constexpr (std::is_same_v<T, String>)
    {
        if (is_a<int>())
            return std::to_string(get<int>());
        else if (is_a<double>())
            return std::to_string(get<double>());
        else if (is_a<bool>())
            return get<bool>() ? "true" : "false";
        else if (is_a<char>())
            return String(1, get<char>());
        else if (is_a<None>())
            return "none";
    }
    else if constexpr (std::is_same_v<T, int>)
    {
        if (is_a<double>()) { return static_cast<int>(get<double>()); }
        else if (is_a<bool>()) { return get<bool>() ? 1 : 0; }
        else if (is_a<char>()) { return get<char>(); }
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        if (is_a<int>()) { return static_cast<double>(get<int>()); }
        else if (is_a<bool>()) { return get<bool>() ? 1.0 : 0.0; }
        else if (is_a<char>()) { return static_cast<double>(get<char>()); }
    }
    else if constexpr (std::is_same_v<T, bool>)
    {
        if (is_a<int>()) { return get<int>() != 0; }
        else if (is_a<double>()) { return get<double>() != 0.0; }
        else if (is_a<char>()) { return get<char>() != '\0'; }
        else if (is_a<String>()) { return !get<String>().empty(); }
        else if (is_a<None>()) { return false; }
    }
    else if constexpr (std::is_same_v<T, char>)
    {
        if (is_a<int>()) { return static_cast<char>(get<int>()); }
    }

    throw TypeError("Cannot cast to type");
}

bool NodeValue::is_numeric() const
{
    return is_a<int>() || is_a<double>();
}

bool NodeValue::is_nothing() const
{
    return is_a<None>();
}

template <typename Op> NodeValue numeric_op(const NodeValue& lhs, const NodeValue& rhs, Op op)
{
    if (!lhs.is_numeric() || !rhs.is_numeric())
    {
        throw TypeError("Cannot perform arithmetic operation on " + lhs.cast<String>() + " and " + rhs.cast<String>());
    }

    if (lhs.is_a<int>() && rhs.is_a<int>()) { return op(lhs.get<int>(), rhs.get<int>()); }
    else { return op(lhs.cast<double>(), rhs.cast<double>()); }
}

template <typename Op> NodeValue comparison(const NodeValue& lhs, const NodeValue& rhs, Op op)
{
    if (lhs.is_a<int>() && rhs.is_a<int>()) { return op(lhs.get<int>(), rhs.get<int>()); }
    else if (lhs.is_a<double>() && rhs.is_a<double>()) { return op(lhs.get<double>(), rhs.get<double>()); }
    else if (lhs.is_a<bool>() && rhs.is_a<bool>()) { return op(lhs.get<bool>(), rhs.get<bool>()); }
    else if (lhs.is_a<char>() && rhs.is_a<char>()) { return op(lhs.get<char>(), rhs.get<char>()); }
    else if (lhs.is_a<String>() && rhs.is_a<String>()) { return op(lhs.get<String>(), rhs.get<String>()); }
    else if (lhs.is_numeric() && rhs.is_numeric()) { return op(lhs.cast<double>(), rhs.cast<double>()); }

    throw TypeError("Cannot compare values of types " + lhs.cast<String>() + " and " + rhs.cast<String>());
}

NodeValue operator+(const NodeValue& lhs, const NodeValue& rhs)
{
    if (lhs.is_a<String>() && rhs.is_a<String>()) { return lhs.get<String>() + rhs.get<String>(); }

    return numeric_op(lhs, rhs, [](auto a, auto b)
    {
        return a + b;
    });
}

NodeValue operator-(const NodeValue& lhs, const NodeValue& rhs)
{
    return numeric_op(lhs, rhs, [](auto a, auto b)
    {
        return a - b;
    });
}

NodeValue operator*(const NodeValue& lhs, const NodeValue& rhs)
{
    return numeric_op(lhs, rhs, [](auto a, auto b)
    {
        return a * b;
    });
}

NodeValue operator/(const NodeValue& lhs, const NodeValue& rhs)
{
    if ((rhs.is_a<int>() && rhs.get<int>() == 0) || (rhs.is_a<double>() && rhs.get<double>() == 0.0))
    {
        throw RuntimeError("Division by zero");
    }

    return numeric_op(lhs, rhs, [](auto a, auto b)
    {
        return a / b;
    });
}

NodeValue operator%(const NodeValue& lhs, const NodeValue& rhs)
{
    if (lhs.is_a<int>() && rhs.is_a<int>())
    {
        if (rhs.get<int>() == 0) { throw RuntimeError("Modulo by zero"); }
        return lhs.get<int>() % rhs.get<int>();
    }

    throw TypeError("Modulo operation requires integer operands");
}

NodeValue operator==(const NodeValue& lhs, const NodeValue& rhs)
{
    if (lhs.is_a<None>() || rhs.is_a<None>()) { return lhs.is_a<None>() && rhs.is_a<None>(); }
    return comparison(lhs, rhs, [](auto a, auto b)
    {
        return a == b;
    });
}

NodeValue operator!=(const NodeValue& lhs, const NodeValue& rhs)
{
    return comparison(lhs, rhs, [](auto a, auto b)
    {
        return a != b;
    });
}

NodeValue operator<(const NodeValue& lhs, const NodeValue& rhs)
{
    return comparison(lhs, rhs, [](auto a, auto b)
    {
        return a < b;
    });
}

NodeValue operator<=(const NodeValue& lhs, const NodeValue& rhs)
{
    return comparison(lhs, rhs, [](auto a, auto b)
    {
        return a <= b;
    });
}

NodeValue operator>(const NodeValue& lhs, const NodeValue& rhs)
{
    return comparison(lhs, rhs, [](auto a, auto b)
    {
        return a > b;
    });
}

NodeValue operator>=(const NodeValue& lhs, const NodeValue& rhs)
{
    return comparison(lhs, rhs, [](auto a, auto b)
    {
        return a >= b;
    });
}

NodeValue operator&&(const NodeValue& lhs, const NodeValue& rhs)
{
    return comparison(lhs, rhs, [](auto a, auto b)
    {
        return a && b;
    });
}

NodeValue operator||(const NodeValue& lhs, const NodeValue& rhs)
{
    return comparison(lhs, rhs, [](auto a, auto b)
    {
        return a || b;
    });
}

NodeValue pow(const NodeValue& lhs, const NodeValue& rhs)
{
    if (!lhs.is_numeric() || !rhs.is_numeric()) { throw TypeError("Cannot raise non-numeric value to a power"); }

    if (lhs.is_a<int>() && rhs.is_a<int>()) { return static_cast<int>(std::pow(lhs.get<int>(), rhs.get<int>())); }
    else { return std::pow(lhs.cast<double>(), rhs.cast<double>()); }
}

NodeValue operator-(const NodeValue& val)
{
    if (!val.is_numeric()) { throw TypeError("Cannot negate non-numeric value"); }

    if (val.is_a<int>()) { return -val.get<int>(); }
    return -val.cast<double>();
}

NodeValue operator!(const NodeValue& val)
{
    if (!val.is_a<bool>()) { throw TypeError("Cannot apply logical NOT to non-boolean value"); }
    return !val.get<bool>();
}

template bool NodeValue::is_a<int>() const;
template bool NodeValue::is_a<double>() const;
template bool NodeValue::is_a<bool>() const;
template bool NodeValue::is_a<char>() const;
template bool NodeValue::is_a<String>() const;
template bool NodeValue::is_a<None>() const;

template int NodeValue::get<int>() const;
template double NodeValue::get<double>() const;
template bool NodeValue::get<bool>() const;
template char NodeValue::get<char>() const;
template String NodeValue::get<String>() const;
template None NodeValue::get<None>() const;

template int NodeValue::cast<int>() const;
template double NodeValue::cast<double>() const;
template bool NodeValue::cast<bool>() const;
template char NodeValue::cast<char>() const;
template String NodeValue::cast<String>() const;
template None NodeValue::cast<None>() const;

} // namespace funk
