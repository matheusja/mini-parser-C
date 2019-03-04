#pragma once
#include "lexer.h"
#include "ast.h"

struct ast *parse(struct lexer *p_lex);
