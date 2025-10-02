//
// Created by Ajay Sain on 25/09/25.
//

#ifndef INTERPRETER_BINARYOPNODE_H
#define INTERPRETER_BINARYOPNODE_H

#include "ASTNode.h"

class BinaryOpNode : public Node {
public:
    TokenType op;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    BinaryOpNode(TokenType op, std::unique_ptr<Node> left, std::unique_ptr<Node> right)
            : op(op), left(std::move(left)), right(std::move(right)) {}

    Value evaluate() const override {
        Value left_val = left->evaluate();
        Value right_val = right->evaluate();

        switch(op) {
            case TokenType::PLUS: return left_val + right_val;
            case TokenType::MINUS: return left_val - right_val;
            case TokenType::ASTERISK: return left_val * right_val;
            case TokenType::SLASH: {
                if (right_val == Value(0)) throw std::runtime_error("Division by zero");
                return left_val / right_val;
            }
            case TokenType::MODULO: {
                if (right_val == Value(0)) throw std::runtime_error("Modulo by zero");
                return left_val % right_val;
            }
            case TokenType::CARET: {
                // Handle both exponentiation (^) and bitwise XOR (^) based on context
                // In C++, we'll use CARET for bitwise XOR, and we'll use a different token for exponentiation if needed
                return left_val ^ right_val;
            }
                // Bitwise operators
            case TokenType::PIPE: return left_val | right_val;
            case TokenType::AMPERSAND: return left_val & right_val;
                // Comparison operators
            case TokenType::LESS: return Value(left_val < right_val);
            case TokenType::LESS_EQUAL: return Value(left_val <= right_val);
            case TokenType::GREATER: return Value(left_val > right_val);
            case TokenType::GREATER_EQUAL: return Value(left_val >= right_val);
            case TokenType::EQUAL_EQUAL: return Value(left_val == right_val);
            case TokenType::BANG_EQUAL: return Value(!(left_val == right_val));
                // Logical operators
            case TokenType::PIPE_PIPE: return left_val || right_val;
            case TokenType::AMP_AMP: return left_val && right_val;
            default:
                throw std::runtime_error("Unknown binary operator");
        }
    }
};

#endif //INTERPRETER_BINARYOPNODE_H
