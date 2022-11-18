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
class BlockNode;
class CompoundNode;
class StatementNode;
class ExpressionNode;
class SimpleExpNode;
class TermNode;
class FactorNode;

class BaseNode {
public:
  virtual void printTo(ostream &os) = 0;
  virtual ~BaseNode() {}
};

ostream& operator<<(ostream&, BaseNode&);

class ProgramNode : public BaseNode {
public:
  ProgramNode() {}
  ~ProgramNode();

  BlockNode* child;

  void printTo(ostream &os);
  void interpret();
};

class BlockNode : public BaseNode {
public:
  BlockNode() {}
  ~BlockNode();

  CompoundNode* child;

  void printTo(ostream &os);
  void interpret();
};

class StatementNode : public BaseNode {
public:
  virtual void interpret();
};

class AssignmentNode : public StatementNode {
public:
  AssignmentNode() {}
  ~AssignmentNode();

  ExpressionNode* child;
  string ident;

  void printTo(ostream &os);
  void interpret();
};

class CompoundNode : public StatementNode {
public:
  CompoundNode() {}
  ~CompoundNode();

  vector<StatementNode*> children;

  void printTo(ostream &os);
  void interpret();
};

class IfNode : public StatementNode {
public:
  IfNode() {}
  ~IfNode();

  ExpressionNode* expr;
  StatementNode* then_stmt;
  StatementNode* else_stmt = nullptr;

  void printTo(ostream &os);
  void interpret();
};

class WhileNode : public StatementNode {
public:
  WhileNode() {}
  ~WhileNode();

  ExpressionNode* expr;
  StatementNode* stmt;

  void printTo(ostream &os);
  void interpret();
};

class ReadNode : public StatementNode {
public:
  ReadNode() {}
  ~ReadNode();

  string ident;

  void printTo(ostream &os);
  void interpret();
};

class WriteNode : public StatementNode {
public:
  WriteNode() {}
  ~WriteNode();

  string ident;
  int type;

  void printTo(ostream &os);
  void interpret();
};

class ExpressionNode : public BaseNode {
public:
  ExpressionNode() {}
  ~ExpressionNode();

  vector<SimpleExpNode*> children;
  string seperator;

  void printTo(ostream &os);
  float interpret();
};

class SimpleExpNode : public BaseNode {
public:
  SimpleExpNode() {}
  ~SimpleExpNode();

  vector<TermNode*> children;
  vector<string> seperators;

  void printTo(ostream &os);
  float interpret();
};

class TermNode : public BaseNode {
public:
  TermNode() {}
  ~TermNode();

  vector<FactorNode*> children;
  vector<string> seperators;

  void printTo(ostream &os);
  float interpret();
};

class FactorNode : public BaseNode {
public:
  virtual float interpret();
};

class IntLitNode : public FactorNode {
public:
  IntLitNode(int _value) {value = _value;}
  ~IntLitNode();

  int value;

  void printTo(ostream &os);
  float interpret();
};

class FloatLitNode : public FactorNode {
public:
  FloatLitNode(float _value) {value = _value;}
  ~FloatLitNode();

  float value;

  void printTo(ostream &os);
  float interpret();
};

class IdentNode : public FactorNode {
public:
  IdentNode(string _name) {value = _name;}
  ~IdentNode();

  string value;

  void printTo(ostream &os);
  float interpret();
};

class NestedExpNode : public FactorNode {
public:
  NestedExpNode() {}
  ~NestedExpNode();

  ExpressionNode* child;

  void printTo(ostream &os);
  float interpret();
};

class NotNode : public FactorNode {
public:
  NotNode() {}
  ~NotNode();

  FactorNode* child;

  void printTo(ostream &os);
  float interpret();
};

class MinusNode : public FactorNode {
public:
  MinusNode() {}
  ~MinusNode();

  FactorNode* child;

  void printTo(ostream &os);
  float interpret();
};

#endif /* PARSE_TREE_NODES_H */
