#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

void run_ast_table(struct ast *const p_tree, void *const p_arg, const ast_func *const ast_func_table) {
    (*ast_func_table[p_tree->code])(p_tree, p_arg);
}

void init_ast_num(struct ast *const ptr, const int num) {
    ptr->code = ast_num;
    ptr->data.number.num = num;
}

void init_ast_op(struct ast *const ptr, const enum ast_code astc, struct ast *const left, struct ast *const right) {
    ptr->code = astc;
    ptr->data.operation.left = left;
    ptr->data.operation.right = right;
}

static void eval_ast_num(struct ast *const num, void *const p_arg) {
    *(int *)p_arg = num->data.number.num;
}
static void eval_ast_sum(struct ast *const num, void *const p_arg) {
    int left, right;
    run_ast_table(num->data.operation.left, (void *)&left, eval_ast_table);
    run_ast_table(num->data.operation.right, (void *)&right, eval_ast_table);
    *(int *)p_arg = left + right;
}
static void eval_ast_sub(struct ast *const num, void *const p_arg) {
    int left, right;
    run_ast_table(num->data.operation.left, (void *)&left, eval_ast_table);
    run_ast_table(num->data.operation.right, (void *)&right, eval_ast_table);
    *(int *)p_arg = left - right;
}
static void eval_ast_mult(struct ast *const num, void *const p_arg) {
    int left, right;
    run_ast_table(num->data.operation.left, (void *)&left, eval_ast_table);
    run_ast_table(num->data.operation.right, (void *)&right, eval_ast_table);
    *(int *)p_arg = left * right;
}
static void eval_ast_div(struct ast *const num, void *const p_arg) {
    int left, right;
    run_ast_table(num->data.operation.left, (void *)&left, eval_ast_table);
    run_ast_table(num->data.operation.right, (void *)&right, eval_ast_table);
    *(int *)p_arg = left / right;
}
static void print_par_ast_num(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "%d", num->data.number.num);
}
static void print_par_ast_sum(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "(");
    run_ast_table(num->data.operation.left, p_arg, print_par_ast_table);
    fprintf((FILE *)p_arg, " + ");
    run_ast_table(num->data.operation.right, p_arg, print_par_ast_table);
    fprintf((FILE *)p_arg, ")");
}
static void print_par_ast_sub(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "(");
    run_ast_table(num->data.operation.left, p_arg, print_par_ast_table);
    fprintf((FILE *)p_arg, " - ");
    run_ast_table(num->data.operation.right, p_arg, print_par_ast_table);
    fprintf((FILE *)p_arg, ")");
}
static void print_par_ast_mult(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "(");
    run_ast_table(num->data.operation.left, p_arg, print_par_ast_table);
    fprintf((FILE *)p_arg, " * ");
    run_ast_table(num->data.operation.right, p_arg, print_par_ast_table);
    fprintf((FILE *)p_arg, ")");
}
static void print_par_ast_div(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "(");
    run_ast_table(num->data.operation.left, p_arg, print_par_ast_table);
    fprintf((FILE *)p_arg, " / ");
    run_ast_table(num->data.operation.right, p_arg, print_par_ast_table);
    fprintf((FILE *)p_arg, ")");
}

static void print_rpn_ast_num(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "%d", num->data.number.num);
}

static void print_rpn_ast_sum(struct ast *const num, void *const p_arg) {
    run_ast_table(num->data.operation.left, p_arg, print_rpn_ast_table);
    fprintf((FILE *)p_arg, " ");
    run_ast_table(num->data.operation.right, p_arg, print_rpn_ast_table);
    fprintf((FILE *)p_arg, " +");
}

static void print_rpn_ast_sub(struct ast *const num, void *const p_arg) {
    run_ast_table(num->data.operation.left, p_arg, print_rpn_ast_table);
    fprintf((FILE *)p_arg, " ");
    run_ast_table(num->data.operation.right, p_arg, print_rpn_ast_table);
    fprintf((FILE *)p_arg, " -");
}

