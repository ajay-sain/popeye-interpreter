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

        auto expr = parseExpression();
        return std::make_unique<AssignmentNode>(varName, std::move(expr));
    }

    return parseExpression();
}

std::unique_ptr<Node> Parser::parseExpression() {
    auto node = parseTerm();

    while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseTerm());
    }

    return node;
}

std::unique_ptr<Node> Parser::parseTerm() {
    auto node = parseFactor();

    while (currentToken.type == TokenType::ASTERISK ||
           currentToken.type == TokenType::SLASH ||
           currentToken.type == TokenType::MODULO) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseFactor());
    }

    return node;
}

std::unique_ptr<Node> Parser::parseFactor() {
    auto node = parsePrimary();

    if (currentToken.type == TokenType::CARET) {
        Token op = currentToken;
        getNextToken();
        node = std::make_unique<BinaryOpNode>(op.type, std::move(node), parseFactor());
    }

    return node;
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
            auto node = parseExpression();
            match(TokenType::RIGHT_PAREN, "Expected ')' after expression");
            return node;
        }
        case TokenType::PLUS:
        case TokenType::MINUS: {
            Token op = token;
            getNextToken();
            return std::make_unique<UnaryOpNode>(op.type, parsePrimary());
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