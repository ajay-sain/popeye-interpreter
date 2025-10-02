//
// Created by Ajay Sain on 25/09/25.
//

#ifndef INTERPRETER_TOKENTYPE_H
#define INTERPRETER_TOKENTYPE_H

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
    TILDE,       // ~ (bitwise NOT)
    BANG,        // ! (logical NOT)
    EQUAL,       // =
    ASSIGN,      // = (for variable assignment)
    PIPE,        // |
    AMPERSAND,   // &
    PIPE_PIPE,   // ||
    AMP_AMP,     // &&
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

#endif //INTERPRETER_TOKENTYPE_H
