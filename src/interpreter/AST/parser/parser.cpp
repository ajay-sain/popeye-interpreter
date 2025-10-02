//
// Parser implementation for the Popeye interpreter
//

#include "interpreter/parser.h"
#include <stdexcept>
#include <cmath>

Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken{TokenType::END_OF_FILE, ""} {
    getNextToken();
}

void Parser::getNextToken() {
    currentToken = lexer.next();
}

void Parser::match(TokenType expectedType, const std::string& errorMessage) {
    if (currentToken.type != expectedType) {
        throw std::runtime_error(errorMessage);
    }
    getNextToken();
}

std::unique_ptr<Node> Parser::parse() {
    return parseAssignment();
}

std::unique_ptr<Node> Parser::parseAssignment() {
    if (currentToken.type == TokenType::LET) {
        getNextToken(); // Consume 'let'

        if (currentToken.type != TokenType::IDENTIFIER) {
            throw std::runtime_error("Expected identifier after 'let'");
        }

        std::string varName = currentToken.lexeme;
        getNextToken(); // Consume identifier

        match(TokenType::ASSIGN, "Expected '=' after variable name");

        auto expr = parseLogicalOr();
        return std::make_unique<AssignmentNode>(varName, std::move(expr));
    }

    return parseLogicalOr();
}

std::unique_ptr<Node> Parser::parseLogicalOr() {
    auto node = parseLogicalAnd();

    while (currentToken.type == TokenType::PIPE_PIPE) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseLogicalAnd());
    }

    return node;
}

std::unique_ptr<Node> Parser::parseLogicalAnd() {
    return parseBitwiseOr();
}

std::unique_ptr<Node> Parser::parseBitwiseOr() {
    auto node = parseBitwiseXor();

    while (currentToken.type == TokenType::PIPE) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseBitwiseXor());
    }

    return node;
}

std::unique_ptr<Node> Parser::parseBitwiseXor() {
    auto node = parseBitwiseAnd();

    while (currentToken.type == TokenType::CARET) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseBitwiseAnd());
    }

    return node;
}

std::unique_ptr<Node> Parser::parseBitwiseAnd() {
    auto node = parseEquality();

    while (currentToken.type == TokenType::AMPERSAND) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseEquality());
    }

    return node;
}

std::unique_ptr<Node> Parser::parseEquality() {
    auto node = parseComparison();

    while (currentToken.type == TokenType::EQUAL_EQUAL ||
           currentToken.type == TokenType::BANG_EQUAL) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseComparison());
    }

    return node;
}

std::unique_ptr<Node> Parser::parseComparison() {
    auto node = parseTerm();

    while (currentToken.type == TokenType::LESS ||
           currentToken.type == TokenType::LESS_EQUAL ||
           currentToken.type == TokenType::GREATER ||
           currentToken.type == TokenType::GREATER_EQUAL) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseTerm());
    }

    return node;
}

std::unique_ptr<Node> Parser::parseTerm() {
    auto node = parseFactor();

    while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseFactor());
    }

    return node;
}

std::unique_ptr<Node> Parser::parseFactor() {
    auto node = parseUnary();

    while (currentToken.type == TokenType::ASTERISK ||
           currentToken.type == TokenType::SLASH ||
           currentToken.type == TokenType::MODULO) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseUnary());
    }

    return node;
}

std::unique_ptr<Node> Parser::parseUnary() {
    if (currentToken.type == TokenType::MINUS ||
        currentToken.type == TokenType::BANG ||
        currentToken.type == TokenType::TILDE) {
        Token op = currentToken;
        getNextToken();
        return std::make_unique<UnaryOpNode>(op.type, parseUnary());
    }

    return parsePrimary();
}

std::unique_ptr<Node> Parser::parsePrimary() {
    Token token = currentToken;

    switch (token.type) {
        case TokenType::INTEGER:
        case TokenType::FLOAT: {
            getNextToken();
            if (token.type == TokenType::FLOAT) {
                return std::make_unique<LiteralNode>(Value(std::stod(token.lexeme)));
            } else {
                return std::make_unique<LiteralNode>(Value(std::stoi(token.lexeme)));
            }
        }
        case TokenType::BOOLEAN: {
            getNextToken();
            bool value = (token.lexeme == "true");
            return std::make_unique<LiteralNode>(Value(value));
        }
        case TokenType::STRING: {
            getNextToken();
            return std::make_unique<LiteralNode>(Value(token.lexeme));
        }
        case TokenType::NIL: {
            getNextToken();
            return std::make_unique<LiteralNode>(Value());
        }
        case TokenType::IDENTIFIER: {
            std::string varName = token.lexeme;
            getNextToken();
            return std::make_unique<VariableNode>(varName);
        }
        case TokenType::LEFT_PAREN: {
            getNextToken();
            auto node = parseLogicalOr();
            match(TokenType::RIGHT_PAREN, "Expected ')' after expression");
            return node;
        }
        default:
            throw std::runtime_error("Unexpected token: " + token.lexeme);
    }
}

Value Parser::evaluate(const Node* node) {
    return node->evaluate();
}

Value Parser::convertToValue(const Token& token) const {
    switch (token.type) {
        case TokenType::INTEGER:
            return Value(std::stoi(token.lexeme));
        case TokenType::FLOAT:
            return Value(std::stod(token.lexeme));
        case TokenType::BOOLEAN:
            return Value(token.lexeme == "true");
        case TokenType::STRING:
            return Value(token.lexeme);
        case TokenType::NIL:
            return Value();
        case TokenType::IDENTIFIER:
            return SymbolTable::getInstance().get(token.lexeme);
        default:
            throw std::runtime_error("Cannot convert token to value: " + token.lexeme);
    }
}