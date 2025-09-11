//
// Created by Ajay Sain on 09/09/25.
//

#pragma once

#include <string>
#include "lexer.h"

namespace interpreter {
    class Parser {
    private:
        Lexer lexer;
    public:
        explicit Parser(const std::string& input) : lexer(input) {}
        void parse();
    };
}
