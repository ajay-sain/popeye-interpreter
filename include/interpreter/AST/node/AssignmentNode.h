//
// Created by Ajay Sain on 25/09/25.
//

#ifndef INTERPRETER_ASSIGNMENTNODE_H
#define INTERPRETER_ASSIGNMENTNODE_H

#include "interpreter/AST/node/ASTNode.h"
#include "interpreter/memory/SymbolTable.h"

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

#endif //INTERPRETER_ASSIGNMENTNODE_H
