//
// Created by Ajay Sain on 25/09/25.
//

#ifndef INTERPRETER_TOKEN_H
#define INTERPRETER_TOKEN_H

#include <string>

#include "interpreter/lexer/TokenType.h"

// Represents a token with type and lexeme
struct Token {
    TokenType type;
    std::string lexeme;
    size_t line;

    Token(TokenType type, std::string lexeme, size_t line = 1)
            : type(type), lexeme(std::move(lexeme)), line(line) {}
};

#endif //INTERPRETER_TOKEN_H
