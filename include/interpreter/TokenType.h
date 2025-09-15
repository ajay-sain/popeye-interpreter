//
// Created by Ajay Sain on 09/09/25.
//

#pragma once

namespace interpreter {
    enum TokenType {
        // Literals (highest precedence)
        IDENTIFIER, STRING, NUMBER,
        // Keywords
        TRUE, FALSE, NIL,

        // Grouping
        LEFT_PAREN, RIGHT_PAREN,
        LEFT_BRACKET, RIGHT_BRACKET,

        // Unary operators
        BANG, TILDE,

        // Multiplicative
        STAR, SLASH, PERCENT,

        // Additive
        PLUS, MINUS,  // MINUS is here as binary operator

        // Bitwise shift (you might want to add these)
//        LESS_LESS, GREATER_GREATER,

        // Relational
        GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

        // Equality
        EQUAL_EQUAL, BANG_EQUAL,

        // Bitwise AND
        AMPERSAND,

        // Bitwise XOR
        CARET,

        // Bitwise OR
        PIPE,

        // Logical AND
        AND,

        // Logical OR
        OR,

        // Assignment
        EQUAL,

        // Other operators
        PLUS_EQUAL, MINUS_EQUAL,  // Compound assignment operators
        STAR_EQUAL, SLASH_EQUAL,  // You might want to add these

        // Other punctuation
        LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, COLON, SEMICOLON, QUESTION,

        // Control flow keywords
        IF, ELSE, WHILE, FOR, FUN, RETURN, CLASS,
        // End markers for blocks
        END_IF, END_WHILE, END_FOR, END_FUN, END_CLASS,

        // Other
        SUPER, THIS, VAR,

        // Special
        EOF_, NEWLINE, ERROR, COMMENT, HASH, TAB, BACKSLASH, BACKSPACE, CARRIAGE_RETURN,
        UNDERSCORE, DOUBLE_QUOTE, SINGLE_QUOTE,
    };
}
