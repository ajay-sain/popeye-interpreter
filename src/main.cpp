/**
 * @file main.cpp
 * @brief Main entry point for the interpreter project
 */

#include <iostream>
#include <string>

#include "spdlog/spdlog.h"

#include "interpreter/Interpreter.h"

/**
 * @brief Main function
 * @return Exit status
 */
int main() {
    spdlog::info("Hello and welcome to my Interpreter written in C++ for fun!");
    interpreter::Interpreter interpreter;
    interpreter.run();
    return 0;
}
