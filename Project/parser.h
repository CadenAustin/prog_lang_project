/********************************************************************* 
  Name: Caden Austin             NetID: CBA169 
  Course: CSE 4714              Assignment: Part 2 
  Programming Environment: Linux/VSCODE
  Purpose of File: Contains the Parser Header File
*********************************************************************/ 

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "parse_tree_nodes.h"
#include <set>
#include <iostream>

using namespace std;

// Holds the symbols in the interpreted program
extern set<string> symbolTable;

extern int nextToken;        // next token returned by lexer
extern bool printParse; 

extern "C" {
	// Instantiate global variables used by flex
	extern int   yylex();      // the generated lexical analyzer
	extern char* yytext;       // text of current lexeme
}

// Function declarations
ProgramNode* program();
void block();
void compound_stmt();
void statement();
void assignment_stmt();
void if_stmt();
void while_stmt();
void read_stmt();
void write_stmt();
void expression();
void simp_expr();
void term();
void factor();
void identifier_block();

#endif /* PARSER_H */
