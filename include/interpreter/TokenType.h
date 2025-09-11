//
// Created by Ajay Sain on 09/09/25.
//

#pragma once

namespace interpreter {
    enum TokenType{
        // Operators
        PLUS, MINUS, STAR, SLASH, PERCENT,
        EQUAL, GREATER, LESS,
        BANG, BANG_EQUAL,
        EQUAL_EQUAL, GREATER_EQUAL, LESS_EQUAL,
        AMPERSAND, PIPE, CARET, TILDE,

        // Punctuators
        LEFT_PAREN, RIGHT_PAREN,
        LEFT_BRACE, RIGHT_BRACE,
        COMMA,
        DOT,
        COLON,
        SEMICOLON,
        UNDERSCORE,
        QUESTION,
        LEFT_BRACKET, RIGHT_BRACKET, DOUBLE_QUOTE, SINGLE_QUOTE,

        // Literals
        IDENTIFIER, STRING, NUMBER,

        // Keywords
        AND, CLASS, END_CLASS, ELSE, FALSE, FUN, END_FUN, FOR, END_FOR, IF, END_IF, NIL, OR,
        RETURN, SUPER, THIS, TRUE, VAR, WHILE, END_WHILE,

        //
        EOF_, NEWLINE, ERROR, COMMENT, HASH, TAB, BACKSLASH, BACKSPACE, CARRIAGE_RETURN
    };
}
