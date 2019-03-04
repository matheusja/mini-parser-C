#pragma once

enum ast_code {
    ast_num = 0, ast_sum, ast_sub, ast_mult, ast_div,

    ast_last /* Util para determinar o tamanho da ast_table*/
};

//struct ast;

struct ast_node_num {
    int num;
};

struct ast_node_bin_op {
    struct ast *left, *right;
};

struct ast {
    enum ast_code code;
    union {
        struct ast_node_num       number;
        struct ast_node_bin_op operation;
    } data;
};

typedef void (*ast_func)(struct ast *const, void *const p_arg);

void run_ast_table(struct ast *const p_tree, void *const p_arg, const ast_func *const ast_func_table);
void init_ast_num(struct ast *const ptr, const int num);
void init_ast_op(struct ast *const ptr, const enum ast_code astc, struct ast *const left, struct ast *const right);

extern const ast_func eval_ast_table[ast_last];
extern const ast_func print_par_ast_table[ast_last];
extern const ast_func print_rpn_ast_table[ast_last];
extern const ast_func print_brn_ast_table[ast_last];
extern const ast_func destroy_ast_table[ast_last];
