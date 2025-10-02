//
// Created by Ajay Sain on 30/09/25.
//

#ifndef INTERPRETER_NODEFACTORY_H
#define INTERPRETER_NODEFACTORY_H

#include "interpreter/AST/node/ASTNode.h"
#include "interpreter/AST/node/BinaryOpNode.h"
#include "interpreter/AST/node/UnaryOpNode.h"
#include "interpreter/AST/node/VariableNode.h"
#include "interpreter/AST/node/LiteralNode.h"
#include "interpreter/AST/node/AssignmentNode.h"
#include "interpreter/AST/node/NodeType.h"

class NodeFactory{
public:

    static std::unique_ptr<Node> createNode(NodeType type, const std::string& value = "") ;
};


#endif //INTERPRETER_NODEFACTORY_H
