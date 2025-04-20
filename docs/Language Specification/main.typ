#import "template.typ": *

#show: project.with(
  course: "TDP019 Projekt: Datorspråk",
  title: "Specification & Implementation",
  authors: (
    (name: "Mattias Ajander", email: "mataj513@student.liu.se"),
    (name: "Ludwig Moström", email: "ludmo578@student.liu.se"),
  ),
  date: "2025-02-25",
  term: "Vårterminen 2025",
  version: "1.0",
)

= Revision History
#table(
  columns: (5.5em, 1fr, 5.5em),
  inset: 4pt,
  stroke: 0.5pt,
  [*Version*], [*Description*], [*Date*],
  [3], [Language specification done, added Implementation steps], [2025-03-05],
  [2], [Most of the syntax done, draft of BNF], [2025-02-26],
  [1], [Core idea and some syntax], [2025-02-19],
)

#pagebreak()
= Language Specification

== Syntax and Code Style
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

#pagebreak()
== Data Types
Funk is statically typed, requiring explicit type declarations for all variables. The auto keyword may be introduced for
type inference in the future.

=== Primitive Types
- `numb`: Integer values.
- `real`: Floating-point values (uses . as the decimal separator).
- `bool`: Boolean values (true, false).
- `char`: Single-character values (enclosed in single quotes, e.g., 'c').
- `none`: Represents an absence of value.

=== Composite Types
- `text`: A sequence of char values (strings). Implemented natively or in Funk.
- `list`: A collection of values, using angle brackets to specify type (list<numb>).

=== Variables & Immutability
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

#pagebreak()
== Data Structures

Funk provides data structures as an alternative to traditional class-based inheritance. Data structures combine related data with associated functionality.

- Data structures are defined using the `data` keyword.
- Data structure variables cannot be reassigned after initialization.
- Fields are immutable by default unless declared with `mut`.
- All fields are public and directly accessible using dot notation (`structure.field_name`).
- Methods can access all fields of their containing data structure.
- All functions can read fields in data while only mutable functions can change mutable values.

Examples:
```funk
# Definition
data Rectangle {
    numb width;
    numb height;
    mut numb area = 0;

    # Method that reads fields but doesn't modify anything
    funk calculate_area = {
        return width * height;
    };

    # Method that updates a mutable field
    mut funk update_area = {
        area = width * height;
    };
};

# Initialization
Rectangle rect = Rectangle {
    width = 10,
    height = 20
};

# Usage
numb w = rect.width;
numb a = rect.calculate_area();
rect.update_area();
```

#pagebreak()
== Generics

Funk supports generic type parameters, allowing developers to create reusable data structures and functions that work with multiple types. Generic types are declared using angle brackets with type parameter names:

```funk
struct Pair<A, B> {
    A first;
    B second;
};

funk swap<A, B> = (Pair<A, B> pair) {
    return Pair<B, A> {
        first = pair.second,
        second = pair.first
    };
};
```

#pagebreak()
== Control Structures

=== Conditional Statements
Funk supports if, else if, and else for branching logic:
```funk
if (x < y) {
    "x is less than y" >> print;
} else if (x == y) {
    "x equals y" >> print;
} else {
    "x is greater than y" >> print;
}
```

=== Pattern Matching
Pattern matching with match simplifies multiple conditional checks. It is restricted to primitive types:
```funk
match (x) {
    case (1) { "One" >> print; }
    case (2) { "Two" >> print; }
    case (3)
    case (4)
    case (5) { "Three, Four, or Five" >> print; }
    none     { "Unknown value" >> print; }
}
```

=== Loops
Funk provides only `while` loops. Collections may implement `.each()` for iteration:

```funk
mut numb i = 0;
while (i < 100) {
    i += 1;
}
```

#pagebreak()
== Functions
Functions in Funk can be assigned to variables or used as anonymous expressions. They are defined in two parts,
arguments and code block, If no arguments are given, functions can be used without it.

=== Function Declaration
```funk
funk add = (numb a, numb b) { return a + b };
```

=== Mutable Functions
Regular functions are pure and cannot modify variables outside their scope. Mutable functions (`mut funk`) can:
- Modify `mut` variables from enclosing scope.
- Have side effects.
- Modify data structure properties passed to them.

=== Function Execution
```funk
numb result = add(10, 5);
numb nested = add(10, add(20, 30));
```

=== Anonymous Functions
```funk
add(1, { return rand() * 100 });
```

=== Pattern Matching in Functions

Pattern matching can be used for declarative function definitions:
```funk
funk factorial = (0) { return 1 };
funk factorial = (numb n) { return n * factorial(n - 1) };
```

=== Implicit Returns (Lambda Syntax)
Might be implemented later.
```funk
funk double = (x) -> x * 2;
```

=== Function Overloading
Overloading allows functions to be defined with different type signatures:
```funk
funk print = (numb x) { ... };
funk print = (text x) { ... };
```

#pagebreak()
== Piping & Function Chaining

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
    >> (list<text> lst) { lst.each((text line) { line >> print; }) };
