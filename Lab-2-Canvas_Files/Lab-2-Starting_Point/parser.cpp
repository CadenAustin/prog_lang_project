//**************************************************************************
 
// Replace with appropriate header comment......

//**************************************************************************

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

extern "C"
{
  extern int   yylex();      // the generated lexical analyzer
  extern char *yytext;       // text of current lexeme
}

int nextToken = 0;

// Production functions
bool firstOf_sentence();

//*****************************************************************************
// Get the next lexeme (word in sentence)
int lex() {
  nextToken = yylex();
  if( nextToken == TOK_EOF ) {
    yytext[0] = 'E'; yytext[1] = 'O'; yytext[2] = 'F'; yytext[3] = 0;   
  }

  printf("Next token: %d, lexeme: |%s|\n", nextToken, yytext);
  return nextToken;
}
//*****************************************************************************
// Report what we found
void output( string what ) {
  cout << "===> Accepted " << what << ": |" << yytext << "| <===" << endl;
}
//*****************************************************************************
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
void sentence() 
{
  if( firstOf_sentence() == false )
    throw( "<sentence> did not start with an article or possessive." );

  cout << "Enter <sentence>" << endl;

  /* TODO: Add code here... */ 

  cout << "Exit <sentence>" << endl;
} 
//*****************************************************************************
bool firstOf_sentence() {
  /* TODO: Finish this method... */
  return true;
}

/*
    TODO: Add functions for the other grammar productions...
*/