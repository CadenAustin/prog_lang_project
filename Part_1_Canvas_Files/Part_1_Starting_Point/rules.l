/******************************************************************* 
write an appropriate header comment, see the assignment
*******************************************************************/
%option yylineno
%option noyywrap
%{
#include "lexer.h"

%}

%%





 /* Found an unknown character */

.         { return TOK_UNKNOWN; }

 /* Recognize end of file */

<<EOF>>   { return TOK_EOF; }

