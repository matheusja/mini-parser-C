#pragma once
#include <stdio.h>

enum token_type {
    token_type_num,
    token_type_add,
    token_type_sub,
    token_type_mult,
    token_type_div,
    token_type_open_par,
    token_type_close_par,
    token_type_eof
};

struct token {
    enum token_type type;
    int              val;
};

struct lexer;

void create_lexer(struct lexer **const p_lex, FILE *const file);
void create_lexer_c_token(struct lexer **const p_lex, FILE *const file, const size_t c_token);
void destroy_lexer(struct lexer **const p_lex);
void next_token(struct lexer **const p_lex, struct token *const p_token);
void push_back_token(struct lexer **const p_lex, const struct token *const p_token);
