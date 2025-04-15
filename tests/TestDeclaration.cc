#include <gtest/gtest.h>
#include "utils/Common.h"
#include "ast/declaration/DeclarationNode.h"
#include "parser/Scope.h"


using namespace funk;


class TestDeclaration : public ::testing::Test{
protected:
    void SetUp() override
    {
        // Setup common test objects
        loc = SourceLocation{"test.funk", 0, 0};
        // Clean up all scopes before each test
        Scope::instance().push();
    }

    void TearDown() override
    {
        // Cleanup code if needed
    }

    SourceLocation loc{"test.funk", 0, 0};

};

TEST_F(TestDeclaration, DeclareAndRetrieveVariable) {
    auto* decl = new DeclarationNode(loc, false, TokenType::NUMB_TYPE, "x", new LiteralNode(loc, NodeValue{42}));
    decl->evaluate();
    auto* var = dynamic_cast<VariableNode*>(Scope::instance().get("x"));
    ASSERT_NE(var, nullptr);
    ASSERT_EQ(var->get_identifier(), "x");
    ASSERT_EQ(var->get_value().get<int>(), 42);
    ASSERT_EQ(var->get_type(), TokenType::NUMB_TYPE);
}

TEST_F(TestDeclaration, RedeclarationInSameScopeThrows) {
    auto* decl1 = new DeclarationNode(loc, false, TokenType::NUMB_TYPE, "y", new LiteralNode(loc, NodeValue{1}));
    decl1->evaluate();
    auto* decl2 = new DeclarationNode(loc, false, TokenType::NUMB_TYPE, "y", new LiteralNode(loc, NodeValue{2}));
    EXPECT_THROW(decl2->evaluate(), RuntimeError);
}

TEST_F(TestDeclaration, DeclareWithSameNameAsBuiltInFunction) {
    auto* decl = new DeclarationNode(loc, false, TokenType::NUMB_TYPE, "print", new LiteralNode(loc, NodeValue{42}));
    EXPECT_THROW(decl->evaluate(), RuntimeError);
}

//Mut tests later when implemented