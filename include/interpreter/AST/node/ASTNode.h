//
// Created by Ajay Sain on 25/09/25.
//

#ifndef INTERPRETER_ASTNODE_H
#define INTERPRETER_ASTNODE_H

#include <memory>
#include <string>
#include <cmath>

#include "interpreter/lexer/TokenType.h"

#include "interpreter/memory/Value.h"
#include "interpreter/AST/node/NodeType.h"

class Node {
public:
    virtual ~Node() = default;
    virtual Value evaluate() const = 0;
};

#endif //INTERPRETER_ASTNODE_H
