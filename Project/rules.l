/********************************************************************* 
  Name: Caden Austin             NetID: CBA169 
  Course: CSE 4714              Assignment: Part 2 
  Programming Environment: Linux/VSCODE
  Purpose of File: Contains the Rules for Flex 
*********************************************************************/ 
%option yylineno
%option noyywrap
%{
#include "lexer.h"
int line_number = 1;
%}

%%

\n {++line_number;}

BEGIN { return TOK_BEGIN; }
BREAK { return TOK_BREAK; }
CONTINUE { return TOK_CONTINUE; }
DOWNTO { return TOK_DOWNTO; }
ELSE { return TOK_ELSE; }
END { return TOK_END; }
FOR { return TOK_FOR; }
IF { return TOK_IF; }
LET { return TOK_LET; }
PROGRAM { return TOK_PROGRAM; }
READ { return TOK_READ; }
THEN { return TOK_THEN; }
TO { return TOK_TO; }
VAR { return TOK_VAR; }
WHILE { return TOK_WHILE; }
WRITE { return TOK_WRITE; }

INTEGER { return TOK_INTEGER; }
REAL { return TOK_REAL; }

";" { return TOK_SEMICOLON; }
":" { return TOK_COLON; }
"(" { return TOK_OPENPAREN; }
")" { return TOK_CLOSEPAREN; }

"+" { return TOK_PLUS; }
"-" { return TOK_MINUS; }
"*" { return TOK_MULTIPLY; }
"/" { return TOK_DIVIDE; }
":=" { return TOK_ASSIGN; }
"=" { return TOK_EQUALTO; }
"<>" { return TOK_NOTEQUALTO; }
"<" { return TOK_LESSTHAN; }
">" { return TOK_GREATERTHAN; }
MOD { return TOK_MOD; }
NOT { return TOK_NOT; }
OR { return TOK_OR; }
AND { return TOK_AND; }

[A-Z][A-Z0-9]* { if (yyleng < 9) return TOK_IDENT; else return TOK_UNKNOWN; }
[0-9]+"\."+[0-9]+ { return TOK_FLOATLIT; }
[0-9]+ { return TOK_INTLIT; }
\'(\\.|[^'\\\n])*\' { if (yyleng < 81) return TOK_STRINGLIT; else return TOK_UNKNOWN; }

"\{"+.?+"\}" /* comment */
[ \t\r]+             /* nop */

 /* Found an unknown character */

.         { return TOK_UNKNOWN; }

 /* Recognize end of file */

<<EOF>>   { return TOK_EOF; }

