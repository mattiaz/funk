#include "lexer/Lexer.h"
#include "logging/LogMacros.h"

int main(int argc, char* argv[])
{
    LOG_INFO("Starting main function");

    funk::Lexer lexer{"bool test = true; print(false || test);", "test"};
    auto tokens = lexer.tokenize();
    for (auto& token : tokens) { LOG_DEBUG(token); }

    LOG_INFO("Finished main function");
    return 0;
}
