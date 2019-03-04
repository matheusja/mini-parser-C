#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

/*
    E -> E op E | (E) | N

    E0 -> E0 op0 E1 | E1
    E1 -> E1 op1 E2 | E2
    E2 -> (E0) | N

    E0 -> E1 (op1 E1)*
    E1 -> E2 (op2 E2)*
    E2 -> (E0) | N
*/

static struct ast *parse_E2(struct lexer *p_lexer);
static struct ast *parse_E1(struct lexer *p_lexer);
static struct ast *parse_E0(struct lexer *p_lexer);


static struct ast *parse_E2(struct lexer *p_lexer) {
    struct token tok;
    struct ast *tree;
    next_token(&p_lexer, &tok);
    switch (tok.type) {
        case token_type_num:
            init_ast_num(tree = malloc(sizeof(struct ast)), tok.val);
            return tree;
        case token_type_open_par:
            tree = parse_E0(p_lexer);
            next_token(&p_lexer, &tok);
            if (tok.type != token_type_close_par) {
                fprintf(stderr, "Error: expected ')'\n");
            }
            return tree;
        default:
            fprintf(stderr, "Error: expected '(' or <num>\n");
    }
    return NULL;
}

static int accepted_operator(enum token_type type) {
    return (type != token_type_num) && (type != token_type_open_par);
}

static struct ast *parse_E1(struct lexer *p_lexer) {
    struct token tok;
    struct ast *left;
    struct ast *up;
    struct ast *right;
    left = parse_E2(p_lexer);
    for (next_token(&p_lexer, &tok);accepted_operator(tok.type);next_token(&p_lexer, &tok)) {
        switch (tok.type) {
            case token_type_mult:
                right = parse_E2(p_lexer);
                up = malloc(sizeof(struct ast));
                init_ast_op(up, ast_mult, left, right);
                left = up;
                break;
            case token_type_div:
                right = parse_E2(p_lexer);
                up = malloc(sizeof(struct ast));
                init_ast_op(up, ast_div, left, right);
                left = up;
                break;
            case token_type_add:
            case token_type_sub:
            case token_type_close_par:
            case token_type_eof:
                push_back_token(&p_lexer, &tok);
                return left;
            default:
                break;
        }
    }
    fprintf(stderr, "Erro\n");
    return NULL;
}


static struct ast *parse_E0(struct lexer *p_lexer) {
    struct token tok;
    struct ast *left;
    struct ast *up;
    struct ast *right;
    left = parse_E1(p_lexer);
    for (next_token(&p_lexer, &tok);accepted_operator(tok.type);next_token(&p_lexer, &tok)) {
        switch (tok.type) {
            case token_type_add:
                right = parse_E1(p_lexer);
                up = malloc(sizeof(struct ast));
                init_ast_op(up, ast_sum, left, right);
                left = up;
                break;
            case token_type_sub:
                right = parse_E1(p_lexer);
                up = malloc(sizeof(struct ast));
                init_ast_op(up, ast_sub, left, right);
                left = up;
                break;
            case token_type_close_par:
            case token_type_eof:
                push_back_token(&p_lexer, &tok);
                return left;
            default:
                break;
        }
    }
    fprintf(stderr, "Erro\n");
    return NULL;
}


struct ast *parse(struct lexer *p_lex) {
    return parse_E0(p_lex);
}
