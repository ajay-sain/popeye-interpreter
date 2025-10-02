//
// Created by Ajay Sain on 18/09/25.
//

//
// Symbol table implementation for the Popeye interpreter
//

#include "interpreter/symbol_table.h"

// Initialize static member
SymbolTable* SymbolTable::instance = nullptr;

// Get singleton instance implementation
SymbolTable& SymbolTable::getInstance() {
    if (!instance) {
        instance = new SymbolTable();
    }
    return *instance;
}
