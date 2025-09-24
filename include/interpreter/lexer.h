//
// Lexer for the Popeye programming language
//

#ifndef INTERPRETER_LEXER_H
#define INTERPRETER_LEXER_H

#include <string>
#include <stdexcept>

// Token types for the lexer
enum class TokenType {
    // Literals
    NUMBER,     // Numeric literal (e.g., 42, 3.14)
    IDENTIFIER, // Variable/function name (e.g., x, myVar)

    // Operators
    PLUS,       // +
    MINUS,      // -
    ASTERISK,   // *
    SLASH,      // /
    MODULO,     // %
    CARET,      // ^
    EQUAL,      // =

    // Grouping
    LEFT_PAREN, // (
    RIGHT_PAREN,// )

    // Special
    UNKNOWN,    // Unknown token (for error handling)
    END_OF_FILE, // End of input

    // Keywords
    LET,        // let keyword for variable declaration

    // Variable assignment
    ASSIGN      // = (for variable assignment)
};

// Represents a token with type and lexeme
struct Token {
    TokenType type;
    std::string lexeme;
    size_t line;

    Token(TokenType type, std::string lexeme, size_t line = 1)
        : type(type), lexeme(std::move(lexeme)), line(line) {}
};

class Lexer {
public:
    explicit Lexer(std::string source);

    // Get the next token from the input
    Token next();

    // Peek at the next token without consuming it
    Token peek();

    // Get the current line number (1-based)
    size_t getLine() const { return line; }

private:
    const std::string source;
    size_t current;
    size_t start;
    size_t line;

    // Helper methods
    char advance();
    bool isAtEnd() const;
    char peekChar() const;
    bool match(char expected);

    // Token creation methods
    Token number();
    Token identifier();
    Token makeToken(TokenType type);

    // Error handling
    [[noreturn]] void error(const std::string& message) const;

    void skipWhitespace();
};

#endif // INTERPRETER_LEXER_H
