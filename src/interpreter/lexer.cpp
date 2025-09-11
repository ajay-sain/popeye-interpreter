//
// Created by Ajay Sain on 09/09/25.
//

#include <cctype>
#include <string>
#include "interpreter/lexer.h"
#include "spdlog/spdlog.h"
interpreter::Token interpreter::Lexer::next() {
    previousToken = currentToken;
    // Skip whitespace
    while (current < expression.length() && isspace(expression[current])) {
        if (expression[current] == '\n') line++;
        current++;
    }
    if (current >= expression.length()) {
        return Token{TokenType::EOF_, ""};
    }
    char c = expression[current];
    start = current;

    // Handle single character tokens
    switch (c) {
        case '(': advance(); return Token{TokenType::LEFT_PAREN, "("};
        case ')': advance(); return Token{TokenType::RIGHT_PAREN, ")"};
        case '{': advance(); return Token{TokenType::LEFT_BRACE, "{"};
        case '}': advance(); return Token{TokenType::RIGHT_BRACE, "}"};
        case ',': advance(); return Token{TokenType::COMMA, ","};
        case '.': advance(); return Token{TokenType::DOT, "."};
        case '-': advance(); return Token{TokenType::MINUS, "-"};
        case '+': advance(); return Token{TokenType::PLUS, "+"};
        case ';': advance(); return Token{TokenType::SEMICOLON, ";"};
        case ':': advance(); return Token{TokenType::COLON, ":"};
        case '*': advance(); return Token{TokenType::STAR, "*"};
        case '%': advance(); return Token{TokenType::PERCENT, "%"};
        case '^': advance(); return Token{TokenType::CARET, "^"};
        case '&': advance(); return Token{TokenType::AMPERSAND, "&"};
        case '|': advance(); return Token{TokenType::PIPE, "|"};
        case '~': advance(); return Token{TokenType::TILDE, "~"};
        case '?': advance(); return Token{TokenType::QUESTION, "?"};
        case '[': advance(); return Token{TokenType::LEFT_BRACKET, "["};
        case ']': advance(); return Token{TokenType::RIGHT_BRACKET, "]"};
        case '#': advance(); return Token{TokenType::HASH, "#"};

            // Handle one or two character tokens
        case '!':
            advance();
            if (match('=')) return Token{TokenType::BANG_EQUAL, "!="};
            return Token{TokenType::BANG, "!"};

        case '=':
            advance();
            if (match('=')) return Token{TokenType::EQUAL_EQUAL, "=="};
            return Token{TokenType::EQUAL, "="};

        case '<':
            advance();
            if (match('=')) return Token{TokenType::LESS_EQUAL, "<="};
            return Token{TokenType::LESS, "<"};

        case '>':
            advance();
            if (match('=')) return Token{TokenType::GREATER_EQUAL, ">="};
            return Token{TokenType::GREATER, ">"};
//
//        case '\\':
//            advance();
//            switch (peekNextChar()) {
//                case '\\': return Token{TokenType::BACKSLASH, "\\"};
//                case '\'': return Token{TokenType::SINGLE_QUOTE, "\\'"};
//                case '"': return Token{TokenType::DOUBLE_QUOTE, "\\\""};
//                case 'n': return Token{TokenType::NEWLINE, "\\n"};
//                case 't': return Token{TokenType::TAB, "\\t"};
//                case 'r': return Token{TokenType::CARRIAGE_RETURN, "\\r"};
//                case 'b': return Token{TokenType::BACKSPACE, "\\b"};
//                default: return Token{TokenType::ERROR, "Unexpected escape character"};
//            }
        case '/':
            if (peekNextChar() == '/') {
                advance(); // skip the first '/'
                advance(); // skip the second '/'
                std::string comment;
                while (current < expression.length() && expression[current] != '\n') {
                    comment += expression[current];
                    current++;
                }
                return Token{TokenType::COMMENT, std::move(comment)};
            }
            else
                return Token{TokenType::SLASH, "/"};

            // Handle string literals
        case '\'': return _string(TokenType::SINGLE_QUOTE);
        case '"': return _string(TokenType::DOUBLE_QUOTE);

            // Handle numbers
        default:
            if (isdigit(c)) return _number();
            if (isalpha(c) || c == '_') return _identifier();

            // Handle unexpected characters
            advance();
            return Token{TokenType::ERROR, "Unexpected character"};
    }
}

