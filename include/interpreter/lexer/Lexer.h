//
// Lexer for the Popeye programming language
//

#ifndef INTERPRETER_LEXER_H
#define INTERPRETER_LEXER_H

#include <string>
#include <stdexcept>

#include "interpreter/lexer/Token.h"

class Lexer {
private:
    const std::string source;
    size_t current;
    size_t start;
    size_t line;

public:
    explicit Lexer(std::string source);
    Token next();                               // Get the next token from the input
    Token peek();                               // Peek at the next token without consuming it
    size_t getLine() const { return line; }     // Get the current line number (1-based)

private:                                        // Helper methods
    char advance();                             // Advance to the next character
    bool isAtEnd() const;                       // Check if we've reached the end of the input
    char peekChar() const;                      // Get the next character without consuming it
    char peekNextChar() const;                  // Get the character after the next without consuming it
    bool match(char expected);                  // Check if the next character matches the expected character
    void skipWhitespace();                      // Skip over whitespace characters
    Token makeToken(TokenType type) const;      // Create a token of the given type
    Token string();                             // Create a string token

    // Error handling
    [[noreturn]] void error(const std::string& message) const;

    std::string string() const;                 // Get the current source string
};

#endif // INTERPRETER_LEXER_H
