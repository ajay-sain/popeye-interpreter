//
// Created by Ajay Sain on 25/09/25.
//

#ifndef INTERPRETER_LITERALNODE_H
#define INTERPRETER_LITERALNODE_H

#include "interpreter/AST/node/ASTNode.h"

class LiteralNode : public Node {
public:
    Value value;

    explicit LiteralNode(Value value) : value(std::move(value)) {}

    Value evaluate() const override {
        return value;
    }
};

#endif //INTERPRETER_LITERALNODE_H
