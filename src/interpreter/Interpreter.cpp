//
// Created by Ajay Sain on 14/10/25.
//
#include "interpreter/Interpreter.h"

#include <stdexcept>
#include <fstream>
#include <iostream>

#include "spdlog/spdlog.h"

Interpreter Interpreter::Builder::build() {
    return Interpreter(args);
}

int Interpreter::run() {
    if (files.size() > 1)
        return runFromFiles();
    else
        return runFromStdin();
}

int Interpreter::runFromFiles() {
    for (const auto &file: files) {
        std::ifstream input(file);
        if (!input.is_open()) {
            throw std::runtime_error("Failed to open file: " + file);
        }
        try {
            // :TODO implement Lexer
            // :TODO implement Parser
            // :TODO implement Evaluator
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}

int Interpreter::runFromStdin() {
    std::cout << "Enter commands: (Ctrl+D to exit)\n";
    std::string line;
    while (std::getline(std::cin, line)) {
        try {
            spdlog::info("Processing line: {}", line);
            // :TODO implement Lexer
            // :TODO implement Parser
            // :TODO implement Evaluator
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
