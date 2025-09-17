//
// Created by Ajay Sain on 15/09/25.
//

#include <iostream>
#include <fstream>

#include "spdlog/spdlog.h"

void printBanner(const std::string& message) {
    size_t padding = 4; // Spaces on each side of the message
    size_t totalWidth = message.length() + (padding * 2) + 2; // +2 for the '*' at each end

    // Top border
    std::cout << std::string(totalWidth, '*') << std::endl;

    // Message line
    std::cout << "*" << std::setw(static_cast<int>(totalWidth - 2)) << std::left << std::string(padding, ' ') + message + std::string(padding, ' ') << "*" << std::endl;

    // Bottom border
    std::cout << std::string(totalWidth, '*') << std::endl;
}

int main(int argc, char **argv) {
    printBanner("Hello from popeye language Interpreter written in C++ for fun!");
    while(true){
        std::string input;
        std::cout << "command > ";
        std::getline(std::cin, input);
        if (input == "exit") {
            break;
        }
        spdlog::info("You entered: {}", input);
    }
    return 0;

}
