#ifndef INTERPRETER_VALUE_H
#define INTERPRETER_VALUE_H

#include <string>
#include <variant>
#include <stdexcept>
#include <iostream> // Added for std::ostream

// Forward declaration for the Value type
class Value {
public:
    // Supported types
    enum class Type {
        NIL,
        INTEGER,
        FLOAT,
        BOOLEAN,
        STRING
    };

    // Default constructor creates a NIL value
    Value() : type(Type::NIL) {}

    // Constructors for different types
    explicit Value(int val) : type(Type::INTEGER), intValue(val) {}
    explicit Value(double val) : type(Type::FLOAT), floatValue(val) {}
    explicit Value(bool val) : type(Type::BOOLEAN), boolValue(val) {}
    explicit Value(const std::string& val) : type(Type::STRING), stringValue(new std::string(val)) {}

    // Copy constructor
    Value(const Value& other);

    // Assignment operator
    Value& operator=(const Value& other);

    // Destructor
    ~Value();

    // Type checking
    Type getType() const { return type; }
    bool isNil() const { return type == Type::NIL; }
    bool isInteger() const { return type == Type::INTEGER; }
    bool isFloat() const { return type == Type::FLOAT; }
    bool isBoolean() const { return type == Type::BOOLEAN; }
    bool isString() const { return type == Type::STRING; }

    // Getters with type checking
    int asInteger() const {
        if (type != Type::INTEGER) throw std::runtime_error("Not an integer");
        return intValue;
    }

    double asFloat() const {
        if (type == Type::FLOAT) return floatValue;
        if (type == Type::INTEGER) return static_cast<double>(intValue);
        throw std::runtime_error("Not a number");
    }

    bool asBoolean() const {
        if (type != Type::BOOLEAN) throw std::runtime_error("Not a boolean");
        return boolValue;
    }

    std::string asString() const {
        switch (type) {
            case Type::NIL: return "nil";
            case Type::INTEGER: return std::to_string(intValue);
            case Type::FLOAT: return std::to_string(floatValue);
            case Type::BOOLEAN: return boolValue ? "true" : "false";
            case Type::STRING: return *stringValue;
            default: return "unknown";
        }
    }

    // Comparison operators
    bool operator==(const Value& other) const;
    bool operator!=(const Value& other) const { return !(*this == other); }

    // Arithmetic operators
    Value operator+(const Value& other) const;
    Value operator-(const Value& other) const;
    Value operator*(const Value& other) const;
    Value operator/(const Value& other) const;
    Value operator%(const Value& other) const;
    Value operator-() const; // Unary minus

    // Type conversion helpers
    double asNumeric() const {
        if (type == Type::FLOAT) return floatValue;
        if (type == Type::INTEGER) return static_cast<double>(intValue);
        throw std::runtime_error("Cannot convert to number");
    }

    // Friend declaration for stream output
    friend std::ostream& operator<<(std::ostream& os, const Value& value);

private:
    Type type;
    union {
        int intValue;
        double floatValue;
        bool boolValue;
        std::string* stringValue;
    };
};

// Stream output operator
inline std::ostream& operator<<(std::ostream& os, const Value& value) {
    return os << value.asString();
}

#endif // INTERPRETER_VALUE_H
