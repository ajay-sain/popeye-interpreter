//
// Created by Ajay Sain on 17/09/25.
//

#ifndef INTERPRETER_NODE_H
#define INTERPRETER_NODE_H

#include <memory>
#include <string>

#include "interpreter/symbol_table.h"

class Node {
public:
    virtual ~Node() = default;
    virtual int resolve() = 0;
};

class OperatorNode : public Node {
private:
    char _operator;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
public:
    OperatorNode(char op, std::unique_ptr<Node> left, std::unique_ptr<Node> right)
        : _operator(op), left(std::move(left)), right(std::move(right)) {}

    int resolve() override {
        switch(_operator) {
            case '+': return left->resolve() + right->resolve();
            case '-': return left->resolve() - right->resolve();
            case '*': return left->resolve() * right->resolve();
            case '/': {
                int right_val = right->resolve();
                if (right_val == 0) throw std::runtime_error("Division by zero");
                return left->resolve() / right_val;
            }
            case '%': {
                int right_val = right->resolve();
                if (right_val == 0) throw std::runtime_error("Modulo by zero");
                return left->resolve() % right_val;
            }
            case '^': return left->resolve() ^ right->resolve();
            default: throw std::runtime_error("Unknown operator");
        }
    }
};

class NumberNode : public Node {
public:
    explicit NumberNode(int value) : value(value) {}

    int value;

    int resolve() override {
        return value;
    }
};

class IdentifierNode : public Node {
public:
    explicit IdentifierNode(std::string name) : name(std::move(name)) {}

    std::string name;

    int resolve() override {
        return SymbolTable::getInstance().get(name);
    }
};

class AssignmentNode : public Node {
    std::string name;
    std::unique_ptr<Node> value;
public:
    AssignmentNode(std::string name, std::unique_ptr<Node> value)
            : name(std::move(name)), value(std::move(value)) {}

    int resolve() override {
        int val = value->resolve();
        SymbolTable::getInstance().add(name, val);
        return val;
    }
};

#endif //INTERPRETER_NODE_H
