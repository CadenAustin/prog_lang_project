/*********************************************************************
  Name: Caden Austin             NetID: CBA169
  Course: CSE 4714              Assignment: Part 2
  Programming Environment: Linux/VSCODE
  Purpose of File: Contains the Parser for the Code
*********************************************************************/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "parse_tree_nodes.h"

using namespace std;

int nextToken = 0; // hold nextToken returned by lex
bool printParse = false; 

// Which tree level are we currently in?
static int level = 0;

// Feel free to use a different data structure for the symbol table (list of
// variables declared in the program) but you will have to adjust the code in
// main() to print out the symbol table after a successful parse
set<string> symbolTable; // Symbol Table

int lex()
{
  nextToken = yylex();
  if (nextToken == TOK_EOF)
  {
    yytext[0] = 'E';
    yytext[1] = 'O';
    yytext[2] = 'F';
    yytext[3] = 0;
  }
  return nextToken;
}

//*****************************************************************************
// Indent to reveal tree structure
string psp(void)
{ // Stands for p-space, but I want the name short
  string str("");
  for (int i = 0; i < level; i++)
    str += "|  ";
  return str;
}
//*****************************************************************************
// Report what we found
string tok_to_string(int token)
{
  switch (token)
  {
  case TOK_BEGIN:
    return "BEGIN";
    break;
  case TOK_BREAK:
    return "BREAK";
    break;
  case TOK_CONTINUE:
    return "CONTINUE";
    break;
  case TOK_DOWNTO:
    return "DOWNTO";
    break;
  case TOK_ELSE:
    return "ELSE";
    break;
  case TOK_END:
    return "END";
    break;
  case TOK_FOR:
    return "FOR";
    break;
  case TOK_IF:
    return "IF";
    break;
  case TOK_LET:
    return "LET";
    break;
  case TOK_PROGRAM:
    return "PROGRAM";
    break;
  case TOK_READ:
    return "READ";
    break;
  case TOK_THEN:
    return "THEN";
    break;
  case TOK_TO:
    return "TO";
    break;
  case TOK_VAR:
    return "VAR";
    break;
  case TOK_WHILE:
    return "WHILE";
    break;
  case TOK_WRITE:
    return "WRITE";
    break;
  case TOK_INTEGER:
    return "INTEGER";
    break;
  case TOK_REAL:
    return "REAL";
    break;
  case TOK_SEMICOLON:
    return "SEMICOLON";
    break;
  case TOK_COLON:
    return "COLON";
    break;
  case TOK_OPENPAREN:
    return "OPENPAREN";
    break;
  case TOK_CLOSEPAREN:
    return "CLOSEPAREN";
    break;
  case TOK_PLUS:
    return "PLUS";
    break;
  case TOK_MINUS:
    return "MINUS";
    break;
  case TOK_MULTIPLY:
    return "MULTIPLY";
    break;
  case TOK_DIVIDE:
    return "DIVIDE";
    break;
  case TOK_ASSIGN:
    return "ASSIGN";
    break;
  case TOK_EQUALTO:
    return "EQUALTO";
    break;
  case TOK_LESSTHAN:
    return "LESSTHAN";
    break;
  case TOK_GREATERTHAN:
    return "GREATERTHAN";
    break;
  case TOK_NOTEQUALTO:
    return "NOTEQUALTO";
    break;
  case TOK_MOD:
    return "MOD";
    break;
  case TOK_NOT:
    return "NOT";
    break;
  case TOK_OR:
    return "OR";
    break;
  case TOK_AND:
    return "AND";
    break;
  case TOK_IDENT:
    return "IDENTIFIER";
    break;
  case TOK_INTLIT:
    return "INTLIT";
    break;
  case TOK_FLOATLIT:
    return "FLOATLIT";
    break;
  case TOK_STRINGLIT:
    return "STRINGLIT";
    break;
  case TOK_EOF:
    return "EOF";
    break;
  case TOK_UNKNOWN:
    return "UNKNOWN";
    break;
  default:
    throw("Invalid Token Type");
    break;
  }
}

void output(string what)
{
  cout << psp() << "found |" << yytext << "| " << what << endl;
}

void output_type(string what, string type)
{
  cout << psp() << "-- idName: |" << what << "| idType: |" << type << "| --" << endl;
}

void advance_tok(void)
{
  lex();
  output(tok_to_string(nextToken));
}

