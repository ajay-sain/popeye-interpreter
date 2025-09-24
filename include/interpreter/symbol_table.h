//
// Created by Ajay Sain on 18/09/25.
//

#ifndef INTERPRETER_SYMBOLTABLE_H
#define INTERPRETER_SYMBOLTABLE_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <unordered_map>

class SymbolTable {
    private:
    SymbolTable() = default; // Private constructor

    public:
    static SymbolTable& getInstance() {
        static SymbolTable instance; // Guaranteed to be destroyed.
                                     // Instantiated on first use.
        return instance;
    }

    private:
    std::unordered_map<std::string, int> table;
    SymbolTable(const SymbolTable&) = delete;  // No copy constructor allowed
    void operator=(const SymbolTable&) = delete; // No copy assignment operator allowed

    public:
    void add(const std::string& name, int value) {
        table[name] = value;
    }

    int get(const std::string& name) {
        auto it = table.find(name);
        if (it == table.end()) {
            throw std::runtime_error("Undefined variable: " + name);
        }
        return table[name];
    }

    bool has(const std::string& name) {
        return table.find(name) != table.end();
    }

    void remove(const std::string& name) {
        table.erase(name);
    }

    void clear() {
        table.clear();
    }

    size_t size() const {
        return table.size();
    }

    void print() const {
        for (const auto& [name, value] : table) {
            std::cout << name << " = " << value << std::endl;
        }
    }

};


#endif //INTERPRETER_SYMBOLTABLE_H
