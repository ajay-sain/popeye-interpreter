//
// Created by Ajay Sain on 25/09/25.
//

#ifndef INTERPRETER_VARIABLENODE_H
#define INTERPRETER_VARIABLENODE_H

#include "interpreter/AST/node/ASTNode.h"
#include "interpreter/memory/SymbolTable.h"

class VariableNode : public Node {
public:
    std::string name;

    explicit VariableNode(std::string name) : name(std::move(name)) {}

    Value evaluate() const override {
        return SymbolTable::getInstance().get(name);
    }
};

#endif //INTERPRETER_VARIABLENODE_H
