#!/bin/bash

# Create the main examples directory structure
mkdir -p /Users/ajaysain/Learning/CPP/interpreter/examples/{01_basics,02_functions,03_data_structures,04_oop,05_error_handling,06_file_io,modules}

# 01_basics/hello_world.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/01_basics/hello_world.popeye << 'EOL'
// hello_world.popeye
print("Hello, Popeye!")
print("Welcome to the Popeye programming language!")

// String concatenation
name = "Sailor"
greeting = "Ahoy, " + name + "!"
print(greeting)
EOL

# 01_basics/variables.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/01_basics/variables.popeye << 'EOL'
// variables.popeye
name = "Popeye"
age = 35
strength = 99.9
hasSpinach = true
weakness = null

// Constants
const VERSION = "1.0.0"
const MAX_STRENGTH = 100

// Multiple assignment
x, y, z = 10, 20, 30

// Type conversion
number_string = "42"
number = int(number_string)
EOL

# 01_basics/control_flow.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/01_basics/control_flow.popeye << 'EOL'
// control_flow.popeye
age = 25
if age < 13 {
    print("Child")
} else if age < 20 {
    print("Teenager")
} else {
    print("Adult")
}

// While loop
print("\nCounting to 5:")
i = 1
while i <= 5 {
    print("  " + string(i))
    i = i + 1
}

// For loop
print("\nEven numbers up to 10:")
for num in range(1, 11) {
    if num % 2 == 0 {
        print("  " + string(num))
    }
}
EOL

# 02_functions/simple_functions.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/02_functions/simple_functions.popeye << 'EOL'
// simple_functions.popeye
func greet(name) {
    return "Hello, " + name + "!"
}

// Function with default parameter
func power(base, exponent = 2) {
    result = 1
    for i in range(1, exponent + 1) {
        result = result * base
    }
    return result
}

// Recursive function
func factorial(n) {
    if n <= 1 {
        return 1
    }
    return n * factorial(n - 1)
}

// Using the functions
print(greet("Popeye"))
print("2^3 =", power(2, 3))
print("5! =", factorial(5))
EOL

# 02_functions/higher_order.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/02_functions/higher_order.popeye << 'EOL'
// higher_order.popeye
func apply_operation(a, b, operation) {
    return operation(a, b)
}

// Function that returns a function
func make_multiplier(factor) {
    return func(x) {
        return x * factor
    }
}

// Using higher-order functions
add = func(a, b) { return a + b }
result = apply_operation(5, 3, add)
print("5 + 3 =", result)

// Using closure
double = make_multiplier(2)
triple = make_multiplier(3)

print("Double of 7:", double(7))
print("Triple of 7:", triple(7))
EOL

# 03_data_structures/lists.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/03_data_structures/lists.popeye << 'EOL'
// lists.popeye
fruits = ["apple", "banana", "cherry"]
numbers = [1, 2, 3, 4, 5]

// List operations
fruits.push("date")
first = fruits[0]
fruits[1] = "blueberry"
length = len(fruits)

// List slicing
first_two = fruits[0:2]
last_two = fruits[-2:]

// List comprehension
squares = [x * x for x in numbers if x % 2 == 0]

print("Fruits:", fruits)
print("First fruit:", first)
print("Squared evens:", squares)
EOL

# 03_data_structures/dictionaries.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/03_data_structures/dictionaries.popeye << 'EOL'
// dictionaries.popeye
person = {
    "name": "Popeye",
    "age": 35,
    "occupation": "sailor",
    "skills": ["sailing", "fighting", "whistling"]
}

// Accessing values
name = person["name"]
age = person.get("age", 0)

// Adding/updating
person["strength"] = 100
person["age"] = 36

// Dictionary methods
keys = person.keys()
values = person.values()
has_skill = "sailing" in person["skills"]

print("Person:", person)
print("Name:", name)
print("Has sailing skill:", has_skill)
EOL

# 04_oop/classes.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/04_oop/classes.popeye << 'EOL'
// classes.popeye
class Ship {
    init(name, type, speed = 0) {
        this.name = name
        this.type = type
        this.speed = speed
        this.passengers = []
    }

    accelerate(amount) {
        this.speed += amount
        return this.name + " is now going " + string(this.speed) + " knots"
    }

    add_passenger(name) {
        this.passengers.push(name)
        return name + " boarded " + this.name
    }
}

// Create instances
titanic = Ship("Titanic", "passenger")
blackPearl = Ship("Black Pearl", "pirate ship", 15)

// Use methods
print(titanic.accelerate(10))
print(blackPearl.add_passenger("Jack Sparrow"))

