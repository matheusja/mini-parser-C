#include <stdlib.h>
#include "parser.h"

int main() {
	struct lexer *p_lex;
	struct ast *AST;
	FILE *f = fopen("teste.txt", "r");
	create_lexer(&p_lex, f);
	AST = parse(p_lex);
	fclose(f);
	int result;
	f = fopen("teste.txt", "a");
	run_ast_table(AST, f, print_par_ast_table);
	run_ast_table(AST, &result, eval_ast_table);
	fprintf(f, " = %d\n", result);
	run_ast_table(AST, f, print_rpn_ast_table);
	fprintf(f, "\n");
	run_ast_table(AST, f, print_brn_ast_table);
	run_ast_table(AST, NULL, destroy_ast_table);
	fprintf(f, "\n");
	return 0;
}
