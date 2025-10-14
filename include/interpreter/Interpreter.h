//
// Created by Ajay Sain on 14/10/25.
//

#ifndef INTERPRETER_INTERPRETER_H
#define INTERPRETER_INTERPRETER_H

#include <utility>
#include <vector>
#include <string>

class Interpreter{
private:
    std::vector<std::string> files;

    explicit Interpreter(std::vector<std::string> const& files) : files(files) {}
    int runFromFiles();
    int runFromStdin();

public:
    class Builder {
    private:
        std::vector<std::string> args;

    public:
        Builder() = default;
        Builder& withArgs(const std::vector<std::string>& newArgs) {
            args = newArgs;
            return *this;
        }
        Interpreter build();
    };
    int run();
};

#endif //INTERPRETER_INTERPRETER_H
