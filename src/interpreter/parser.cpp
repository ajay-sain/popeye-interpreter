//
// Created by Ajay Sain on 09/09/25
//

#include "spdlog/spdlog.h"
#include "magic_enum.hpp"

#include "interpreter/parser.h"

namespace interpreter {
    void Parser::parse() {
        Token token = lexer.next();
        while (token.type != TokenType::EOF_) {
            spdlog::info("Token: {}, {}", token.lexeme, magic_enum::enum_name(token.type));
            token = lexer.next();
        }
    }
} // namespace interpreter
