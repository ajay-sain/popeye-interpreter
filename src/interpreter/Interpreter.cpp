//
// Created by Ajay Sain on 09/09/25.
//

#include <iostream>
#include <fstream>

#include "spdlog/spdlog.h"

#include "interpreter/Interpreter.h"
#include "interpreter/parser.h"

void interpreter::Interpreter::run() {
    spdlog::info("Running Interpreter");

    std::ifstream file("/Users/ajaysain/Learning/CPP/interpreter/language_examples/example2.popeye");
    if (!file.is_open()) {
        spdlog::error("Failed to open file");
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string input = buffer.str();
    interpreter::Parser parser(input);
    parser.parse();
//    while (true) {
//        std::cout << "command > ";
//        std::string input;
//        std::getline(std::cin, input);
//        if (input == "exit") {
//            break;
//        }
//        interpreter::Parser parser(input);
//        parser.parse();
//    }
}
