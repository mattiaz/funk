#include "ast/ExpressionNode.h"

namespace funk
{

ExpressionNode::ExpressionNode(const SourceLocation& loc) : Node(loc) {}

template <typename T> bool ExpressionNode::is_a() const
{
    return std::holds_alternative<T>(get_value());
}

template <typename T> T ExpressionNode::get() const
{
    if (!is_a<T>()) { throw TypeError(location, "Unexpected type"); }
    return std::get<T>(get_value());
}

template <typename T> T ExpressionNode::cast() const
{
    if (is_a<T>()) { return get<T>(); }
    if constexpr (std::is_same_v<T, None>) { throw TypeError(location, "Cannot cast 'none' to type"); }

    NodeValue value{get_value()};

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

    throw TypeError(location, "Cannot cast to type");
}

bool ExpressionNode::is_numeric() const
{
    return is_a<int>() || is_a<double>();
}

bool ExpressionNode::is_nothing() const
{
    return is_a<None>();
}

template bool ExpressionNode::is_a<int>() const;
template bool ExpressionNode::is_a<double>() const;
template bool ExpressionNode::is_a<bool>() const;
template bool ExpressionNode::is_a<char>() const;
template bool ExpressionNode::is_a<String>() const;
template bool ExpressionNode::is_a<None>() const;

template int ExpressionNode::get<int>() const;
template double ExpressionNode::get<double>() const;
template bool ExpressionNode::get<bool>() const;
template char ExpressionNode::get<char>() const;
template String ExpressionNode::get<String>() const;
template None ExpressionNode::get<None>() const;

template int ExpressionNode::cast<int>() const;
template double ExpressionNode::cast<double>() const;
template bool ExpressionNode::cast<bool>() const;
template char ExpressionNode::cast<char>() const;
template String ExpressionNode::cast<String>() const;
template None ExpressionNode::cast<None>() const;

} // namespace funk