static void print_rpn_ast_mult(struct ast *const num, void *const p_arg) {
    run_ast_table(num->data.operation.left, p_arg, print_rpn_ast_table);
    fprintf((FILE *)p_arg, " ");
    run_ast_table(num->data.operation.right, p_arg, print_rpn_ast_table);
    fprintf((FILE *)p_arg, " *");
}

static void print_rpn_ast_div(struct ast *const num, void *const p_arg) {
    run_ast_table(num->data.operation.left, p_arg, print_rpn_ast_table);
    fprintf((FILE *)p_arg, " ");
    run_ast_table(num->data.operation.right, p_arg, print_rpn_ast_table);
    fprintf((FILE *)p_arg, " /");
}


static void print_brn_ast_num(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "[%d]", num->data.number.num);
}

static void print_brn_ast_sum(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "[+");
    run_ast_table(num->data.operation.left, p_arg, print_brn_ast_table);
    run_ast_table(num->data.operation.right, p_arg, print_brn_ast_table);
    fprintf((FILE *)p_arg, "]");
}

static void print_brn_ast_sub(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "[-");
    run_ast_table(num->data.operation.left, p_arg, print_brn_ast_table);
    run_ast_table(num->data.operation.right, p_arg, print_brn_ast_table);
    fprintf((FILE *)p_arg, "]");
}

static void print_brn_ast_mult(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "[*");
    run_ast_table(num->data.operation.left, p_arg, print_brn_ast_table);
    run_ast_table(num->data.operation.right, p_arg, print_brn_ast_table);
    fprintf((FILE *)p_arg, "]");
}

static void print_brn_ast_div(struct ast *const num, void *const p_arg) {
    fprintf((FILE *)p_arg, "[/");
    run_ast_table(num->data.operation.left, p_arg, print_brn_ast_table);
    run_ast_table(num->data.operation.right, p_arg, print_brn_ast_table);
    fprintf((FILE *)p_arg, "]");
}

static void destroy_ast_num(struct ast *const num, __attribute__((unused)) void *const p_arg) {
    free(num);
}
static void destroy_ast_sum(struct ast *const num, void *const __attribute__((unused)) p_arg) {
    run_ast_table(num->data.operation.left, p_arg, destroy_ast_table);
    run_ast_table(num->data.operation.right, p_arg, destroy_ast_table);
    free(num);
}
static void destroy_ast_sub(struct ast *const num, void *const __attribute__((unused)) p_arg) {
    run_ast_table(num->data.operation.left, p_arg, destroy_ast_table);
    run_ast_table(num->data.operation.right, p_arg, destroy_ast_table);
    free(num);
}
static void destroy_ast_mult(struct ast *const num, void *const __attribute__((unused)) p_arg) {
    run_ast_table(num->data.operation.left, p_arg, destroy_ast_table);
    run_ast_table(num->data.operation.right, p_arg, destroy_ast_table);
    free(num);
}
static void destroy_ast_div(struct ast *const num, void *const __attribute__((unused)) p_arg) {
    run_ast_table(num->data.operation.left, p_arg, destroy_ast_table);
    run_ast_table(num->data.operation.right, p_arg, destroy_ast_table);
    free(num);
}


const ast_func eval_ast_table[ast_last] = {
    eval_ast_num, eval_ast_sum, eval_ast_sub, eval_ast_mult, eval_ast_div/*, 0*/
};

const ast_func print_par_ast_table[ast_last] = {
    print_par_ast_num, print_par_ast_sum, print_par_ast_sub, print_par_ast_mult, print_par_ast_div/*, 0*/
};
const ast_func print_rpn_ast_table[ast_last] = {
    print_rpn_ast_num, print_rpn_ast_sum, print_rpn_ast_sub, print_rpn_ast_mult, print_rpn_ast_div/*, 0*/
};
const ast_func print_brn_ast_table[ast_last] = {
    print_brn_ast_num, print_brn_ast_sum, print_brn_ast_sub, print_brn_ast_mult, print_brn_ast_div/*, 0*/
};
const ast_func destroy_ast_table[ast_last] = {
    destroy_ast_num, destroy_ast_sum, destroy_ast_sub, destroy_ast_mult, destroy_ast_div/*, 0*/
};
