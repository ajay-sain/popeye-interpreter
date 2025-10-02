#include "interpreter/value.h"
#include <cmath>
#include <stdexcept>

// Copy constructor
Value::Value(const Value& other) : type(other.type) {
    switch (type) {
        case Type::INTEGER: intValue = other.intValue; break;
        case Type::FLOAT: floatValue = other.floatValue; break;
        case Type::BOOLEAN: boolValue = other.boolValue; break;
        case Type::STRING: stringValue = new std::string(*other.stringValue); break;
        case Type::NIL: break;
    }
}

// Assignment operator
Value& Value::operator=(const Value& other) {
    if (this != &other) {
        // Clean up existing string if any
        if (type == Type::STRING) {
            delete stringValue;
        }

        type = other.type;
        switch (type) {
            case Type::INTEGER: intValue = other.intValue; break;
            case Type::FLOAT: floatValue = other.floatValue; break;
            case Type::BOOLEAN: boolValue = other.boolValue; break;
            case Type::STRING: stringValue = new std::string(*other.stringValue); break;
            case Type::NIL: break;
        }
    }
    return *this;
}

// Destructor
Value::~Value() {
    if (type == Type::STRING) {
        delete stringValue;
    }
}

// Equality comparison
bool Value::operator==(const Value& other) const {
    if (type != other.type) {
        // Try numeric comparison if types are different but both are numbers
        if ((type == Type::INTEGER || type == Type::FLOAT) &&
            (other.type == Type::INTEGER || other.type == Type::FLOAT)) {
            return asNumeric() == other.asNumeric();
        }
        return false;
    }

    switch (type) {
        case Type::NIL: return true;
        case Type::INTEGER: return intValue == other.intValue;
        case Type::FLOAT: return floatValue == other.floatValue;
        case Type::BOOLEAN: return boolValue == other.boolValue;
        case Type::STRING: return *stringValue == *other.stringValue;
        default: return false;
    }
}

// Comparison operators
bool Value::operator<(const Value& other) const {
    if (type == Type::STRING && other.type == Type::STRING) {
        return *stringValue < *other.stringValue;
    }
    return asNumeric() < other.asNumeric();
}

bool Value::operator<=(const Value& other) const {
    if (type == Type::STRING && other.type == Type::STRING) {
        return *stringValue <= *other.stringValue;
    }
    return asNumeric() <= other.asNumeric();
}

bool Value::operator>(const Value& other) const {
    if (type == Type::STRING && other.type == Type::STRING) {
        return *stringValue > *other.stringValue;
    }
    return asNumeric() > other.asNumeric();
}

bool Value::operator>=(const Value& other) const {
    if (type == Type::STRING && other.type == Type::STRING) {
        return *stringValue >= *other.stringValue;
    }
    return asNumeric() >= other.asNumeric();
}

// Arithmetic operators
Value Value::operator+(const Value& other) const {
    if (type == Type::STRING || other.type == Type::STRING) {
        return Value(asString() + other.asString());
    }
    return Value(asNumeric() + other.asNumeric());
}

Value Value::operator-(const Value& other) const {
    return Value(asNumeric() - other.asNumeric());
}

Value Value::operator*(const Value& other) const {
    return Value(asNumeric() * other.asNumeric());
}

Value Value::operator/(const Value& other) const {
    double divisor = other.asNumeric();
    if (divisor == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    return Value(asNumeric() / divisor);
}

Value Value::operator%(const Value& other) const {
    if (type == Type::FLOAT || other.type == Type::FLOAT) {
        return Value(std::fmod(asNumeric(), other.asNumeric()));
    }
    int divisor = other.asInteger();
    if (divisor == 0) {
        throw std::runtime_error("Modulo by zero");
    }
    return Value(asInteger() % divisor);
}

Value Value::operator-() const {
    return Value(-asNumeric());
}

// Bitwise operators
Value Value::operator|(const Value& other) const {
    return Value(asInteger() | other.asInteger());
}

Value Value::operator&(const Value& other) const {
    return Value(asInteger() & other.asInteger());
}

Value Value::operator^(const Value& other) const {
    return Value(asInteger() ^ other.asInteger());
}

Value Value::operator~() const {
    return Value(~asInteger());
}

Value Value::operator<<(const Value& other) const {
    return Value(asInteger() << other.asInteger());
}

Value Value::operator>>(const Value& other) const {
    return Value(asInteger() >> other.asInteger());
}

// Logical operators
Value Value::operator||(const Value& other) const {
    return Value(asBoolean() || other.asBoolean());
}

Value Value::operator&&(const Value& other) const {
    return Value(asBoolean() && other.asBoolean());
}

Value Value::operator!() const {
    return Value(!static_cast<bool>(*this));
}

// Type conversion helpers
