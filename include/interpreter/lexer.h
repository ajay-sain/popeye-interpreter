//
// Created by Ajay Sain on 09/09/25.
//

#pragma once

#include "interpreter/Token.h"

namespace interpreter {
    class Lexer {
    private :
        std::string expression;
        int start = 0;
        int current = 0;
        int line = 1;

        void advance();
        char peekNextChar();
        interpreter::Token _number();
        interpreter::Token _identifier();
        interpreter::Token _string(TokenType type);
        bool isAtEnd();
        bool match(char i);

    public :
        Token currentToken;
        Token previousToken;

        explicit Lexer(std::string input) : expression(std::move(input)) {}
        Token next();
        Token peek();
    };
}
