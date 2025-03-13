#include "ast/NodeValue.h"
#include "utils/Common.h"
#include <gtest/gtest.h>

using namespace funk;

class TestNodeValue : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Setup code if needed
    }

    void TearDown() override
    {
        // Cleanup code if needed
    }
};

TEST_F(TestNodeValue, Integer)
{
    NodeValue value{5};
    ASSERT_TRUE(value.is_numeric());
    ASSERT_TRUE(value.is_a<int>());
    ASSERT_FALSE(value.is_a<double>());
    ASSERT_FALSE(value.is_nothing());
    ASSERT_EQ(value.get<int>(), 5);
    ASSERT_THROW(value.get<double>(), TypeError);
    ASSERT_THROW(value.cast<None>(), TypeError);
    ASSERT_EQ(value.cast<double>(), 5.0);
    ASSERT_EQ(value.cast<bool>(), true);
    ASSERT_EQ(value.cast<char>(), static_cast<char>(5));
    ASSERT_EQ(value.cast<String>(), "5");
}

TEST_F(TestNodeValue, Double)
{
    NodeValue value{3.14};
    ASSERT_TRUE(value.is_numeric());
    ASSERT_FALSE(value.is_a<int>());
    ASSERT_TRUE(value.is_a<double>());
    ASSERT_FALSE(value.is_nothing());
    ASSERT_EQ(value.get<double>(), 3.14);
    ASSERT_THROW(value.get<int>(), TypeError);
    ASSERT_EQ(value.cast<int>(), 3);
    ASSERT_EQ(value.cast<bool>(), true);
    ASSERT_THROW(value.cast<char>(), TypeError);
}

TEST_F(TestNodeValue, Boolean)
{
    NodeValue true_value{true};
    ASSERT_FALSE(true_value.is_numeric());
    ASSERT_TRUE(true_value.is_a<bool>());
    ASSERT_FALSE(true_value.is_nothing());
    ASSERT_EQ(true_value.get<bool>(), true);
    ASSERT_EQ(true_value.cast<int>(), 1);
    ASSERT_EQ(true_value.cast<double>(), 1.0);
    ASSERT_EQ(true_value.cast<String>(), "true");

    NodeValue false_value{false};
    ASSERT_EQ(false_value.get<bool>(), false);
    ASSERT_EQ(false_value.cast<int>(), 0);
    ASSERT_EQ(false_value.cast<double>(), 0.0);
    ASSERT_EQ(false_value.cast<String>(), "false");
}

TEST_F(TestNodeValue, String)
{
    NodeValue value{String("hello")};
    ASSERT_FALSE(value.is_numeric());
    ASSERT_TRUE(value.is_a<String>());
    ASSERT_FALSE(value.is_nothing());
    ASSERT_EQ(value.get<String>(), "hello");
    ASSERT_EQ(value.cast<bool>(), true);
    ASSERT_THROW(value.cast<int>(), TypeError);
    ASSERT_THROW(value.cast<double>(), TypeError);
    ASSERT_THROW(value.cast<char>(), TypeError);
}

TEST_F(TestNodeValue, Char)
{
    NodeValue value{'A'};
    ASSERT_FALSE(value.is_numeric());
    ASSERT_TRUE(value.is_a<char>());
    ASSERT_FALSE(value.is_nothing());
    ASSERT_EQ(value.get<char>(), 'A');
    ASSERT_EQ(value.cast<int>(), 65);
    ASSERT_EQ(value.cast<double>(), 65.0);
    ASSERT_EQ(value.cast<bool>(), true);
    ASSERT_EQ(value.cast<String>(), "A");
}

TEST_F(TestNodeValue, None)
{
    NodeValue value{None{}};
    ASSERT_FALSE(value.is_numeric());
    ASSERT_TRUE(value.is_a<None>());
    ASSERT_TRUE(value.is_nothing());
    ASSERT_NO_THROW(value.get<None>());
    ASSERT_EQ(value.cast<bool>(), false);
    ASSERT_EQ(value.cast<String>(), "none");
    ASSERT_THROW(value.cast<int>(), TypeError);
    ASSERT_THROW(value.cast<double>(), TypeError);
    ASSERT_THROW(value.cast<char>(), TypeError);
}

