#include "ast/expression/LiteralNode.h"
#include "ast/expression/UnaryOpNode.h"
#include "utils/Common.h"
#include <gtest/gtest.h>

using namespace funk;

class TestUnaryOpNode : public ::testing::Test
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

TEST_F(TestUnaryOpNode, Construction)
{
    LiteralNode* intVal = new LiteralNode(loc, 5);
    LiteralNode* boolVal = new LiteralNode(loc, false);

    Token minus_token(loc, "-", TokenType::MINUS);
    Token not_token(loc, "not", TokenType::NOT);

    UnaryOpNode negateNode(minus_token, intVal);
    UnaryOpNode notNode(not_token, boolVal);

    ASSERT_EQ(negateNode.get_op().get_type(), TokenType::MINUS);
    ASSERT_EQ(negateNode.get_expr(), intVal);

    ASSERT_EQ(notNode.get_op().get_type(), TokenType::NOT);
    ASSERT_EQ(notNode.get_expr(), boolVal);
}

TEST_F(TestUnaryOpNode, NegateEvaluation)
{
    LiteralNode* val1 = new LiteralNode(loc, 5);
    LiteralNode* val2 = new LiteralNode(loc, 3.14);

    Token minus_token(loc, "-", TokenType::MINUS);
    Token not_token(loc, "not", TokenType::NOT);

    UnaryOpNode negateInt(minus_token, val1);
    UnaryOpNode negateDouble(minus_token, val2);

    ASSERT_EQ(negateInt.get_value().get<int>(), -5);
    ASSERT_DOUBLE_EQ(negateDouble.get_value().get<double>(), -3.14);
}

TEST_F(TestUnaryOpNode, NotEvaluation)
{
    LiteralNode* val1 = new LiteralNode(loc, true);
    LiteralNode* val2 = new LiteralNode(loc, false);

    Token not_token(loc, "not", TokenType::NOT);

    UnaryOpNode notTrue(not_token, val1);
    UnaryOpNode notFalse(not_token, val2);

    ASSERT_FALSE(notTrue.get_value().get<bool>());
    ASSERT_TRUE(notFalse.get_value().get<bool>());
}

TEST_F(TestUnaryOpNode, ErrorCases)
{
    // Negate string value
    {
        LiteralNode* val = new LiteralNode(loc, String("test"));
        Token minus_token(loc, "-", TokenType::MINUS);
        UnaryOpNode node(minus_token, val);

        ASSERT_THROW(node.get_value(), TypeError);
    }

    // Negate boolean value, apparently this works in c++ but it's ugly
    {
        LiteralNode* val = new LiteralNode(loc, true);
        Token minus_token(loc, "-", TokenType::MINUS);
        UnaryOpNode node(minus_token, val);

        ASSERT_THROW(node.get_value(), TypeError);
    }

    // Logical NOT on non-boolean value
    {
        LiteralNode* val = new LiteralNode(loc, 5);
        Token op(loc, "not", TokenType::NOT);
        UnaryOpNode node(op, val);

        ASSERT_THROW(node.get_value(), TypeError);
    }
}

TEST_F(TestUnaryOpNode, StringRepresentation)
{
    LiteralNode* val = new LiteralNode(loc, 5);
    Token minus_token(loc, "-", TokenType::MINUS);
    UnaryOpNode node(minus_token, val);

    ASSERT_EQ(node.to_s(), "(-5)");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
