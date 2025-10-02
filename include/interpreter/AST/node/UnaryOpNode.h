//
// Created by Ajay Sain on 25/09/25.
//

#ifndef INTERPRETER_UNARYOPNODE_H
#define INTERPRETER_UNARYOPNODE_H

#include "interpreter/AST/node/ASTNode.h"

class UnaryOpNode : public Node {
public:
    TokenType op;
    std::unique_ptr<Node> operand;

    UnaryOpNode(TokenType op, std::unique_ptr<Node> operand)
            : op(op), operand(std::move(operand)) {}

    Value evaluate() const override {
        Value operand_val = operand->evaluate();

        switch(op) {
            case TokenType::PLUS: return operand_val;  // Unary plus
            case TokenType::MINUS: return -operand_val; // Unary minus
            case TokenType::BANG: return !operand_val;  // Logical NOT
            case TokenType::TILDE: return ~operand_val; // Bitwise NOT
            default:
                throw std::runtime_error("Unknown unary operator");
        }
    }
};

#endif //INTERPRETER_UNARYOPNODE_H
