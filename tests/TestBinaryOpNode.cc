#include "ast/expression/BinaryOpNode.h"
#include "ast/expression/LiteralNode.h"
#include "utils/Common.h"
#include <gtest/gtest.h>

using namespace funk;

class TestBinaryOpNode : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Setup common test objects
        loc = SourceLocation{"test.funk", 0, 0};
    }

    void TearDown() override
    {
        // Cleanup code if needed
    }

    SourceLocation loc{"test.funk", 0, 0};
};

TEST_F(TestBinaryOpNode, Construction)
{
    LiteralNode* left = new LiteralNode(loc, 5);
    LiteralNode* right = new LiteralNode(loc, 3);

    Token op(loc, "+", TokenType::PLUS);
    BinaryOpNode node(left, op, right);

    ASSERT_EQ(node.get_op().get_type(), TokenType::PLUS);
    ASSERT_EQ(node.get_left(), left);
    ASSERT_EQ(node.get_right(), right);
}

TEST_F(TestBinaryOpNode, ArithmeticOperations)
{
    // Addition
    {
        LiteralNode* left = new LiteralNode(loc, 5);
        LiteralNode* right = new LiteralNode(loc, 3);
        Token op(loc, "+", TokenType::PLUS);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<int>());
        ASSERT_EQ(result.get<int>(), 8);
    }

    // Subtraction
    {
        LiteralNode* left = new LiteralNode(loc, 10);
        LiteralNode* right = new LiteralNode(loc, 4);
        Token op(loc, "-", TokenType::MINUS);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<int>());
        ASSERT_EQ(result.get<int>(), 6);
    }

    // Multiplication
    {
        LiteralNode* left = new LiteralNode(loc, 5);
        LiteralNode* right = new LiteralNode(loc, 6);
        Token op(loc, "*", TokenType::MULTIPLY);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<int>());
        ASSERT_EQ(result.get<int>(), 30);
    }

    // Division
    {
        LiteralNode* left = new LiteralNode(loc, 20);
        LiteralNode* right = new LiteralNode(loc, 4);
        Token op(loc, "/", TokenType::DIVIDE);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<int>());
        ASSERT_EQ(result.get<int>(), 5);
    }

    // Modulo
    {
        LiteralNode* left = new LiteralNode(loc, 17);
        LiteralNode* right = new LiteralNode(loc, 5);
        Token op(loc, "%", TokenType::MODULO);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<int>());
        ASSERT_EQ(result.get<int>(), 2);
    }

    // Power
    {
        LiteralNode* left = new LiteralNode(loc, 2);
        LiteralNode* right = new LiteralNode(loc, 3);
        Token op(loc, "^", TokenType::POWER);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<int>());
        ASSERT_EQ(result.get<int>(), 8);
    }
}

TEST_F(TestBinaryOpNode, ComparisonOperations)
{
    // Equal
    {
        LiteralNode* left = new LiteralNode(loc, 5);
        LiteralNode* right = new LiteralNode(loc, 5);
        Token op(loc, "==", TokenType::EQUAL);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<bool>());
        ASSERT_EQ(result.get<bool>(), true);
    }

    // Not Equal
    {
        LiteralNode* left = new LiteralNode(loc, 5);
        LiteralNode* right = new LiteralNode(loc, 3);
        Token op(loc, "!=", TokenType::NOT_EQUAL);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<bool>());
        ASSERT_EQ(result.get<bool>(), true);
    }

    // Less Than
    {
        LiteralNode* left = new LiteralNode(loc, 3);
        LiteralNode* right = new LiteralNode(loc, 5);
        Token op(loc, "<", TokenType::LESS);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<bool>());
        ASSERT_EQ(result.get<bool>(), true);
    }

    // Less Than or Equal
    {
        LiteralNode* left = new LiteralNode(loc, 5);
        LiteralNode* right = new LiteralNode(loc, 5);
        Token op(loc, "<=", TokenType::LESS_EQUAL);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<bool>());
        ASSERT_EQ(result.get<bool>(), true);
    }

    // Greater Than
    {
        LiteralNode* left = new LiteralNode(loc, 8);
        LiteralNode* right = new LiteralNode(loc, 5);
        Token op(loc, ">", TokenType::GREATER);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<bool>());
        ASSERT_EQ(result.get<bool>(), true);
    }

    // Greater Than or Equal
    {
        LiteralNode* left = new LiteralNode(loc, 5);
        LiteralNode* right = new LiteralNode(loc, 5);
        Token op(loc, ">=", TokenType::GREATER_EQUAL);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<bool>());
        ASSERT_EQ(result.get<bool>(), true);
    }
}

