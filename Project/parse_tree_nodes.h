//*****************************************************************************
// (part 3)
// purpose: node classes used while building a parse tree for
//              the arithmetic expression
// version: Spring 2022
//  author: Joe Crumpton / Ed Swan
//*****************************************************************************

#ifndef PARSE_TREE_NODES_H
#define PARSE_TREE_NODES_H

#include <iostream>
#include <vector>
#include <string>
#include "lexer.h"

using namespace std;

extern bool printDelete;      // shall we print deleting the tree?

// ---------------------------------------------------------------------
// Forward declaration of node types
class DefualtNode;

class ProgramNode;

class BaseNode {
public:
  virtual void printTo(ostream &os) = 0; 
};

ostream& operator<<(ostream&, BaseNode&);

class ProgramNode : public BaseNode {
public:
  ProgramNode() {}
  ~ProgramNode() {}

  void printTo(ostream &os);
};

#endif /* PARSE_TREE_NODES_H */
