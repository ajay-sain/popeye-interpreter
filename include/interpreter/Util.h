#pragma once

#include <string>
#include "interpreter/TokenType.h"

namespace interpreter {

/**
 * @brief Get the project version as a string
 * @return Version string in the format "MAJOR.MINOR.PATCH"
 */
inline std::string get_version_string() {
    return std::to_string(PROJECT_VERSION_MAJOR) + "." +
           std::to_string(PROJECT_VERSION_MINOR) + "." +
           std::to_string(PROJECT_VERSION_PATCH);
}

    inline int get_precedence(TokenType type) {
        switch (type) {
            // Grouping (highest precedence)
            case TokenType::LEFT_PAREN:
            case TokenType::RIGHT_PAREN:
            case TokenType::LEFT_BRACKET:
            case TokenType::RIGHT_BRACKET:
                return 17;

                // Member access
            case TokenType::DOT:
                return 16;

                // Function call
            case TokenType::LEFT_BRACE:
                return 15;

                // Unary operators
            case TokenType::BANG:
            case TokenType::TILDE:
                return 14;

                // Multiplicative
            case TokenType::STAR:
            case TokenType::SLASH:
            case TokenType::PERCENT:
                return 13;

                // Additive
            case TokenType::PLUS:
            case TokenType::MINUS:  // Binary minus
                return 12;

                // Bitwise shift (if you add them)
                // case TokenType::LESS_LESS:
                // case TokenType::GREATER_GREATER:
                //     return 11;

                // Relational
            case TokenType::GREATER:
            case TokenType::GREATER_EQUAL:
            case TokenType::LESS:
            case TokenType::LESS_EQUAL:
                return 10;

                // Equality
            case TokenType::EQUAL_EQUAL:
            case TokenType::BANG_EQUAL:
                return 9;

                // Bitwise AND
            case TokenType::AMPERSAND:
                return 8;

                // Bitwise XOR
            case TokenType::CARET:
                return 7;

                // Bitwise OR
            case TokenType::PIPE:
                return 6;

                // Logical AND
            case TokenType::AND:
                return 5;

                // Logical OR
            case TokenType::OR:
                return 4;

                // Assignment and compound assignment
            case TokenType::EQUAL:
            case TokenType::PLUS_EQUAL:
            case TokenType::MINUS_EQUAL:
            case TokenType::STAR_EQUAL:
            case TokenType::SLASH_EQUAL:
                return 2;  // Lower than comma/ternary if you add them

                // Comma (if you add it as an operator)
                // case TokenType::COMMA:
                //     return 1;

            default:
                return 0;  // Lowest precedence
        }
    }

} // namespace interpreter