```

== Scope

=== Hierarchy

Funk implements scope in a hierarchical structure:

- Global scope: Contains all top-level declarations (functions, data structures, variables).
- Function scope: Each function creates a new scope containing its parameters and variables.
- Block scope: Created by control structures (if, while) and code blocks `{}` as a new scope.

=== Access
Variables are visible in their declaring scope and all nested scopes. Inner scopes can declare variables with the same name as outer scopes, overloading the outer variable in this and subsequent scopes.

=== Mutability

*Pure functions (default)*
- Can access and modify their local variables if also mutable.
- Can access but not modify their function parameters. Alternatively parameters are sent as copies and not references in which case they can modify them.
- Can access but not modify variables from enclosing scopes.
- Cannot have side effects.
- Can call other pure functions, but not mutable ones.

*Mutable functions (`mut`)*
- Have the same properties as Pure functions.
- Can modify `mut` variables from enclosing scopes and passed parameters.
- Can have side effects.
- Can call both pure and mutable functions.

#pagebreak()

= BNF

#table(
  columns: (0.2fr, 0.8fr),
  align: (center, left),
  stroke: 0.5pt,
  [*Symbol*], [*Explanation*],
  [`<...> | <...>`],[OR],
  [`<...>*`],      [One or more],
  [`[ ... ]`],      [Optional],
  [`R'...'`],       [Regex]
)


#let bnf = read("bnf.txt").split("\n").map(row => row.split("->").map(cell => cell.trim()))

#table(
  columns: 3,
  align: (left, center, left),
  gutter: 0pt,
  inset: 3pt,
  stroke: 0pt,
  ..for rule in bnf {
    if rule.len() == 2 {
      (raw(rule.at(0)), `::=`, raw(rule.at(1)))
    }
    else {
      if (rule.at(0).starts-with("|")) {
        ("", "   |", raw(rule.at(0).replace("| ", "", count: 1)))
      }
      else {
        ("","","")
      }
    }
  }
)

#pagebreak()
= Implementation

== Overview

The project will be completed in 5 phases, which will be carried out sequentially to ensure sufficient time for essential and mandatory tasks.

+ Project setup in C++, including Tokens, Lexer, and basic Parser.
+ Implementation of all features required for a grade 3.
+ Implementation of more advanced features, still within the scope of the course, for a grade 5.
+ Language documentation and preparation for the presentation.
+ Addition of fun, interesting, and personal features to the project, if time permits.

== Detailed Steps

+ Define Token list (Enum) from specification.
+ Implement Token Class with metadata from source code.
+ Lexer Implementation that converts source code to list of tokens.
+ Implement base node for all other nodes to inherit from.
+ Implement nodes for common datatypes.
+ Implement nodes for arithmetic operations.
+ Parser Implementation for evaluating nodes (beginning with arithmetic nodes).
+ Implement a basic print function for easier debugging. Will be correctly implemented later.
+ Extend AST with boolean nodes for boolean logic.
+ Implement scope manager (before variable implementation to prevent later rewrites).
+ Implement variable declaration and assignment.
+ Implement functions (rewrite print function?).
+ Handle parentheses and operator precedence.
+ Error handling and printing metadata such as col, row.
+ Control structures such as if-else and loops
+ Implement match function.
+ Implement mutations.
+ Implement data structures.
+ Implement function piping.
+ Implement pattern-matching for functions.
+ STL, type inference, ownership, unit testing, integration with IDE and more advanced features will be implemented last. Order not yet determined.

== Distribution / Role Assignment

Most of the work will be done individually, but with frequent communication and key decisions made together. At the beginning of the project, we will work closely together to set up the lexer and parser, aiming to quickly create a minimal viable product before transitioning to more individual tasks.

The specific tasks each of us will take on have not yet been determined, but they will be assigned as the project progresses, with a focus on working on features that align with our individual interests.

#pagebreak()
== Deadlines

#table(
  columns: (0.15fr, 0.75fr, 0.10fr),
  stroke: 0.5pt,
  [*Date*],     [*Task*],                                                             [*Status*],
  [2025-03-28], [Lexer complete, can convert source code to list of Tokens.],         [Done],
  [2025-04-01], [Primitive datatypes implemented as AST Nodes.],                      [Done],
  [2025-04-04], [Basic arithmetic operations can be performed and evaluated.],        [Done],
  [2025-04-09], [Basic boolen operations and comparisons completed.],                 [Done],
  [2025-04-11], [Assignment of variables in global scope completed.],                 [Done],
  [2025-04-16], [Function declaration and calling complete, with correct scope.],     [Done],
  [2025-04-18], [Operator precedence complete, if not implemented before.],           [Done],
  [2025-04-21], [Mutation implemented.],                                              [],
  [2025-04-25], [If/Else + Loops implemented.],                                       [Done],
  [2025-04-30], [Recursion implemented. Verify that project meets grade 3 criteria.], [],
  [2025-05-02], [Match + case implemented.],                                          [],
  [2025-05-07], [Data structures implemented.],                                       [],
  [2025-05-09], [Function piping implemented.],                                       [Done],
  [2025-05-12], [Pattern matching implemented. (Optional, in case of extra time.)],   [Done],
  [2025-05-12], [Documentation + Project complete.],                                  [],
  [2025-05-13], [_Project deadline for presentation._],                                [],
  [2025-06-02], [_Project deadline for document submission._],                         [],
)
