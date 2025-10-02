//
// Lexer implementation for the Popeye programming language
//

#include <stdexcept>
#include <cctype>

#include "interpreter/lexer/Lexer.h"

Lexer::Lexer(std::string source)
    : source(std::move(source)), current(0), start(0), line(1) {}

Token Lexer::next() {
    skipWhitespace();

    if (isAtEnd()) {
        return makeToken(TokenType::END_OF_FILE);
    }

    start = current;
    char c = advance();

    // Handle string literals
    if (c == '"') {
        return string();
    }

    // Handle identifiers and keywords
    if (isalpha(c) || c == '_') {
        while (isalnum(peekChar()) || peekChar() == '_') {
            advance();
        }

        std::string text = source.substr(start, current - start);

        // Check for keywords
        if (text == "let") return makeToken(TokenType::LET);
        if (text == "true" || text == "false") return makeToken(TokenType::BOOLEAN);
        if (text == "nil") return makeToken(TokenType::NIL);

        return makeToken(TokenType::IDENTIFIER);
    }

    // Handle numbers (integers and floats)
    if (isdigit(c)) {
        bool isFloat = false;

        while (isdigit(peekChar())) {
            advance();
        }

        // Check for decimal part
        if (peekChar() == '.' && isdigit(peekNextChar())) {
            isFloat = true;
            advance(); // Consume the '.'

            while (isdigit(peekChar())) {
                advance();
            }
        }

        return makeToken(isFloat ? TokenType::FLOAT : TokenType::INTEGER);
    }

    // Handle operators and other single-character tokens
    switch (c) {
        case '=': return makeToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::ASSIGN);
        case '!': return makeToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        case '<': return makeToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        case '>': return makeToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        case '|': return makeToken(match('|') ? TokenType::PIPE_PIPE : TokenType::PIPE);
        case '&': return makeToken(match('&') ? TokenType::AMP_AMP : TokenType::AMPERSAND);
        case '~': return makeToken(TokenType::TILDE);
        case '+': return makeToken(TokenType::PLUS);
        case '-': return makeToken(TokenType::MINUS);
        case '*': return makeToken(TokenType::ASTERISK);
        case '/': return makeToken(TokenType::SLASH);
        case '%': return makeToken(TokenType::MODULO);
        case '^': return makeToken(TokenType::CARET);
        case '(': return makeToken(TokenType::LEFT_PAREN);
        case ')': return makeToken(TokenType::RIGHT_PAREN);
        case ',': return makeToken(TokenType::COMMA);
        case ';': return makeToken(TokenType::SEMICOLON);
        default:  return makeToken(TokenType::UNKNOWN);
    }
}

Token Lexer::peek() {
    size_t savedCurrent = current;
    size_t savedStart = start;
    size_t savedLine = line;

    Token token = next();

    current = savedCurrent;
    start = savedStart;
    line = savedLine;

    return token;
}

Token Lexer::makeToken(TokenType type) const {
    std::string text = source.substr(start, current - start);
    return Token(type, text, line);
}

Token Lexer::string() {
    std::string value;

    while (peekChar() != '"' && !isAtEnd()) {
        if (peekChar() == '\\') {
            advance(); // Consume the backslash

            // Handle escape sequences
            switch (peekChar()) {
                case 'n': value += '\n'; break;
                case 't': value += '\t'; break;
                case 'r': value += '\r'; break;
                case '"': value += '"'; break;
                case '\\': value += '\\'; break;
                default:
                    error("Invalid escape sequence");
            }
            advance(); // Consume the escaped character
        } else {
            value += peekChar();
            advance();
        }
    }

    if (isAtEnd()) {
        error("Unterminated string");
    }

    advance(); // Consume the closing "
    return Token(TokenType::STRING, value, line);
}

void Lexer::skipWhitespace() {
    while (true) {
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

            case '/':
                if (peekNextChar() == '/') {
                    // A comment goes until the end of the line
                    while (peekChar() != '\n' && !isAtEnd()) {
                        advance();
                    }
                } else {
                    return;
                }
                break;

            default:
                return;
        }
    }
}

char Lexer::advance() {
    if (isAtEnd()) return '\0';
    return source[current++];
}

char Lexer::peekChar() const {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Lexer::peekNextChar() const {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

bool Lexer::isAtEnd() const {
    return current >= source.length();
}

bool Lexer::match(char expected) {
    if (isAtEnd() || source[current] != expected) return false;
    current++;
    return true;
}

[[noreturn]] void Lexer::error(const std::string& message) const {
    throw std::runtime_error("Line " + std::to_string(line) + ": " + message);
}
