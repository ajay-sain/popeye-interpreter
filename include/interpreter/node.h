//
// AST Node definitions for the Popeye interpreter
//

#ifndef INTERPRETER_NODE_H
#define INTERPRETER_NODE_H

#include <memory>
#include <string>
#include <cmath>
#include "interpreter/value.h"
#include "interpreter/lexer.h"
#include "interpreter/symbol_table.h"

// Forward declarations
class SymbolTable;

class Node {
public:
    virtual ~Node() = default;
    virtual Value evaluate() const = 0;
};

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
                return Value(std::pow(left_val.asFloat(), right_val.asFloat()));
            }
            // Comparison operators
            case TokenType::LESS:           return Value(left_val < right_val);
            case TokenType::LESS_EQUAL:     return Value(left_val <= right_val);
            case TokenType::GREATER:        return Value(left_val > right_val);
            case TokenType::GREATER_EQUAL:  return Value(left_val >= right_val);
            case TokenType::EQUAL_EQUAL:    return Value(left_val == right_val);
            case TokenType::BANG_EQUAL:     return Value(!(left_val == right_val));
            default:
                throw std::runtime_error("Unknown binary operator");
        }
    }
};

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
            default:
                throw std::runtime_error("Unknown unary operator");
        }
    }
};

class LiteralNode : public Node {
public:
    Value value;

    explicit LiteralNode(Value value) : value(std::move(value)) {}

    Value evaluate() const override {
        return value;
    }
};

class VariableNode : public Node {
public:
    std::string name;

    explicit VariableNode(std::string name) : name(std::move(name)) {}

    Value evaluate() const override {
        return SymbolTable::getInstance().get(name);
    }
};

class AssignmentNode : public Node {
public:
    std::string name;
    std::unique_ptr<Node> expression;

    AssignmentNode(std::string name, std::unique_ptr<Node> expression)
        : name(std::move(name)), expression(std::move(expression)) {}

    Value evaluate() const override {
        Value val = expression->evaluate();
        SymbolTable::getInstance().set(name, val);
        return val;
    }
};

#endif // INTERPRETER_NODE_H
