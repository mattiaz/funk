# Funk - Placeholder name

## Syntax and Code Style
```funk
# Example program written in FunkCode
# Single-line comments use "#"

##
Multiline comments use double "#".
The first occurrence of "##" marks the end of the block.
##

funk add = (numb x, numb y) { return x + y };
funk sub = (numb x, numb y) { return x - y };

funk main = {
    mut numb res = add(1, 2);
    res = sub(res, 1);
};

main();
```

## Data Types
Funk is statically typed, requiring explicit type declarations for all variables. The auto keyword may be introduced for
type inference in the future.

### Primitive Types
- `numb`: Integer values.
- `real`: Floating-point values (uses . as the decimal separator).
- `bool`: Boolean values (true, false).
- `char`: Single-character values (enclosed in single quotes, e.g., 'c').
- `none`: Represents an absence of value.

### Composite Types
- `text`: A sequence of char values (strings). Implemented natively or in Funk.
- `list`: A collection of values, using angle brackets to specify type (list<numb>).

## Variables & Immutability
All variables are immutable by default. To allow mutation, use the `mut` keyword:
```funk
mut numb counter = 0;
counter = counter + 1;
```

Funk enforces ownership transfer in function return values. This means reassignment requires creating a new variable:
```funk
list<numb> numbs = [1, 2, 3];
list<numb> new_numbs = numbs.push(4);
```

## Control Structures

### Conditional Statements
Funk supports if, else if, and else for branching logic:
```funk
if (x < y) {
    print("x is less than y");
} else if (x == y) {
    print("x equals y");
} else {
    print("x is greater than y");
}
```

### Pattern Matching
Pattern matching with match simplifies multiple conditional checks. It is restricted to primitive types:
```funk
match (x) {
    case (1) { print("One"); }
    case (2) { print("Two"); }
    case (3)
    case (4)
    case (5) { print("Three, Four, or Five"); }
    none     { print("Unknown value"); }
}
```

### Loops
Funk provides only `while` loops. Collections may implement `.each()` for iteration:

```funk
mut numb i = 0;
while (i < 100) {
    i += 1;
}
```

## Functions
Functions in Funk can be assigned to variables or used as anonymous expressions. They are defined in two parts,
arguments and code block, If no arguments are given, functions can be used without it.

### Function Declaration
```funk
funk add = (numb a, numb b) { return a + b };
```

### Function Execution
```funk
numb result = add(10, 5);
numb nested = add(10, add(20, 30));
```

### Anonymous Functions
```funk
add(1, { return rand() * 100 });
```

### Pattern Matching in Functions

Pattern matching can be used for declarative function definitions:
```funk
funk factorial = (0) { return 1 };
funk factorial = (numb n) { return n * factorial(n - 1) };
```

### Implicit Returns (Lambda Syntax)
Might be implemented later.
```funk
funk double = (x) -> x * 2;
```

### Function Overloading
Overloading allows functions to be defined with different type signatures:
```funk
funk print = (numb x) { ... };
funk print = (text x) { ... };
```

## Piping & Function Chaining

Funk supports function chaining via the `>>` operator. This allows the output of one function to become the input of
the next:

```funk
numb total = add(10, 2) >> add(5) >> (numb sum) { return sum * 10 };
list<text> sorted_results = fetch_data() >> filter() >> sort();
```

For readability, chains can be split across multiple lines:

```funk
fetch_data()
    >> filter()
    >> sort()
    >> (list<text> lst) { lst.each((text line) { line >> print(); }) };
```
