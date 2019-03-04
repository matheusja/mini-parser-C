# mini-parser-C
A parser of simple mathetical expressions in C

The parser's logic is not on "main.c": its just a simply execution;

The "parse" function in "ast.h" recieves a pointer to a lexer(created then initialized create_lexer*) and returns a pointer to an AST;

It uses a recursive descent parser to assemble a Abstract Syntax Tree;

However, instead of a "vtable polymorphism", each type(num, sum of 2 expressions, subtraction of 2 expressions, ...) is a integer starting from 0;

And a "method-like operation" can be defined by creating a function for each type and wrapping it in a array(via function pointers), then calling it via run_ast_table(first the AST, then an argument then a table of methods) it will determine which one of these will be called and will put them as arguments;

* void create_lexer(struct lexer **const p_lexer, FILE *f)
creates a lexer on p_lexer that reads the stream 'f'
