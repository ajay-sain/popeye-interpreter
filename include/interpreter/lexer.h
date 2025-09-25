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
    INTEGER,     // Integer literal (e.g., 42)
    FLOAT,       // Floating-point literal (e.g., 3.14, 1e-5)
    BOOLEAN,     // Boolean literal (true, false)
    STRING,      // String literal (e.g., "hello")
    NIL,         // Nil literal (nil)
    IDENTIFIER,  // Variable/function name (e.g., x, myVar)

    // Keywords
    LET,         // let keyword for variable declaration

    // Operators
    PLUS,        // +
    MINUS,       // -
    ASTERISK,    // *
    SLASH,       // /
    MODULO,      // %
    CARET,       // ^ (exponentiation)
    EQUAL,       // =
    ASSIGN,      // = (for variable assignment)
    LESS,        // <
    LESS_EQUAL,  // <=
    GREATER,     // >
    GREATER_EQUAL, // >=
    EQUAL_EQUAL, // ==
    BANG_EQUAL,  // !=

    // Grouping
    LEFT_PAREN,  // (
    RIGHT_PAREN, // )

    // Punctuation
    COMMA,       // ,
    SEMICOLON,   // ;

    // Special
    UNKNOWN,     // Unknown token (for error handling)
    END_OF_FILE  // End of input
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
    char peekNextChar() const;
    bool match(char expected);
    void skipWhitespace();
    Token makeToken(TokenType type) const;
    Token string();

    // Error handling
    [[noreturn]] void error(const std::string& message) const;

    std::string string() const;
};

#endif // INTERPRETER_LEXER_H
