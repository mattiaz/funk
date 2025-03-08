#include "token/TokenType.h"

namespace funk
{

String token_type_to_string(TokenType token)
{
    switch (token)
    {
    case TokenType::FUNK: return "FUNK";
    case TokenType::DATA: return "DATA";
    case TokenType::MUT: return "MUT";
    case TokenType::IF: return "IF";
    case TokenType::ELSE: return "ELSE";
    case TokenType::WHILE: return "WHILE";
    case TokenType::MATCH: return "MATCH";
    case TokenType::CASE: return "CASE";
    case TokenType::NONE: return "NONE";
    case TokenType::RETURN: return "RETURN";

    case TokenType::NUMB: return "NUMB";
    case TokenType::REAL: return "REAL";
    case TokenType::BOOL: return "BOOL";
    case TokenType::CHAR: return "CHAR";
    case TokenType::TEXT: return "TEXT";

    case TokenType::NUMB_TYPE: return "NUMB_TYPE";
    case TokenType::REAL_TYPE: return "REAL_TYPE";
    case TokenType::BOOL_TYPE: return "BOOL_TYPE";
    case TokenType::CHAR_TYPE: return "CHAR_TYPE";
    case TokenType::TEXT_TYPE: return "TEXT_TYPE";

    case TokenType::IDENTIFIER: return "IDENTIFIER";

    case TokenType::PLUS: return "PLUS";
    case TokenType::MINUS: return "MINUS";
    case TokenType::MULTIPLY: return "MULTIPLY";
    case TokenType::DIVIDE: return "DIVIDE";
    case TokenType::PERCENT: return "PERCENT";

    case TokenType::ASSIGN: return "ASSIGN";
    case TokenType::PLUS_ASSIGN: return "PLUS_ASSIGN";
    case TokenType::MINUS_ASSIGN: return "MINUS_ASSIGN";
    case TokenType::MULTIPLY_ASSIGN: return "MULTIPLY_ASSIGN";
    case TokenType::DIVIDE_ASSIGN: return "DIVIDE_ASSIGN";

    case TokenType::EQUAL: return "EQUAL";
    case TokenType::NOT_EQUAL: return "NOT_EQUAL";
    case TokenType::LESS: return "LESS";
    case TokenType::GREATER: return "GREATER";
    case TokenType::LESS_EQUAL: return "LESS_EQUAL";
    case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";

    case TokenType::OR: return "OR";
    case TokenType::AND: return "AND";
    case TokenType::NOT: return "NOT";

    case TokenType::PIPE: return "PIPE";

    case TokenType::L_PAR: return "L_PAR";
    case TokenType::R_PAR: return "R_PAR";
    case TokenType::L_BRACE: return "L_BRACE";
    case TokenType::R_BRACE: return "R_BRACE";
    case TokenType::L_BRACKET: return "L_BRACKET";
    case TokenType::R_BRACKET: return "R_BRACKET";
    case TokenType::COMMA: return "COMMA";
    case TokenType::DOT: return "DOT";
    case TokenType::COLON: return "COLON";
    case TokenType::SEMICOLON: return "SEMICOLON";
    case TokenType::QUESTION: return "QUESTION";

    case TokenType::COMMENT: return "COMMENT";
    case TokenType::BLOCK_COMMENT: return "BLOCK_COMMENT";

    case TokenType::EOF_TOKEN: return "EOF_TOKEN";
    case TokenType::ERROR: return "ERROR";
    }

    return "UNKNOWN";
}
} // namespace funk
