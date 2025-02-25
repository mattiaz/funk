# Funk - Placeholder name

## Syntax and Code Style

```funk
# This is a example program written in FunkCode
# Comments can be made with #

##
Multiline comments can be made with 2 #.
The first occuring 2 # is used as end of block.
##

funk add = (numb x, numb y) {return x + y};
funk sub = (numb x, numb y) {return x - y};

funk main = {
    mut numb res = add(1,2);
    numb = sub(numb, 1);
};

main();
```

## Datatypes

### Simple

- `numb`: Integer
- `real`: Floating point number
- `bool`: Boolean (true, false)
- `char`: Character

- `void`: No return type
- `none`: Null/None value, not the same as void

### Composite

- `text`: List of chars
- `list`: Array/Vector of multiple values of the same type

## Variables & References

All variables are immutable as default, the keyword `mut` can be added before the datatype to make it mutable.

Funktions returning data transfers ownership of this data to either a variable or another function.

## Control Structures

To branch the following keywords are available: `if`, `else if`, `else` and `match` with multiple `case`.

Keywords are followed by a `(condition == true)` and the code block. Example:
```funk
if ( x < y )
{
}
else if ( x == y )
{
}
else
{
}
```

Match can only be used for simple datatypes and is used as following:
```funk
match ( x )
{
    case ( 1 ) {}
    case ( 2 ) {}
    case ( 3 )
    case ( 4 )
    case ( 5 ) {}
    none       {}
}
```

For iteration and loops only `while` is available. Complex datatypes such as list might implement an each function, but
this in turn uses while. Example:

```funk
mut numb i = 0;
while (i < 100)
{
    i += 1;
}
```

## Functions

Functions are defined in two parts, arguments and block to execute. Arguments is defined as `(bool x, real y)`.
Following the arguments `{}` are used to define the block of the function. If no arguments are given, argument
parenthesis can be ignored.

All functions are of the "type" `funk` and can either be stored as a "variable" or be executed anonymously. This
combines lambda functions with regular functions to reduce complexity.

Example function definition and execution:
```funk
funk add = (numb a, numb b) { return a + b };
numb a = 10;
numb b = 20;

add(a, b);
add(1, 2);
add(10, add(20, 30));
add(1, { return rand() * 100 });
```

## Piping & Function Chaining

All functions can be "piped" to other functions where the return value will be passed to the next one in the chain.

An example is the following:
```funk
numb total = add(10, 2) >> add(5) >> (numb sum){ return sum * 10 };
list<text> result = fetch_data() >> filter() >> sort();
```

Longer chains can be split on multiple rows beginning with `>>` for each new row.
