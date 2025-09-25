//
// Parser for the Popeye programming language
//

#ifndef INTERPRETER_PARSER_H
#define INTERPRETER_PARSER_H

#include <memory>
#include <vector>
#include <stack>
#include <string>
#include "interpreter/lexer.h"
#include "interpreter/node.h"
#include "interpreter/value.h"
#include "interpreter/symbol_table.h"

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
    std::unique_ptr<Node> parseExpression();
    std::unique_ptr<Node> parseComparison();
    std::unique_ptr<Node> parseTerm();
    std::unique_ptr<Node> parseFactor();
    std::unique_ptr<Node> parsePrimary();
    std::unique_ptr<Node> parseAssignment();

    // Evaluation
    Value evaluate(const Node* node);

    // Type conversion
    Value convertToValue(const Token& token) const;
};

#endif // INTERPRETER_PARSER_H