TEST_F(TestBinaryOpNode, LogicalOperations)
{
    // AND
    {
        LiteralNode* left = new LiteralNode(loc, true);
        LiteralNode* right = new LiteralNode(loc, true);
        Token op(loc, "&&", TokenType::AND);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<bool>());
        ASSERT_EQ(result.get<bool>(), true);
    }

    // OR
    {
        LiteralNode* left = new LiteralNode(loc, false);
        LiteralNode* right = new LiteralNode(loc, true);
        Token op(loc, "||", TokenType::OR);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<bool>());
        ASSERT_EQ(result.get<bool>(), true);
    }
}

TEST_F(TestBinaryOpNode, MixedTypeOperations)
{
    // Integer + Double
    {
        LiteralNode* left = new LiteralNode(loc, 5);
        LiteralNode* right = new LiteralNode(loc, 3.5);
        Token op(loc, "+", TokenType::PLUS);
        BinaryOpNode node(left, op, right);

        NodeValue result = node.get_value();
        ASSERT_TRUE(result.is_a<double>());
        ASSERT_DOUBLE_EQ(result.get<double>(), 8.5);
    }
}

TEST_F(TestBinaryOpNode, ErrorCases)
{
    // Division by zero
    {
        LiteralNode* left = new LiteralNode(loc, 10);
        LiteralNode* right = new LiteralNode(loc, 0);
        Token op(loc, "/", TokenType::DIVIDE);
        BinaryOpNode node(left, op, right);

        ASSERT_THROW(node.get_value(), RuntimeError);
    }

    // Invalid operation: String % Integer
    {
        LiteralNode* left = new LiteralNode(loc, String("hello"));
        LiteralNode* right = new LiteralNode(loc, 5);
        Token op(loc, "%", TokenType::MODULO);
        BinaryOpNode node(left, op, right);

        ASSERT_THROW(node.get_value(), TypeError);
    }

    // String + Integer
    {
        LiteralNode* left = new LiteralNode(loc, String("hello"));
        LiteralNode* right = new LiteralNode(loc, 123);
        Token op(loc, "+", TokenType::PLUS);
        BinaryOpNode node(left, op, right);

        ASSERT_THROW(node.get_value(), TypeError);
    }
}

TEST_F(TestBinaryOpNode, StringRepresentation)
{
    LiteralNode* left = new LiteralNode(loc, 10);
    LiteralNode* right = new LiteralNode(loc, 5);
    Token op(loc, "+", TokenType::PLUS);
    BinaryOpNode node(left, op, right);

    ASSERT_EQ(node.to_s(), "(10 + 5)");
}

TEST_F(TestBinaryOpNode, Evaluate)
{
    LiteralNode* left = new LiteralNode(loc, 7);
    LiteralNode* right = new LiteralNode(loc, 3);
    Token op(loc, "-", TokenType::MINUS);
    BinaryOpNode node(left, op, right);

    Node* result = node.evaluate();
    ASSERT_NE(result, nullptr);

    // After evaluation, result should be a LiteralNode
    LiteralNode* literal_result = dynamic_cast<LiteralNode*>(result);
    ASSERT_NE(literal_result, nullptr);
    ASSERT_EQ(literal_result->get_value().get<int>(), 4);
}

TEST_F(TestBinaryOpNode, NestedOperations)
{
    // Create (5 + 3) * 2
    LiteralNode* five = new LiteralNode(loc, 5);
    LiteralNode* three = new LiteralNode(loc, 3);
    LiteralNode* two = new LiteralNode(loc, 2);

    Token plus_op(loc, "+", TokenType::PLUS);
    Token mult_op(loc, "*", TokenType::MULTIPLY);

    BinaryOpNode* addition = new BinaryOpNode(five, plus_op, three);
    BinaryOpNode multiplication(addition, mult_op, two);

    NodeValue result = multiplication.get_value();
    ASSERT_TRUE(result.is_a<int>());
    ASSERT_EQ(result.get<int>(), 16);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
