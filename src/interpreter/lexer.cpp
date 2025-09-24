//
// Lexer implementation for the Popeye programming language
//

#include "interpreter/lexer.h"
#include <cctype>
#include <sstream>
#include <utility>

Lexer::Lexer(std::string source)
    : source(std::move(source)), current(0), start(0), line(1) {}

char Lexer::advance() {
    if (isAtEnd()) return '\0';
    char c = source[current++];
    if (c == '\n') line++;
    return c;
}

bool Lexer::isAtEnd() const {
    return current >= source.length();
}

char Lexer::peekChar() const {
    return isAtEnd() ? '\0' : source[current];
}

bool Lexer::match(char expected) {
    if (isAtEnd() || source[current] != expected) {
        return false;
    }
    advance();
    return true;
}

[[noreturn]] void Lexer::error(const std::string& message) const {
    std::ostringstream ss;
    ss << "[line " << line << "] Error: " << message;
    throw std::runtime_error(ss.str());
}

Token Lexer::makeToken(TokenType type) {
    std::string lexeme = source.substr(start, current - start);
    return Token{type, lexeme, line};
}

Token Lexer::next() {
    skipWhitespace();
    start = current;

    if (isAtEnd()) {
        return makeToken(TokenType::END_OF_FILE);
    }

    char c = advance();

    // Handle identifiers and keywords
    if (isalpha(c) || c == '_') {
        while (isalnum(peekChar()) || peekChar() == '_') {
            c = advance(); // Update the advance() call to handle the return value
        }

        std::string text = source.substr(start, current - start);
        if (text == "let") {
            return makeToken(TokenType::LET);
        }
        return makeToken(TokenType::IDENTIFIER);
    }

    // Handle numbers
    if (isdigit(c)) {
        while (isdigit(peekChar())) {
            advance();
        }

        // Handle decimal point
        if (peekChar() == '.' && isdigit(source[current + 1])) {
            advance(); // Consume the decimal point
            while (isdigit(peekChar())) {
                advance();
            }
        }

        return makeToken(TokenType::NUMBER);
    }

    // Handle operators and other tokens
    switch (c) {
        case '=':
            return makeToken(TokenType::ASSIGN);
        case '+':
            return makeToken(TokenType::PLUS);
        case '-':
            return makeToken(TokenType::MINUS);
        case '*':
            return makeToken(TokenType::ASTERISK);
        case '/':
            return makeToken(TokenType::SLASH);
        case '%':
            return makeToken(TokenType::MODULO);
        case '^':
            return makeToken(TokenType::CARET);
        case '(':
            return makeToken(TokenType::LEFT_PAREN);
        case ')':
            return makeToken(TokenType::RIGHT_PAREN);
        default:
            return makeToken(TokenType::UNKNOWN);
    }
}

void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peekChar();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                line++;
                advance();
                break;
            default:
                return;
        }
    }
}

Token Lexer::peek() {
    size_t savedCurrent = current;
    size_t savedStart = start;
    size_t savedLine = line;

    Token nextToken = next();

    // Restore state
    current = savedCurrent;
    start = savedStart;
    line = savedLine;

    return nextToken;
}

Token Lexer::number() {
    while (isdigit(peekChar())) {
        advance();
    }

    // Look for decimal point
    if (peekChar() == '.' && isdigit(source[current + 1])) {
        advance(); // Consume the decimal point

        while (isdigit(peekChar())) {
            advance();
        }
    }

    return makeToken(TokenType::NUMBER);
}

Token Lexer::identifier() {

    while (isalnum(peekChar()) || peekChar() == '_') {
        advance();
    }

    return makeToken(TokenType::IDENTIFIER);
}
