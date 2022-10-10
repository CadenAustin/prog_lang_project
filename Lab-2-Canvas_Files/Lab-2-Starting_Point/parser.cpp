/********************************************************************* 
  Name: Caden Austin             NetID: CBA169 
  Course: CSE 4714              Assignment: Lab 2
  Programming Environment: Linux/VSCODE
  Purpose of File: Contains the parsing function 
*********************************************************************/

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
int tab = 0;

// Production functions
bool firstOf_sentence();
void noun(int version);
bool adjective(int version);
void verb(int version);
string match_token(int token);

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

string match_token(int token) {
  switch (token) {
    case NOUN:
      return "NOUN";
      break;
    case ADJECTIVE:
      return "ADJECTIVE";
      break;
    case VERB:
      return "VERB";
      break;
    case ADVERB:
      return "ADVERB";
      break;
    case ARTICLE:
      return "ARTICLE";
      break;
    case POSSESSIVE:
      return "POSSESSIVE";
      break;
    default:
      return "";
      break;
  }

}
//*****************************************************************************
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
void sentence() 
{
  if( firstOf_sentence() == false )
    throw( "<sentence> did not start with an article or possessive." );

  cout << string(tab, '\t') << "Enter <sentence>" << endl;

  tab++;
  noun(1);

  verb(1);

  noun(2);
  tab--;

  cout << string(tab, '\t') << "Exit <sentence>" << endl;
} 
//*****************************************************************************
bool firstOf_sentence() {
  return nextToken == ARTICLE || nextToken == POSSESSIVE;
}

void noun(int version) {
  if (nextToken != ARTICLE && nextToken != POSSESSIVE) throw("<noun phrase> did not start with an article or possessive.");
  cout << string(tab, '\t') << "Enter <noun phrase> " << version << endl;
  tab++;
  if (adjective(version) == false) {
    throw ("<noun phrase> did not start with an article or possessive.");
  }
  tab--;

  if (nextToken != NOUN) {
    throw("<noun phrase> did not have a noun.");
  }
  output(match_token(nextToken));
  lex();
  cout << string(tab, '\t') << "Exit <noun phrase> " << version << endl;
}

bool adjective(int version) {
  cout << string(tab, '\t') << "Enter <adjective phrase> " << version << endl;
  if (nextToken == ARTICLE || nextToken == POSSESSIVE) {
    output(match_token(nextToken));
    lex();
    if (nextToken != ADJECTIVE) throw ("<adjective phrase> did not have an adjective." );
    output(match_token(nextToken));
    lex();
  } else {
    throw ("<adjective phrase> did not start with an article or possessive.");
  }
  cout << string(tab, '\t') << "Exit <adjective phrase> " << version << endl;
  return true;
}

void verb(int version) {
  cout << string(tab, '\t') << "Enter <verb phrase> " << version << endl;
  if (nextToken == VERB) {
    output(match_token(nextToken));
    lex();
  } else if (nextToken == ADVERB) {
    output(match_token(nextToken));
    lex();
    tab++;
    verb(version+1);
    tab--;
  } else {
    throw ("<verb phrase> did not start with a verb or an adverb.");
  }
  cout << string(tab, '\t') << "Exit <verb phrase> " << version << endl;
}

/*
    TODO: Add functions for the other grammar productions...
*/