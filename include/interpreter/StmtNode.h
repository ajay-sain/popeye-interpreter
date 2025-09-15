//
// Created by Ajay Sain on 12/09/25.
//

#pragma once

#include "interpreter/Ast.h"

namespace interpreter {

    class StmtNode : public AstNode {
    public:
        StmtNode(TokenType type) : AstNode(type) {}
        virtual ~StmtNode() = default;
    };


    class BlockStmtNode : public StmtNode {
    public:
        BlockStmtNode(TokenType type) : StmtNode(type) {}
        virtual ~BlockStmtNode() = default;
    };

    class ExpressionStmtNode : public StmtNode {
    public:
        ExpressionStmtNode(TokenType type) : StmtNode(type) {}
        virtual ~ExpressionStmtNode() = default;
    };

    class IfStmtNode : public StmtNode {
    public:
        IfStmtNode(TokenType type) : StmtNode(type) {}
        virtual ~IfStmtNode() = default;
    };

    class WhileStmtNode : public StmtNode {
    public:
        WhileStmtNode(TokenType type) : StmtNode(type) {}
        virtual ~WhileStmtNode() = default;
    };

    class ForStmtNode : public StmtNode {
    public:
        ForStmtNode(TokenType type) : StmtNode(type) {}
        virtual ~ForStmtNode() = default;
    };

    class BreakStmtNode : public StmtNode {
    public:
        BreakStmtNode(TokenType type) : StmtNode(type) {}
        virtual ~BreakStmtNode() = default;
    };

    class ClassStmtNode : public StmtNode {
    public:
        ClassStmtNode(TokenType type) : StmtNode(type) {}
        virtual ~ClassStmtNode() = default;
    };

    class FunctionStmtNode : public StmtNode {
    public:
        FunctionStmtNode(TokenType type) : StmtNode(type) {}
        virtual ~FunctionStmtNode() = default;
    };

    class ReturnStmtNode : public StmtNode {
    public:
        ReturnStmtNode(TokenType type) : StmtNode(type) {}
        virtual ~ReturnStmtNode() = default;
    };

    class VarStmtNode : public StmtNode {
    public:
        VarStmtNode(TokenType type) : StmtNode(type) {}
        virtual ~VarStmtNode() = default;
    };

}
