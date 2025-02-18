# Funky - Placeholder name

## Syntax and Code Style

## Datatypes

### Simple

- `numb`: Integer
- `real`: Floating point number
- `bool`: Boolean
- `char`: Character
- `void`: No return type

### Composite

- `text`: List of chars
- `list`: Array/Vector of multiple values of the same type

## Variables & References

All variables are immutable as default, the keyword `mut` can be added before the datatype to make it mutable.

Funktions returning data transfers ownership of this data to either a variable or another function.

## Control Structures

## Functions

Functions are defined in two parts, arguments and block to execute. Arguments is defined as `(bool x, real y)`. Following the arguments `{}` are used to define the block of the function. If no arguments are given, argument parenthesis can be ignored.

All functions are of the "type" `funk` and can either be stored as a "variable" or be executed anonymously. This combines lambda functions with regular functions to reduce complexity.

Example function definition and execution:
```funky
funk add = (numb a, numb b) { return a + b }
numb a = 10
numb b = 20

add(a, b)
add(1, 2)
add(10, add(20, 30))
add(1, { return rand() * 100 })
```

## Piping & Function Chaining

All functions can be "piped" to other functions where the return value will be passed to the next one in the chain.

An example is the following:
```funky
int sum = add(10, 2)
list
```
