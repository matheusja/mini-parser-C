#include <assert.h>
#include <stdlib.h> /*malloc, realloc, free*/
#include <string.h> /*memcpy*/

#include "lexer.h"

struct lexer {
    FILE *p_file;
    size_t n_token;
    size_t c_token;
    struct token s_token[];
};

static void expand_lexer(struct lexer **const p_lex, size_t c_token) {
    (*p_lex)->c_token += c_token;
    *p_lex = realloc(*p_lex, sizeof(struct lexer) + (*p_lex)->c_token * sizeof(struct token));
}

void create_lexer(struct lexer **const p_lex, FILE *const file) {
    create_lexer_c_token(p_lex, file, (size_t)1);
}
void create_lexer_c_token(struct lexer **const p_lex, FILE *const file, const size_t c_token) {
    *p_lex = malloc(sizeof(struct lexer) + c_token*sizeof(struct token));
    (*p_lex)->p_file = file;
    (*p_lex)->n_token = 0;
    (*p_lex)->c_token = c_token;
}

void destroy_lexer(struct lexer **const p_lex) {
    free(*p_lex);
    *p_lex = NULL;
}
void next_token(struct lexer **const p_lex, struct token *const p_token) {
    if ((*p_lex)->n_token > 0) {
        (*p_lex)->n_token--;
        memcpy(p_token, &(*p_lex)->s_token[(*p_lex)->n_token], sizeof(struct token));
        return;
    }
    register FILE *file = (*p_lex)->p_file;
    int curr = fgetc(file);
    while (curr == ' ' || curr == '\t' || curr == '\n' || curr == '\r' || curr == '#') {
        if (curr == '#') {
            while(curr != '\n') {
                if (curr == EOF) {
                    break;
                }
                curr = fgetc(file);
            }
        }
        if (curr == EOF) {
            break;
        }
        curr = fgetc(file);
    }
    switch(curr) {
        case '+':
            p_token->type = token_type_add;
            break;
        case '-':
            p_token->type = token_type_sub;
            break;
        case '*':
            p_token->type = token_type_mult;
            break;
        case '/':
            p_token->type = token_type_div;
            break;
        case '(':
            p_token->type = token_type_open_par;
            break;
        case ')':
            p_token->type = token_type_close_par;
            break;
        case EOF:
            p_token->type = token_type_eof;
            break;
        default:
            if (curr >= '0' && curr <= '9') {
                ungetc(curr, file);
                int n_scanf = fscanf(file, "%d", &p_token->val);
                assert(n_scanf == 1);
                p_token->type = token_type_num;
            } else {
                /*error*/
            }
    }
}
void push_back_token(struct lexer **const p_lex, const struct token *const p_token) {
    if ((*p_lex)->n_token >= (*p_lex)->c_token)
        expand_lexer(p_lex, 1);
    memcpy(&(*p_lex)->s_token[(*p_lex)->n_token], p_token, sizeof(struct token));
    (*p_lex)->n_token++;
}