//*****************************************************************************
// Forward declarations of FIRST_OF functions.  These check whether the current
// token is in the FIRST set of a production rule.
bool first_of_program(void);
bool first_of_block(void);
bool first_of_statement(void);
bool first_of_factor(void);
bool expect_identifier(void);
//*****************************************************************************
// Parses strings in the language generated by the rule:
// <program> → TOK_PROGRAM TOK_IDENT TOK_SEMICOLON <block>
ProgramNode* program()
{
  if (!first_of_program()) // Check for PROGRAM
    throw "3: 'PROGRAM' expected";
  output(tok_to_string(nextToken));

  cout << psp() << "enter <program>" << endl;
  ++level;

  advance_tok();
  if (!expect_identifier())
    throw "2: identifier expected";
  advance_tok();
  if (nextToken != TOK_SEMICOLON)
    throw "14: ';' expected";
  block();

  --level;
  cout << psp() << "exit <program>" << endl;

  ProgramNode* pNode = new ProgramNode();
  return pNode;
}

void block()
{
  lex();
  if (!first_of_block())
    throw "18: error in declaration part OR 17: 'BEGIN' expected";
  output("BLOCK");
  cout << psp() << "enter <block>" << endl;
  ++level;

  if (nextToken == TOK_VAR)
  {
    lex();
    while (nextToken != TOK_BEGIN && nextToken != TOK_EOF)
    {
      identifier_block();
      lex();
    }
  }

  if (nextToken != TOK_BEGIN)
    throw "17: 'BEGIN' expected";
  output(tok_to_string(nextToken));
  compound_stmt();

  --level;
  cout << psp() << "exit <block>" << endl;
}

void compound_stmt()
{
  cout << psp() << "enter <compound_stmt>" << endl;
  ++level;
  lex();

  bool expect_statement = true;

  while (expect_statement)
  {
    if (!first_of_statement())
      throw "900: illegal type of statement";
    statement();
    if (nextToken == TOK_SEMICOLON)
    {
      output(tok_to_string(nextToken));
      lex();
    }
    else
    {
      if (first_of_statement())
        throw "14: ';' expected";
      expect_statement = false;
    }
  }

  if (nextToken != TOK_END)
    throw "13: 'END' expected";

  --level;
  output(tok_to_string(nextToken));
  lex();
  cout << psp() << "exit <compound_stmt>" << endl;
}

void statement()
{
  output("STATEMENT");
  switch (nextToken)
  {
  case TOK_IDENT:
    assignment_stmt();
    break;
  case TOK_BEGIN:
    output(tok_to_string(nextToken));
    compound_stmt();
    break;
  case TOK_IF:
    if_stmt();
    break;
  case TOK_WHILE:
    while_stmt();
    break;
  case TOK_READ:
    read_stmt();
    break;
  case TOK_WRITE:
    write_stmt();
    break;
  default:
    throw "900: illegal type of statement";
  }
}

void assignment_stmt()
{
  cout << psp() << "enter <assignment>" << endl;
  ++level;
  if (symbolTable.find(yytext) == symbolTable.end())
    throw "104: identifier not declared";
  output(tok_to_string(nextToken));
  cout << psp() << yytext << endl;
  advance_tok();
  if (nextToken != TOK_ASSIGN)
    throw "51: ':=' expected";
  lex();
  if (!first_of_factor())
    throw "144: illegal type of expression";
  expression();

  --level;
  cout << psp() << "exit <assignment>" << endl;
}

void if_stmt()
{
  cout << psp() << "enter <if>" << endl;
  ++level;

  lex();
  expression();

  if (nextToken != TOK_THEN)
    throw "52: 'THEN' expected";
  output(tok_to_string(nextToken));
  lex();
  statement();
  if (nextToken == TOK_ELSE)
  {
    --level;
    output(tok_to_string(nextToken));
    cout << psp() << "enter <else>" << endl;
    ++level;

    lex();
    statement();
  }

  --level;
  cout << psp() << "exit <if>" << endl;
}

void while_stmt()
{
  cout << psp() << "enter <while>" << endl;
  ++level;

  lex();
  expression();
  statement();

  --level;
  cout << psp() << "exit <while>" << endl;
}

void read_stmt()
{
  cout << psp() << "enter <read>" << endl;
  ++level;

  advance_tok();
  if (nextToken != TOK_OPENPAREN)
    throw "9: '(' expected";
  lex();
  if (nextToken != TOK_IDENT)
    throw "2: identifier expected";
  if (symbolTable.find(yytext) == symbolTable.end())
    throw "104: identifier not declared";
  output(tok_to_string(nextToken));
  cout << psp() << yytext << endl;
  advance_tok();
  if (nextToken != TOK_CLOSEPAREN)
    throw "4: ')' expected";
  lex();

  --level;
  cout << psp() << "exit <read>" << endl;
}

