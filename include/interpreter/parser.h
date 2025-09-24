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
#include "interpreter/lexer.h"
#include "interpreter/node.h"

class Parser {
private:
    Lexer& lexer;
    Token currentToken;
    std::vector<std::string> postfixExpressions;
    std::vector<std::unique_ptr<Node>> nodes;

    void getNextToken();
    int precedence(const std::string& op) const;
    void createOperatorNode(char op, std::stack<std::unique_ptr<Node>>& stack);

public:
    Node* tree = nullptr;

    explicit Parser(Lexer& lexer);
    ~Parser() = default;

    std::unique_ptr<Node> parse();
    std::unique_ptr<Node> parseAssignment();
    std::unique_ptr<Node> parseExpression();

    void infixToPostfix();
    void postfixToAST();
};

#endif // INTERPRETER_PARSER_H