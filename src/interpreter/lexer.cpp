//
// Lexer implementation for the Popeye programming language
//

#include "interpreter/lexer.h"
#include <cctype>
#include <sstream>
#include <utility>

Lexer::Lexer(std::string source)
    : source(std::move(source)), current(0), start(0), line(1) {}

void Lexer::advance() {
    if (!isAtEnd()) {
        if (peekChar() == '\n') {
            line++;
        }
        current++;
    }
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
    return Token{type, source.substr(start, current - start), line};
}

Token Lexer::next() {
    // Skip whitespace
    while (!isAtEnd()) {
        start = current;
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
                goto lex_token; // Exit the loop when non-whitespace is found
        }
    }

    if (isAtEnd()) {
        return makeToken(TokenType::END_OF_FILE);
    }

lex_token:
    start = current;
    char c = peekChar();

    // Handle literals
    if (isdigit(c)) {
        return number();
    }

    if (isalpha(c) || c == '_') {
        return identifier();
    }

    // Handle operators and punctuation
    switch (c) {
        case '+': advance(); return makeToken(TokenType::PLUS);
        case '-': advance(); return makeToken(TokenType::MINUS);
        case '*': advance(); return makeToken(TokenType::ASTERISK);
        case '/': advance(); return makeToken(TokenType::SLASH);
        case '%': advance(); return makeToken(TokenType::MODULO);
        case '^': advance(); return makeToken(TokenType::CARET);
        case '=': advance(); return makeToken(TokenType::EQUAL);
        case '(': advance(); return makeToken(TokenType::LEFT_PAREN);
        case ')': advance(); return makeToken(TokenType::RIGHT_PAREN);
    }

    // Handle unknown characters
    advance();
    error("Unexpected character: " + std::string(1, c));
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