bool interpreter::Lexer::match(char expected) {
    if (isAtEnd()) return false;
    if (expression[current] != expected) return false;

    current++;
    return true;
}

char interpreter::Lexer::peekNextChar() {
    if (current + 1 >= expression.length()) return '\0';
    return expression[current + 1];
}

interpreter::Token interpreter::Lexer::peek() {
    if (current < expression.length()) {
        char c = expression[current];
        return Token{static_cast<TokenType>(c), std::string(1, c)};
    }
    return Token{TokenType::EOF_, ""};
}

void interpreter::Lexer::advance() {
    if (current < expression.length()) {
        current++;
    }
}

interpreter::Token interpreter::Lexer::_number() {
    while (current < expression.length() && isdigit(expression[current])) {
        advance();
    }
    // Look for a fractional part.
    if (current < expression.length() - 1 &&
        expression[current] == '.' &&
        isdigit(expression[current + 1])) {
        // Consume the "."
        advance();

        while (current < expression.length() && isdigit(expression[current])) {
            advance();
        }
    }

    std::string numStr = expression.substr(start, current - start);
    return Token{TokenType::NUMBER, numStr};
}

interpreter::Token interpreter::Lexer::_identifier() {
    while (isdigit(expression[current]) || isalpha(expression[current]) || expression[current] == '_') advance();

    std::string text = expression.substr(start, current - start);

    // Check if the identifier is a reserved keyword
    static const std::unordered_map<std::string, TokenType> keywords = {
            {"and", TokenType::AND},
            {"class", TokenType::CLASS},
            {"endclass", TokenType::END_CLASS},
            {"else", TokenType::ELSE},
            {"false", TokenType::FALSE},
            {"for", TokenType::FOR},
            {"endfor", TokenType::END_FOR},
            {"fun", TokenType::FUN},
            {"endfun", TokenType::END_FUN},
            {"if", TokenType::IF},
            {"endif", TokenType::END_IF},
            {"nil", TokenType::NIL},
            {"or", TokenType::OR},
            {"return", TokenType::RETURN},
            {"super", TokenType::SUPER},
            {"this", TokenType::THIS},
            {"true", TokenType::TRUE},
            {"var", TokenType::VAR},
            {"while", TokenType::WHILE},
            {"endwhile", TokenType::END_WHILE}
    };

    auto it = keywords.find(text);
    if (it != keywords.end()) {
        return Token{it->second, text};
    }

    return Token{TokenType::IDENTIFIER, text};

}

interpreter::Token interpreter::Lexer::_string(TokenType type) {
    // Store the opening quote position and skip it
    int startPos = current;
    char quoteChar = (type == TokenType::SINGLE_QUOTE) ? '\'' : '"';

    // Skip the opening quote
    advance();

    std::string value;
    bool escape = false;

    while (!isAtEnd()) {
        char c = expression[current];

        // Handle escape sequences
        if (escape) {
            switch (c) {
                case 'n': value += '\n'; break;
                case 't': value += '\t'; break;
                case 'r': value += '\r'; break;
                case '\\': value += '\\'; break;
                case '\'': value += '\''; break;
                case '"': value += '"'; break;
                default:
                    // Invalid escape sequence
                    return Token{TokenType::ERROR, "Invalid escape sequence"};
            }
            escape = false;
        } else if (c == '\\') {
            escape = true;
        } else if (c == quoteChar) {
            // Found the closing quote
            advance(); // consume the closing quote
            return Token{TokenType::STRING, value};
        } else if (c == '\n') {
            line++;
            value += c;
        } else {
            value += c;
        }

        advance();
    }

    // If we get here, we reached the end of input without finding the closing quote
    return Token{TokenType::ERROR, "Unterminated string"};
}

bool interpreter::Lexer::isAtEnd() {
    return current >= expression.length();
}
