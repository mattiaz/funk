#include "ast/literals/NumbNode.h"
#include "ast/operators/BinaryOpNode.h"
#include <gtest/gtest.h>

using namespace funk;

class TestBinaryOp : public ::testing::Test
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

TEST_F(TestBinaryOp, NumbNode)
{
    NumbNode node(SourceLocation("test.funk", 1, 1), 5);
    ASSERT_EQ(node.get_value(), 5);
}

TEST_F(TestBinaryOp, BinaryOpNode)
{
    NumbNode left(SourceLocation("test.funk", 1, 1), 5);
    NumbNode right(SourceLocation("test.funk", 1, 1), 10);
    BinaryOpNode node(SourceLocation("test.funk", 1, 1), TokenType::PLUS, &left, &right);

    ASSERT_EQ(static_cast<NumbNode*>(node.get_left())->get_value(), 5);
    ASSERT_EQ(static_cast<NumbNode*>(node.get_right())->get_value(), 10);

    ASSERT_EQ(static_cast<NumbNode*>(node.evaluate())->get_value(), 15);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
