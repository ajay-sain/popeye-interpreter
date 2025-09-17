//
// Created by Ajay Sain on 17/09/25.
//

#ifndef INTERPRETER_LEXER_H
#define INTERPRETER_LEXER_H

#include <string>

enum TokenType {

    NUMBER,
    // all operators
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    AMPERSAND,
    CARET,
    EQUAL,

    LEFT_PAREN,
    RIGHT_PAREN,

    EOF_
};

class Token{
public:
    std::string lexeme;
    TokenType type;
    Token(TokenType type, std::string lexeme) : type(type), lexeme(lexeme) {}
};

class Lexer {
public:
    std::string expression;
    Lexer(const std::string& expression) : expression(expression) {}
    Token next();
    Token peek();
};

#endif //INTERPRETER_LEXER_H
