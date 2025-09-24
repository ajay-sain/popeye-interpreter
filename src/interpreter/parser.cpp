//
// Created by Ajay Sain on 18/09/25.
//

#include "interpreter/parser.h"
#include <stdexcept>
#include <stack>

Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken(TokenType::UNKNOWN, "", 1) {
    getNextToken();
}

void Parser::getNextToken() {
    currentToken = lexer.next();
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

        if (currentToken.type != TokenType::ASSIGN) {
            throw std::runtime_error("Expected '=' after variable name");
        }
        getNextToken(); // Consume '='

        auto expr = parseExpression();
        return std::make_unique<AssignmentNode>(varName, std::move(expr));
    }

    return parseExpression();
}

std::unique_ptr<Node> Parser::parseExpression() {
    infixToPostfix();
    postfixToAST();
    return std::unique_ptr<Node>(tree);
}

void Parser::infixToPostfix() {
    std::vector<std::string> postfix;
    std::stack<std::string> operators;

    while (currentToken.type != TokenType::END_OF_FILE) {
        switch (currentToken.type) {
            case TokenType::NUMBER:
            case TokenType::IDENTIFIER:
                postfix.push_back(currentToken.lexeme);
                getNextToken();
                break;

            case TokenType::LEFT_PAREN:
                operators.push(currentToken.lexeme);
                getNextToken();
                break;

            case TokenType::RIGHT_PAREN: {
                while (!operators.empty() && operators.top() != "(") {
                    postfix.push_back(operators.top());
                    operators.pop();
                }
                if (!operators.empty()) operators.pop();
                getNextToken();
                break;
            }

            default: // Operators
                while (!operators.empty() &&
                       operators.top() != "(" &&
                       precedence(currentToken.lexeme) <= precedence(operators.top())) {
                    postfix.push_back(operators.top());
                    operators.pop();
                }
                operators.push(currentToken.lexeme);
                getNextToken();
                break;
        }
    }

    while (!operators.empty()) {
        postfix.push_back(operators.top());
        operators.pop();
    }

    postfixExpressions = std::move(postfix);
}

void Parser::postfixToAST() {
    std::stack<std::unique_ptr<Node>> stack;

    for (const auto& token : postfixExpressions) {
        if (isdigit(token[0])) {
            nodes.push_back(std::make_unique<NumberNode>(std::stoi(token)));
            stack.push(std::unique_ptr<Node>(nodes.back().release()));
        }
        else if (isalpha(token[0])) {
            nodes.push_back(std::make_unique<IdentifierNode>(token));
            stack.push(std::unique_ptr<Node>(nodes.back().release()));
        }
        else if (token.size() == 1) {
            createOperatorNode(token[0], stack);
        }
    }

    if (!stack.empty()) {
        tree = stack.top().release();
    }
}

int Parser::precedence(const std::string& op) const {
    static const std::unordered_map<std::string, int> precedenceMap = {
        {"+", 1}, {"-", 1},
        {"*", 2}, {"/", 2},
        {"^", 3}
    };
    auto it = precedenceMap.find(op);
    return it != precedenceMap.end() ? it->second : 0;
}

void Parser::createOperatorNode(char op, std::stack<std::unique_ptr<Node>>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Not enough operands for operator");
    }

    auto right = std::move(stack.top());
    stack.pop();
    auto left = std::move(stack.top());
    stack.pop();

    nodes.push_back(std::make_unique<OperatorNode>(
        op,
        std::move(left),
        std::move(right)
    ));

    stack.push(std::unique_ptr<Node>(nodes.back().release()));
}