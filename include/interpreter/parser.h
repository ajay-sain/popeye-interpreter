//
// Created by Ajay Sain on 17/09/25.
//

#ifndef INTERPRETER_PARSER_H
#define INTERPRETER_PARSER_H

#include <string>
#include <stack>
#include <memory>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "interpreter/lexer.h"
#include "interpreter/node.h"

class Parser {
private:
    std::string expression;
    std::vector<std::string> postfixExpressions;
    std::vector<std::unique_ptr<Node>> nodes; // For memory management

    int precedence(const std::string& op) const {
        static const std::unordered_map<std::string, int> precedenceMap = {
                {"+", 1}, {"-", 1},
                {"*", 2}, {"/", 2},
                {"^", 3}
        };
        auto it = precedenceMap.find(op);
        return it != precedenceMap.end() ? it->second : 0;
    }

    void createOperatorNode(char op, std::stack<std::unique_ptr<Node>>& stack) {
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

        // Push a non-owning pointer to the stack
        stack.push(std::unique_ptr<Node>(nodes.back().release()));
    }

public:
    Node* tree = nullptr;

    explicit Parser(const std::string& expr) : expression(expr) {
        postfixToAST();
    }

    ~Parser() = default;

    void infixToPostfix() {
        Lexer lexer(expression);
        std::stack<std::string> operators;
        std::vector<std::string> postfix;

        while (true) {
            Token token = lexer.next();
            if (token.type == TokenType::END_OF_FILE) break;

            switch (token.type) {
                case TokenType::NUMBER:
                case TokenType::IDENTIFIER:
                    postfix.push_back(token.lexeme);
                    break;

                case TokenType::LEFT_PAREN:
                    operators.push(token.lexeme);
                    break;

                case TokenType::RIGHT_PAREN:
                    while (!operators.empty() && operators.top() != "(") {
                        postfix.push_back(operators.top());
                        operators.pop();
                    }
                    if (!operators.empty()) operators.pop();
                    break;

                default: // Operators
                    while (!operators.empty() &&
                           operators.top() != "(" &&
                           precedence(token.lexeme) <= precedence(operators.top())) {
                        postfix.push_back(operators.top());
                        operators.pop();
                    }
                    operators.push(token.lexeme);
                    break;
            }
        }

        while (!operators.empty()) {
            postfix.push_back(operators.top());
            operators.pop();
        }

        postfixExpressions = std::move(postfix);
    }

    void postfixToAST() {
        infixToPostfix();
        std::stack<std::unique_ptr<Node>> stack;

        for (const auto& token : postfixExpressions) {
            if (isdigit(token[0])) {
                nodes.push_back(std::make_unique<NumberNode>(std::stoi(token)));
                // Push a non-owning pointer to the stack
                stack.push(std::unique_ptr<Node>(nodes.back().release()));
            }
            else if (isalpha(token[0])) {
                nodes.push_back(std::make_unique<IdentifierNode>(token));
                // Push a non-owning pointer to the stack
                stack.push(std::unique_ptr<Node>(nodes.back().release()));
            }
            else if (token.size() == 1) {
                createOperatorNode(token[0], stack);
            }
        }

        if (!stack.empty()) {
            // The tree now points to the root node, but doesn't own it
            tree = stack.top().release();
        }
    }
};

#endif // INTERPRETER_PARSER_H