TEST_F(TestNodeValue, GetVariant)
{
    NodeValue int_value{42};
    auto variant = int_value.get_variant();
    ASSERT_TRUE(std::holds_alternative<int>(variant));
    ASSERT_EQ(std::get<int>(variant), 42);

    NodeValue string_value{String("test")};
    variant = string_value.get_variant();
    ASSERT_TRUE(std::holds_alternative<String>(variant));
    ASSERT_EQ(std::get<String>(variant), "test");
}

TEST_F(TestNodeValue, ArithmeticOperations)
{
    NodeValue a{5};
    NodeValue b{3};

    NodeValue sum = a + b;
    ASSERT_TRUE(sum.is_a<int>());
    ASSERT_EQ(sum.get<int>(), 8);

    NodeValue diff = a - b;
    ASSERT_TRUE(diff.is_a<int>());
    ASSERT_EQ(diff.get<int>(), 2);

    NodeValue product = a * b;
    ASSERT_TRUE(product.is_a<int>());
    ASSERT_EQ(product.get<int>(), 15);

    NodeValue quotient = a / b;
    ASSERT_TRUE(quotient.is_a<int>());
    ASSERT_EQ(quotient.get<int>(), 1);

    NodeValue modulo = a % b;
    ASSERT_TRUE(modulo.is_a<int>());
    ASSERT_EQ(modulo.get<int>(), 2);

    NodeValue power = pow(a, b);
    ASSERT_TRUE(power.is_a<int>());
    ASSERT_EQ(power.get<int>(), 125);
}

TEST_F(TestNodeValue, ComparisonOperations)
{
    NodeValue a{5};
    NodeValue b{3};
    NodeValue c{5};

    NodeValue eq1 = (a == b);
    ASSERT_TRUE(eq1.is_a<bool>());
    ASSERT_EQ(eq1.get<bool>(), false);

    NodeValue eq2 = (a == c);
    ASSERT_TRUE(eq2.is_a<bool>());
    ASSERT_EQ(eq2.get<bool>(), true);

    NodeValue neq = (a != b);
    ASSERT_TRUE(neq.is_a<bool>());
    ASSERT_EQ(neq.get<bool>(), true);

    NodeValue gt = (a > b);
    ASSERT_TRUE(gt.is_a<bool>());
    ASSERT_EQ(gt.get<bool>(), true);

    NodeValue lt = (a < b);
    ASSERT_TRUE(lt.is_a<bool>());
    ASSERT_EQ(lt.get<bool>(), false);

    NodeValue ge = (a >= c);
    ASSERT_TRUE(ge.is_a<bool>());
    ASSERT_EQ(ge.get<bool>(), true);

    NodeValue le = (a <= c);
    ASSERT_TRUE(le.is_a<bool>());
    ASSERT_EQ(le.get<bool>(), true);
}

TEST_F(TestNodeValue, LogicalOperations)
{
    NodeValue t{true};
    NodeValue f{false};

    NodeValue and_result = (t && t);
    ASSERT_TRUE(and_result.is_a<bool>());
    ASSERT_EQ(and_result.get<bool>(), true);

    NodeValue and_result2 = (t && f);
    ASSERT_TRUE(and_result2.is_a<bool>());
    ASSERT_EQ(and_result2.get<bool>(), false);

    NodeValue or_result = (t || f);
    ASSERT_TRUE(or_result.is_a<bool>());
    ASSERT_EQ(or_result.get<bool>(), true);

    NodeValue or_result2 = (f || f);
    ASSERT_TRUE(or_result2.is_a<bool>());
    ASSERT_EQ(or_result2.get<bool>(), false);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
