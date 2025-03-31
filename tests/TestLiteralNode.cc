#include "ast/expression/LiteralNode.h"
#include "utils/Common.h"
#include <gtest/gtest.h>

using namespace funk;

class TestLiteralNode : public ::testing::Test
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

TEST_F(TestLiteralNode, Integer)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode node{loc, 5};
    ASSERT_TRUE(node.get_value().is_numeric());
    ASSERT_TRUE(node.get_value().is_a<int>());
    ASSERT_FALSE(node.get_value().is_a<double>());
    ASSERT_FALSE(node.get_value().is_nothing());
    ASSERT_EQ(node.get_value().get<int>(), 5);
    ASSERT_THROW(node.get_value().get<double>(), TypeError);
    ASSERT_THROW(node.get_value().cast<None>(), TypeError);
    ASSERT_EQ(node.get_value().cast<double>(), 5.0);
    ASSERT_EQ(node.get_value().cast<bool>(), true);
    ASSERT_EQ(node.get_value().cast<char>(), static_cast<char>(5));
    ASSERT_EQ(node.get_value().cast<String>(), "5");
}

TEST_F(TestLiteralNode, Double)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode node{loc, 3.14};
    ASSERT_TRUE(node.get_value().is_numeric());
    ASSERT_FALSE(node.get_value().is_a<int>());
    ASSERT_TRUE(node.get_value().is_a<double>());
    ASSERT_FALSE(node.get_value().is_nothing());
    ASSERT_EQ(node.get_value().get<double>(), 3.14);
    ASSERT_THROW(node.get_value().get<int>(), TypeError);
    ASSERT_EQ(node.get_value().cast<int>(), 3);
    ASSERT_EQ(node.get_value().cast<bool>(), true);
    ASSERT_THROW(node.get_value().cast<char>(), TypeError);
}

TEST_F(TestLiteralNode, Boolean)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode true_node{loc, true};
    ASSERT_FALSE(true_node.get_value().is_numeric());
    ASSERT_TRUE(true_node.get_value().is_a<bool>());
    ASSERT_FALSE(true_node.get_value().is_nothing());
    ASSERT_EQ(true_node.get_value().get<bool>(), true);
    ASSERT_EQ(true_node.get_value().cast<int>(), 1);
    ASSERT_EQ(true_node.get_value().cast<double>(), 1.0);
    ASSERT_EQ(true_node.get_value().cast<String>(), "true");

    LiteralNode false_node{loc, false};
    ASSERT_EQ(false_node.get_value().get<bool>(), false);
    ASSERT_EQ(false_node.get_value().cast<int>(), 0);
    ASSERT_EQ(false_node.get_value().cast<double>(), 0.0);
    ASSERT_EQ(false_node.get_value().cast<String>(), "false");
}

TEST_F(TestLiteralNode, String)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode node{loc, String("hello")};
    ASSERT_FALSE(node.get_value().is_numeric());
    ASSERT_TRUE(node.get_value().is_a<String>());
    ASSERT_FALSE(node.get_value().is_nothing());
    ASSERT_EQ(node.get_value().get<String>(), "hello");
    ASSERT_EQ(node.to_s(), "\"hello\"");
    ASSERT_EQ(node.get_value().cast<bool>(), true);
    ASSERT_THROW(node.get_value().cast<int>(), TypeError);
    ASSERT_THROW(node.get_value().cast<double>(), TypeError);
    ASSERT_THROW(node.get_value().cast<char>(), TypeError);
}

TEST_F(TestLiteralNode, Char)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode node{loc, 'A'};
    ASSERT_FALSE(node.get_value().is_numeric());
    ASSERT_TRUE(node.get_value().is_a<char>());
    ASSERT_FALSE(node.get_value().is_nothing());
    ASSERT_EQ(node.get_value().get<char>(), 'A');
    ASSERT_EQ(node.get_value().cast<int>(), 65);
    ASSERT_EQ(node.get_value().cast<double>(), 65.0);
    ASSERT_EQ(node.get_value().cast<bool>(), true);
    ASSERT_EQ(node.get_value().cast<String>(), "A");
}

TEST_F(TestLiteralNode, None)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode node{loc, None{}};
    ASSERT_FALSE(node.get_value().is_numeric());
    ASSERT_TRUE(node.get_value().is_a<None>());
    ASSERT_TRUE(node.get_value().is_nothing());
    ASSERT_NO_THROW(node.get_value().get<None>());
    ASSERT_EQ(node.get_value().cast<bool>(), false);
    ASSERT_EQ(node.get_value().cast<String>(), "none");
    ASSERT_THROW(node.get_value().cast<int>(), TypeError);
    ASSERT_THROW(node.get_value().cast<double>(), TypeError);
    ASSERT_THROW(node.get_value().cast<char>(), TypeError);
}

TEST_F(TestLiteralNode, GetValue)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode int_node{loc, 42};
    NodeValue value = int_node.get_value();
    ASSERT_TRUE(std::holds_alternative<int>(value.get_variant()));
    ASSERT_EQ(std::get<int>(value.get_variant()), 42);

    LiteralNode stringNode{loc, String("test")};
    value = stringNode.get_value();
    ASSERT_TRUE(std::holds_alternative<String>(value.get_variant()));
    ASSERT_EQ(std::get<String>(value.get_variant()), "test");
}

TEST_F(TestLiteralNode, Evaluate)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode node{loc, 100};
    Node* result = node.evaluate();
    ASSERT_EQ(result, &node);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
