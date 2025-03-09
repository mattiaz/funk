#include "lexer/Lexer.h"
#include "utils/Common.h"
#include <gtest/gtest.h>

using namespace funk;

class TestLexer : public ::testing::Test
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

TEST_F(TestLexer, Token)
{
    SourceLocation loc{"test.funk", 1, 1};
    Token token{loc, "true", TokenType::BOOL, true};
    ASSERT_EQ(token.get_lexeme(), "true");
    ASSERT_EQ(token.get_type(), TokenType::BOOL);
    ASSERT_EQ(std::get<bool>(token.get_value()), true);
    ASSERT_EQ(token.get_location().line, 1);
    ASSERT_EQ(token.get_location().column, 1);
    ASSERT_EQ(token.get_location().filename, "test.funk");
}

TEST_F(TestLexer, TextToken)
{
    SourceLocation loc{"test.funk", 1, 1};
    Token token{loc, "hello", TokenType::TEXT, "hello"};
    ASSERT_EQ(token.get_lexeme(), "hello");
    ASSERT_EQ(token.get_type(), TokenType::TEXT);
    ASSERT_EQ(std::get<std::string>(token.get_value()), "hello");
    ASSERT_EQ(token.get_location().line, 1);
    ASSERT_EQ(token.get_location().column, 1);
    ASSERT_EQ(token.get_location().filename, "test.funk");
}

TEST_F(TestLexer, Lexer)
{
    Lexer lexer{"bool test = false;", "test"};
    auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[0].get_lexeme(), "bool");
    ASSERT_EQ(tokens[0].get_type(), TokenType::BOOL_TYPE);
    ASSERT_EQ(tokens[1].get_lexeme(), "test");
    ASSERT_EQ(tokens[1].get_type(), TokenType::IDENTIFIER);
    ASSERT_EQ(tokens[2].get_lexeme(), "=");
    ASSERT_EQ(tokens[2].get_type(), TokenType::ASSIGN);
    ASSERT_EQ(tokens[3].get_lexeme(), "false");
    ASSERT_EQ(tokens[3].get_type(), TokenType::BOOL);
    ASSERT_EQ(std::get<bool>(tokens[3].get_value()), false);
    ASSERT_EQ(tokens[4].get_lexeme(), ";");
    ASSERT_EQ(tokens[4].get_type(), TokenType::SEMICOLON);
}

TEST_F(TestLexer, LexerFromFile)
{
    Lexer lexer{read_file("examples/math.funk"), "examples/math.funk"};
    auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 10);
    ASSERT_EQ(tokens[0].get_type(), TokenType::L_PAR);
    ASSERT_EQ(tokens[1].get_type(), TokenType::NUMB);
    ASSERT_EQ(tokens[2].get_type(), TokenType::PLUS);
    ASSERT_EQ(tokens[3].get_type(), TokenType::NUMB);
    ASSERT_EQ(tokens[4].get_type(), TokenType::R_PAR);
    ASSERT_EQ(tokens[5].get_type(), TokenType::DIVIDE);
    ASSERT_EQ(tokens[6].get_type(), TokenType::NUMB);
    ASSERT_EQ(tokens[7].get_type(), TokenType::MULTIPLY);
    ASSERT_EQ(tokens[8].get_type(), TokenType::NUMB);
    ASSERT_EQ(tokens[9].get_type(), TokenType::EOF_TOKEN);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
