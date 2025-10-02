//
// Created by Ajay Sain on 18/09/25.
//

#ifndef INTERPRETER_SYMBOL_TABLE_H
#define INTERPRETER_SYMBOL_TABLE_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include "interpreter/memory/Value.h"

class SymbolTable {
    private:
    std::unordered_map<std::string, Value> symbols;
    static SymbolTable* instance;

    // Private constructor for singleton
    SymbolTable() = default;

    public:
    // Delete copy constructor and assignment operator
    SymbolTable(const SymbolTable&) = delete;
    SymbolTable& operator=(const SymbolTable&) = delete;

    // Get singleton instance
    static SymbolTable& getInstance();

    // Add or update a variable
    void set(const std::string& name, const Value& value) {
        symbols[name] = value;
    }

    // Get a variable's value
    Value get(const std::string& name) const {
        auto it = symbols.find(name);
        if (it == symbols.end()) {
            throw std::runtime_error("Undefined variable: " + name);
        }
        return it->second;
    }

    // Check if a variable exists
    bool exists(const std::string& name) const {
        return symbols.find(name) != symbols.end();
    }

    // Clear all symbols
    void clear() {
        symbols.clear();
    }

    // Print all symbols (for debugging)
    void print() const {
        for (const auto& [name, value] : symbols) {
            std::cout << name << " = " << value << std::endl;
        }
    }

    size_t size() const {
        return symbols.size();
    }

};

#endif // INTERPRETER_SYMBOL_TABLE_H
