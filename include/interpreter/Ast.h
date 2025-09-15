//
// Created by Ajay Sain on 11/09/25.
//

#pragma once

#include "TokenType.h"

namespace interpreter {

    class AstNode{
        private:
            TokenType type;
        public:
        AstNode(TokenType type): type(type){};
        virtual ~AstNode() = default;
    };

}