// Inheritance
class CargoShip extends Ship {
    init(name, capacity) {
        super(name, "cargo")
        this.capacity = capacity
        this.cargo = []
    }

    load(item, quantity) {
        if (len(this.cargo) + quantity > this.capacity) {
            throw "Not enough capacity!"
        }
        this.cargo.push([item, quantity])
        return "Loaded " + string(quantity) + " " + item
    }
}

// Using the derived class
freighter = CargoShip("Ever Given", 1000)
print(freighter.load("containers", 500))
EOL

# 05_error_handling/exceptions.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/05_error_handling/exceptions.popeye << 'EOL'
// exceptions.popeye
func divide(a, b) {
    if b == 0 {
        throw "Division by zero"
    }
    return a / b
}

// Try-catch-finally
try {
    result = divide(10, 0)
    print("Result:", result)
} catch error {
    print("Error:", error)
} finally {
    print("This always runs")
}

// Custom error class
class ValidationError {
    init(message) {
        this.message = message
    }
}

// Using custom error
func validate_age(age) {
    if age < 0 {
        throw ValidationError("Age cannot be negative")
    }
    if age > 150 {
        throw ValidationError("Age seems invalid")
    }
    return "Age is valid"
}

// Handle custom error
try {
    validate_age(200)
} catch e if e is ValidationError {
    print("Validation error:", e.message)
} catch e {
    print("Unexpected error:", e)
}
EOL

# 06_file_io/file_operations.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/06_file_io/file_operations.popeye << 'EOL'
// file_operations.popeye
filename = "example.txt"

// Writing to a file
try {
    file = open(filename, "w")
    file.write("Hello, Popeye!\\n")
    file.write("This is a test file.\\n")
    file.write("Current timestamp: " + string(now()) + "\\n")
    file.close()
    print("Successfully wrote to", filename)

    // Reading from a file
    file = open(filename, "r")
    content = file.read()
    file.close()

    print("\\nFile content:")
    print(content)

    // Reading line by line
    print("\\nReading line by line:")
    file = open(filename, "r")
    while (line = file.readline()) != null {
        print("Line:", line.strip())
    }
    file.close()

} catch e {
    print("File error:", e.message)
} finally {
    if (file) {
        file.close()
    }
}

// Check if file exists
if (file_exists(filename)) {
    print("\\nFile exists, size:", file_size(filename), "bytes")
    delete_file(filename)
    print("File deleted")
}
EOL

# modules/math_utils.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/modules/math_utils.popeye << 'EOL'
// math_utils.popeye
const VERSION = "1.0.0"

func add(a, b) {
    return a + b
}

func subtract(a, b) {
    return a - b
}

func multiply(a, b) {
    return a * b
}

func divide(a, b) {
    if b == 0 {
        throw "Division by zero"
    }
    return a / b
}

// This function is private (convention)
func _internal_helper() {
    return "Internal use only"
}
EOL

# modules/main.popeye
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/modules/main.popeye << 'EOL'
// main.popeye
math = import("math_utils")

print("Math Utils Version:", math.VERSION)
print("5 + 3 =", math.add(5, 3))
print("10 - 4 =", math.subtract(10, 4))

// This would cause an error (private function)
// print(math._internal_helper())

// Error handling with modules
try {
    print("10 / 0 =", math.divide(10, 0))
} catch e {
    print("Error:", e)
}
EOL

# Create README.md
cat > /Users/ajaysain/Learning/CPP/interpreter/examples/README.md << 'EOL'
# Popeye Language Examples

## Directory Structure

- `01_basics/` - Basic syntax, variables, and control flow
  - `hello_world.popeye` - Simple "Hello, World!" program
  - `variables.popeye` - Variables and data types
  - `control_flow.popeye` - If/else, loops, and conditionals

- `02_functions/` - Functions and functional programming
  - `simple_functions.popeye` - Basic function definitions
  - `higher_order.popeye` - Higher-order functions and closures

- `03_data_structures/` - Working with data structures
  - `lists.popeye` - Lists and list operations
  - `dictionaries.popeye` - Dictionaries and their methods

- `04_oop/` - Object-Oriented Programming
  - `classes.popeye` - Classes, objects, and inheritance

- `05_error_handling/` - Error handling
  - `exceptions.popeye` - Try/catch and custom exceptions

- `06_file_io/` - File operations
  - `file_operations.popeye` - Reading from and writing to files

- [modules/](cci:7://file:///Users/ajaysain/Learning/CPP/interpreter/examples/modules:0:0-0:0) - Module system
  - `math_utils.popeye` - Example module
  - `main.popeye` - Using the module

## Running Examples

```bash
# Run a basic example
./popeye examples/01_basics/hello_world.popeye

# Run a module example
./popeye examples/modules/main.popeye