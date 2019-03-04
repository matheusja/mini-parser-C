# mini-parser-C
A parser of simple mathetical expressions in C

The parser's logic is not on "main.c": its just a simply execution;
It uses a recursive descent parser to assemble a Abstract Syntax Tree;
However, instead of a "vtable polymorphism", each type(num, sum of 2 expressions, subtraction of 2 expressions, ...) is a integer starting from 0;
And a "method-like operation" can be defined by creating a function for each type and wrapping it in a array(via function pointers)
