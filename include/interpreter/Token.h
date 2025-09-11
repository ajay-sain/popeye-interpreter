//
// Created by Ajay Sain on 09/09/25.
//

#pragma once

#include <string>
#include "interpreter/TokenType.h"

namespace interpreter {
    class Token{
    public:
        interpreter::TokenType type;
        std::string lexeme;
    };
}