void write_stmt()
{
  cout << psp() << "enter <write>" << endl;
  ++level;

  advance_tok();
  if (nextToken != TOK_OPENPAREN)
    throw "9: '(' expected";
  lex();
  if (nextToken != TOK_IDENT && nextToken != TOK_STRINGLIT)
    throw "134: illegal type of operand(s)";
  if (nextToken == TOK_IDENT && symbolTable.find(yytext) == symbolTable.end())
    throw "104: identifier not declared";
  output("WRITE");
  cout << psp() << yytext << endl;
  advance_tok();
  if (nextToken != TOK_CLOSEPAREN)
    throw "4: ')' expected";
  lex();

  --level;
  cout << psp() << "exit <write>" << endl;
}

void expression()
{
  output("EXPRESSION");
  cout << psp() << "enter <expression>" << endl;
  ++level;

  simp_expr();
  if (nextToken == TOK_EQUALTO || nextToken == TOK_LESSTHAN || nextToken == TOK_GREATERTHAN || nextToken == TOK_NOTEQUALTO)
  {
    output(tok_to_string(nextToken));
    cout << psp() << yytext << endl;
    lex();
    simp_expr();
  }

  --level;
  cout << psp() << "exit <expression>" << endl;
}

void simp_expr()
{
  output("SIMPLE_EXP");
  cout << psp() << "enter <simple_exp>" << endl;
  ++level;

  bool expect_term = true;

  while (expect_term)
  {
    if (!first_of_factor())
      throw "902: illegal type of simple expression";
    term();
    if (nextToken == TOK_PLUS || nextToken == TOK_MINUS || nextToken == TOK_OR)
    {
      output(tok_to_string(nextToken));
      cout << psp() << yytext << endl;
      lex();
    }
    else
    {
      expect_term = false;
    }
  }

  --level;
  cout << psp() << "exit <simple_exp>" << endl;
}

void term()
{
  output("TERM");
  cout << psp() << "enter <term>" << endl;
  ++level;

  bool expect_factor = true;

  while (expect_factor)
  {
    if (!first_of_factor())
      throw "902: illegal type of term";
    factor();
    if (nextToken == TOK_MULTIPLY || nextToken == TOK_DIVIDE || nextToken == TOK_AND)
    {
      output(tok_to_string(nextToken));
      cout << psp() << yytext << endl;
      lex();
    }
    else
    {
      expect_factor = false;
    }
  }

  --level;
  cout << psp() << "exit <term>" << endl;
}

void factor()
{
  output("FACTOR");
  cout << psp() << "enter <factor>" << endl;
  ++level;

  if (nextToken == TOK_OPENPAREN)
  {
    output(tok_to_string(nextToken));
    cout << psp() << yytext << endl;
    lex();
    expression();
    if (nextToken != TOK_CLOSEPAREN)
      throw "4: ')' expected";
    output(tok_to_string(nextToken));
    lex();
  }
  else if (nextToken == TOK_NOT || nextToken == TOK_MINUS)
  {
    output(tok_to_string(nextToken));
    cout << psp() << yytext << endl;
    lex();
    if (!first_of_factor())
      throw "903: illegal type of factor";
    factor();
  }
  else
  {
    output(tok_to_string(nextToken));
    cout << psp() << yytext << endl;
    if (nextToken == TOK_IDENT && symbolTable.find(yytext) == symbolTable.end())
      throw "104: identifier not declared";
    lex();
  }

  --level;
  cout << psp() << "exit <factor>" << endl;
}

void identifier_block()
{
  if (nextToken != TOK_IDENT)
    throw "2: identifier expected";
  string what = yytext;
  output(tok_to_string(nextToken));
  advance_tok();
  if (nextToken != TOK_COLON)
    throw "5: ':' expected";
  lex();
  if (nextToken != TOK_INTEGER && nextToken != TOK_REAL)
    throw "10: error in type";
  output("TYPE");
  string type = yytext;
  advance_tok();
  if (nextToken != TOK_SEMICOLON)
    throw "14: ';' expected";
  output_type(what, type);

  if (symbolTable.find(what) != symbolTable.end())
    throw "101: identifier declared twice";
  symbolTable.insert(what);
  return;
}

bool first_of_program(void)
{
  return nextToken == TOK_PROGRAM;
}

bool first_of_block(void)
{
  return nextToken == TOK_BEGIN || nextToken == TOK_VAR;
}

bool first_of_statement(void)
{
  return nextToken == TOK_IDENT || nextToken == TOK_BEGIN || nextToken == TOK_IF || nextToken == TOK_WHILE || nextToken == TOK_READ || nextToken == TOK_WRITE;
}

bool first_of_factor(void)
{
  return nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || nextToken == TOK_IDENT || nextToken == TOK_OPENPAREN || nextToken == TOK_NOT || nextToken == TOK_MINUS;
}

bool expect_identifier(void)
{
  return nextToken == TOK_IDENT;
}