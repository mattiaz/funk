#include "ast/LiteralNode.h"
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
    ASSERT_TRUE(node.is_numeric());
    ASSERT_TRUE(node.is_a<int>());
    ASSERT_FALSE(node.is_a<double>());
    ASSERT_FALSE(node.is_nothing());
    ASSERT_EQ(node.get<int>(), 5);
    ASSERT_THROW(node.get<double>(), TypeError);
    ASSERT_THROW(node.cast<None>(), TypeError);
    ASSERT_EQ(node.cast<double>(), 5.0);
    ASSERT_EQ(node.cast<bool>(), true);
    ASSERT_EQ(node.cast<char>(), static_cast<char>(5));
    ASSERT_EQ(node.cast<String>(), "5");
}

TEST_F(TestLiteralNode, Double)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode node{loc, 3.14};
    ASSERT_TRUE(node.is_numeric());
    ASSERT_FALSE(node.is_a<int>());
    ASSERT_TRUE(node.is_a<double>());
    ASSERT_FALSE(node.is_nothing());
    ASSERT_EQ(node.get<double>(), 3.14);
    ASSERT_THROW(node.get<int>(), TypeError);
    ASSERT_EQ(node.cast<int>(), 3);
    ASSERT_EQ(node.cast<bool>(), true);
    ASSERT_THROW(node.cast<char>(), TypeError);
}

TEST_F(TestLiteralNode, Boolean)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode trueNode{loc, true};
    ASSERT_FALSE(trueNode.is_numeric());
    ASSERT_TRUE(trueNode.is_a<bool>());
    ASSERT_FALSE(trueNode.is_nothing());
    ASSERT_EQ(trueNode.get<bool>(), true);
    ASSERT_EQ(trueNode.cast<int>(), 1);
    ASSERT_EQ(trueNode.cast<double>(), 1.0);
    ASSERT_EQ(trueNode.cast<String>(), "true");

    LiteralNode falseNode{loc, false};
    ASSERT_EQ(falseNode.get<bool>(), false);
    ASSERT_EQ(falseNode.cast<int>(), 0);
    ASSERT_EQ(falseNode.cast<double>(), 0.0);
    ASSERT_EQ(falseNode.cast<String>(), "false");
}

TEST_F(TestLiteralNode, String)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode node{loc, String("hello")};
    ASSERT_FALSE(node.is_numeric());
    ASSERT_TRUE(node.is_a<String>());
    ASSERT_FALSE(node.is_nothing());
    ASSERT_EQ(node.get<String>(), "hello");
    ASSERT_EQ(node.to_s(), "hello");
    ASSERT_EQ(node.cast<bool>(), true);
    ASSERT_THROW(node.cast<int>(), TypeError);
    ASSERT_THROW(node.cast<double>(), TypeError);
    ASSERT_THROW(node.cast<char>(), TypeError);
}

TEST_F(TestLiteralNode, Char)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode node{loc, 'A'};
    ASSERT_FALSE(node.is_numeric());
    ASSERT_TRUE(node.is_a<char>());
    ASSERT_FALSE(node.is_nothing());
    ASSERT_EQ(node.get<char>(), 'A');
    ASSERT_EQ(node.cast<int>(), 65);
    ASSERT_EQ(node.cast<double>(), 65.0);
    ASSERT_EQ(node.cast<bool>(), true);
    ASSERT_EQ(node.cast<String>(), "A");
}

TEST_F(TestLiteralNode, None)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode node{loc, None{}};
    ASSERT_FALSE(node.is_numeric());
    ASSERT_TRUE(node.is_a<None>());
    ASSERT_TRUE(node.is_nothing());
    ASSERT_NO_THROW(node.get<None>());
    ASSERT_EQ(node.cast<bool>(), false);
    ASSERT_EQ(node.cast<String>(), "none");
    ASSERT_THROW(node.cast<int>(), TypeError);
    ASSERT_THROW(node.cast<double>(), TypeError);
    ASSERT_THROW(node.cast<char>(), TypeError);
}

TEST_F(TestLiteralNode, GetValue)
{
    SourceLocation loc{"test.funk", 0, 0};

    LiteralNode intNode{loc, 42};
    NodeValue value = intNode.get_value();
    ASSERT_TRUE(std::holds_alternative<int>(value));
    ASSERT_EQ(std::get<int>(value), 42);

    LiteralNode stringNode{loc, String("test")};
    value = stringNode.get_value();
    ASSERT_TRUE(std::holds_alternative<String>(value));
    ASSERT_EQ(std::get<String>(value), "test");
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
