//
// Created by Ajay Sain on 25/09/25.
//

#ifndef INTERPRETER_PARSER_H
#define INTERPRETER_PARSER_H

#include "interpreter/lexer/Lexer.h"
#include "interpreter/AST/node/NodeFactory.h"

class Parser {
public:
    explicit Parser(Lexer& lexer);

    // Parse the entire input and return the root of the AST
    std::unique_ptr<Node> parse();

private:
    Lexer& lexer;
    Token currentToken;
    std::vector<std::unique_ptr<Node>> nodes;
    std::stack<std::unique_ptr<Node>> stack;

    // Helper methods
    void getNextToken();
    void match(TokenType expectedType, const std::string& errorMessage);

    // Parsing methods
    std::unique_ptr<Node> parseAssignment();
    std::unique_ptr<Node> parseExpression();
    std::unique_ptr<Node> parseLogicalOr();
    std::unique_ptr<Node> parseLogicalAnd();
    std::unique_ptr<Node> parseBitwiseOr();
    std::unique_ptr<Node> parseBitwiseXor();
    std::unique_ptr<Node> parseBitwiseAnd();
    std::unique_ptr<Node> parseEquality();
    std::unique_ptr<Node> parseComparison();
    std::unique_ptr<Node> parseTerm();
    std::unique_ptr<Node> parseFactor();
    std::unique_ptr<Node> parseUnary();
    std::unique_ptr<Node> parsePrimary();

    // Evaluation
    Value evaluate(const Node* node);

    // Type conversion
    Value convertToValue(const Token& token) const;
};


#endif //INTERPRETER_PARSER_H
