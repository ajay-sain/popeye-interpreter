//
// Main entry point for the Popeye interpreter
//

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>

#include "spdlog/spdlog.h"
#include "interpreter/Interpreter.h"

void printBanner(const std::string& message) {
    size_t padding = 4; // Spaces on each side of the message
    size_t totalWidth = message.length() + (padding * 2) + 2; // +2 for the '*' at each end

    // Top border
    std::cout << std::string(totalWidth, '*') << std::endl;

    // Message line
    std::cout << "*" << std::setw(static_cast<int>(totalWidth - 2)) << std::left
              << std::string(padding, ' ') + message + std::string(padding, ' ')
              << "*" << std::endl;

    // Bottom border
    std::cout << std::string(totalWidth, '*') << std::endl;
}

int main(int argc, char** argv) {
    try {
        auto interpreter = Interpreter::Builder()
                .withArgs({argv, argv + argc})
//                .enableDebug(true)
//                .withMaxMemory(1024 * 1024 * 200) // 200MB
                .build();

        return interpreter.run();
    } catch (const std::exception& e) {
        spdlog::error("Fatal error: {}", e.what());
        return 1;
    }
}



