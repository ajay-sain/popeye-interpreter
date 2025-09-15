//
// Created by Ajay Sain on 12/09/25.
//

#pragma once

#include<memory>

#include "interpreter/Ast.h"

namespace interpreter {

    class ExpNode : public AstNode {
    public:
        ExpNode(TokenType type) : AstNode(type) {}
        virtual ~ExpNode() = default;
    };

    class BinaryExpNode : public ExpNode {
    public:
        BinaryExpNode(TokenType type) : ExpNode(type) {}
        virtual ~BinaryExpNode() = default;
    };

    class UnaryExpNode : public ExpNode {
    public:
        UnaryExpNode(TokenType type) : ExpNode(type) {}
        virtual ~UnaryExpNode() = default;
    };

    class LiteralExpNode : public ExpNode {
    public:
        LiteralExpNode(TokenType type) : ExpNode(type) {}
        virtual ~LiteralExpNode() = default;
    };

    class LogicalExpNode : public ExpNode {
    public:
        LogicalExpNode(TokenType type) : ExpNode(type) {}
        virtual ~LogicalExpNode() = default;
    };

    class GroupingExpNode : public ExpNode {
    public:
        GroupingExpNode(TokenType type) : ExpNode(type) {}
        virtual ~GroupingExpNode() = default;
    };

    class VariableExpNode : public ExpNode {
    public:
        VariableExpNode(TokenType type) : ExpNode(type) {}
        virtual ~VariableExpNode() = default;
    };

    class AssignmentExpNode : public ExpNode {
    public:
        AssignmentExpNode(TokenType type) : ExpNode(type) {}
        virtual ~AssignmentExpNode() = default;
    };

    class CallExpNode : public ExpNode {
    public:
        CallExpNode(TokenType type) : ExpNode(type) {}
        virtual ~CallExpNode() = default;
    };

    class GetExpNode : public ExpNode {
    public:
        GetExpNode(TokenType type) : ExpNode(type) {}
        virtual ~GetExpNode() = default;
    };

    class SetExpNode : public ExpNode {
    public:
        SetExpNode(TokenType type) : ExpNode(type) {}
        virtual ~SetExpNode() = default;
    };

    class ThisExpNode : public ExpNode {
    public:
        ThisExpNode(TokenType type) : ExpNode(type) {}
        virtual ~ThisExpNode() = default;
    };

    class SuperExpNode : public ExpNode {
    public:
        SuperExpNode(TokenType type) : ExpNode(type) {}
        virtual ~SuperExpNode() = default;
    };

}
