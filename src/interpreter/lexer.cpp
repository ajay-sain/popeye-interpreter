//
// Created by Ajay Sain on 17/09/25.
//
#include "interpreter/lexer.h"

class Tokenizer: public Lexer {
private:
    size_t current = 0;
    size_t start = 0;
    size_t line = 1;
    Token previousToken;
    Token currentToken;
public:

    void advance() {
        if (current < expression.length()) {
            current++;
        }
    }

    Token next(){
        previousToken = currentToken;
        // Skip whitespace
        while (current < expression.length() && isspace(expression[current])) {
            if (expression[current] == '\n') line++;
            current++;
        }
        if (current >= expression.length()) {
            return Token{TokenType::EOF_, ""};
        }
        char c = expression[current];
        start = current;

        // Handle single character tokens
        switch (c) {
            case '-': advance(); return Token{TokenType::MINUS, "-"};
            case '+': advance(); return Token{TokenType::PLUS, "+"};
            case '*': advance(); return Token{TokenType::ASTERISK, "*"};
            case '/': advance(); return Token{TokenType::SLASH, "/"};
            case '%': advance(); return Token{TokenType::AMPERSAND, "%"};
            case '^': advance(); return Token{TokenType::CARET, "^"};
            case '(': advance(); return Token{TokenType::LEFT_PAREN, "("};
            case ')': advance(); return Token{TokenType::RIGHT_PAREN, ")"};
            case '=': advance(); return Token{TokenType::EQUAL, "="};
            default: break;
        }
        return Token{TokenType::EOF_, ""};
    }

    Token peek(){
        if (current < expression.length()) {
            char c = expression[current];
            return Token{static_cast<TokenType>(c), std::string(1, c)};
        }
        return Token{TokenType::EOF_, ""};
    }

    bool match(char expected) {
        if (isAtEnd()) return false;
        if (expression[current] != expected) return false;

        current++;
        return true;
    }

    char peekNextChar() {
        if (current + 1 >= expression.length()) return '\0';
        return expression[current + 1];
    }
    Token _number() {
        while (current < expression.length() && isdigit(expression[current])) {
            advance();
        }
        // Look for a fractional part.
        if (current < expression.length() - 1 &&
            expression[current] == '.' &&
            isdigit(expression[current + 1])) {
            // Consume the "."
            advance();

            while (current < expression.length() && isdigit(expression[current])) {
                advance();
            }
        }

        std::string numStr = expression.substr(start, current - start);
        return Token{TokenType::NUMBER, numStr};
    }
};