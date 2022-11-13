//*****************************************************************************
// (part 3)
// purpose: node classes used while building a parse tree for
//              the arithmetic expression
// version: Fall 2022
//  author: Joe Crumpton / Ed Swan
//*****************************************************************************

#include "parse_tree_nodes.h"

bool printDelete = false;   // shall we print deleting the tree?
static int level = 0;

string node_psp(void)
{ // Stands for p-space, but I want the name short
  string str("");
  for (int i = 0; i < level; i++)
    str += "|  ";
  return str;
}

ostream& operator<<(ostream& os, BaseNode& dn) {
    dn.printTo(os);
    return os;
}

void ProgramNode::printTo(ostream& os){
  os << "(program " << endl << *child << endl << "program) ";
}

ProgramNode::~ProgramNode() {
  if (printDelete) cout << "Deleting ProgramNode" << endl;
  delete child;
  child = nullptr;
}

void BlockNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(block " << endl << *child << endl << node_psp() << "block) ";
  level--;
}

BlockNode::~BlockNode() {
  if (printDelete) cout << "Deleting BlockNode" << endl;
  delete child;
  child = nullptr;
}

void CompoundNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(compound_stmt" << endl;
  for (vector<StatementNode*>::iterator ptr = children.begin(); ptr < children.end(); ptr++) {
    os << *(*ptr) << endl;
  }
  os << node_psp() << "compound_stmt)";
  level--;
}

CompoundNode::~CompoundNode() {
  if (printDelete) cout << "Deleting StatementNode:CompoundStmtNode" << endl;
  for (vector<StatementNode*>::iterator ptr = children.begin(); ptr < children.end(); ptr++) {
    delete *ptr;
    *ptr = nullptr;
  }
}

void AssignmentNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(assignment_stmt ( " << ident << " := )" << endl << *child << endl << node_psp() << "assignment_stmt)";
  level--;
}

AssignmentNode::~AssignmentNode() {
  if (printDelete) cout << "Deleting StatementNode:AssignmentStmtNode" << endl;
  delete child;
  child = nullptr;
}

void IfNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(if_stmt " << endl << *expr << endl << node_psp() << "(then " << endl << *then_stmt << endl << node_psp() << "then) " << endl;
  if (else_stmt) os << node_psp() << "(else " << endl << *else_stmt << endl << node_psp() << "else) " << endl;
  os << node_psp() <<  "if_stmt)";
  level--;
}

IfNode::~IfNode() {
  if (printDelete) cout << "Deleting StatementNode:IfStmtNode" << endl;
  delete expr;
  expr = nullptr;
  delete then_stmt;
  then_stmt = nullptr;
  delete else_stmt;
  else_stmt = nullptr;
}

void WhileNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(while_stmt " << endl << *expr << endl << *stmt << endl << node_psp() <<  "while_stmt)";
  level--;
}

WhileNode::~WhileNode() {
  if (printDelete) cout << "Deleting StatementNode:WhileStmtNode" << endl;
  delete expr;
  expr = nullptr;
  delete stmt;
  stmt = nullptr;
}

void ReadNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(read_stmt ( " << ident << " )" << endl << node_psp() <<  "read_stmt)";
  level--;
}

ReadNode::~ReadNode() {
  if (printDelete) cout << "Deleting StatementNode:ReadStmtNode" << endl;
}

void WriteNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(write_stmt ( " << ident << " )" << endl << node_psp() <<  "write_stmt)";
  level--;
}

WriteNode::~WriteNode() {
  if (printDelete) cout << "Deleting StatementNode:WriteStmtNode" << endl;
}

void ExpressionNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(expression " << endl << *children.at(0) << endl; 
  if (children.size() != 1) os << node_psp() << seperator << " " << endl << *children.at(1) << endl;
  os << node_psp() << "expression) ";
  level--;
}

ExpressionNode::~ExpressionNode() {
  if (printDelete) cout << "Deleting ExpressionNode" << endl;
  for (vector<SimpleExpNode*>::iterator ptr = children.begin(); ptr < children.end(); ptr++) {
    delete *ptr;
    *ptr = nullptr;
  }
}

void SimpleExpNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(simple_exp " << endl; 
  for (int i = 0; i < children.size() - 1; i++) {
    os << *(children[i]) << endl;
    os << node_psp() << seperators[i] << " " << endl;
  }
  os << *(children.back()) << endl;
  os << node_psp() << "simple_exp) ";
  level--;
}

SimpleExpNode::~SimpleExpNode() {
  if (printDelete) cout << "Deleting SimpleExpNode" << endl;
  for (vector<TermNode*>::iterator ptr = children.begin(); ptr < children.end(); ptr++) {
    delete *ptr;
    *ptr = nullptr;
  }
}

void TermNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(term " << endl; 
  for (int i = 0; i < children.size() - 1; i++) {
    os << *(children[i]) << endl;
    os << node_psp() << seperators[i] << " " << endl;
  }
  os << *(children.back()) << endl;
  os << node_psp() << "term) ";
  level--;
}

TermNode::~TermNode() {
  if (printDelete) cout << "Deleting TermNode" << endl;
  for (vector<FactorNode*>::iterator ptr = children.begin(); ptr < children.end(); ptr++) {
    delete *ptr;
    *ptr = nullptr;
  }
}

void IntLitNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(factor ( INTLIT: " << value << " ) "<< endl << node_psp() <<  "factor) ";
  level--;
}

IntLitNode::~IntLitNode() {
  if (printDelete) cout << "Deleting FactorNode:IntLitNode" << endl;
}

void FloatLitNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(factor ( FLOATLIT: " << value << " ) "<< endl << node_psp() <<  "factor) ";
  level--;
}

FloatLitNode::~FloatLitNode() {
  if (printDelete) cout << "Deleting FactorNode:FloatLitNode" << endl;
}

void IdentNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(factor ( IDENT: " << value << " ) "<< endl << node_psp() <<  "factor) ";
  level--;
}

IdentNode::~IdentNode() {
  if (printDelete) cout << "Deleting FactorNode:IdNode" << endl;
}

void NestedExpNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(factor ( " << endl << *child << ")" << endl << node_psp() <<  "factor) ";
  level--;
}

NestedExpNode::~NestedExpNode() {
  if (printDelete) cout << "Deleting FactorNode:NestedExprNode" << endl;
  delete child;
  child = nullptr;
}


void NotNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(factor (NOT " << endl << *child << ") " << endl << node_psp() <<  "factor) ";
  level--;
}

NotNode::~NotNode() {
  if (printDelete) cout << "Deleting FactorNode:NotNode" << endl;
  delete child;
  child = nullptr;
}

void MinusNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(factor (- " << endl << *child << ") " << endl << node_psp() << "factor) ";
  level--;
}

MinusNode::~MinusNode() {
  if (printDelete) cout << "Deleting FactorNode:MinusNode" << endl;
  delete child;
  child = nullptr;
}


