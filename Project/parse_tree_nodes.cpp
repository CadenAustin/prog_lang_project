//*****************************************************************************
// (part 3)
// purpose: node classes used while building a parse tree for
//              the arithmfloatetic expression
// version: Fall 2022
//  author: Joe Crumpton / Ed Swan
//*****************************************************************************

#include "parse_tree_nodes.h"
#include "parser.h"

#define EPSILON 0.001 
static bool truth(float F) { 
  return !((EPSILON > F) && (F > -EPSILON)); 
} 

static bool equality(float first, float second) {
  return abs(first - second) <= EPSILON;
}

static bool less_than(float first, float second) {
  return (first - (second + EPSILON)) < -EPSILON;
}

static bool greater_than(float first, float second) {
  return (first - (second - EPSILON)) > EPSILON;
}

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

void ProgramNode::interpret() {
  child->interpret();
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

void BlockNode::interpret() {
  child->interpret();
}

BlockNode::~BlockNode() {
  if (printDelete) cout << "Deleting BlockNode" << endl;
  delete child;
  child = nullptr;
}

void StatementNode::interpret(){
  this->interpret();
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

void CompoundNode::interpret() {
  for (vector<StatementNode*>::iterator ptr = children.begin(); ptr < children.end(); ptr++) {
    (*ptr)->interpret();
  }
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

void AssignmentNode::interpret() {
  symbolTableT::iterator variable = symbolTable.find(ident); 
  float value = child->interpret();
  variable->second = value;
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

void IfNode::interpret() {
  if (truth(expr->interpret())) {
    then_stmt->interpret();
  } else if (else_stmt) {
    else_stmt->interpret();
  }
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

void WhileNode::interpret() {
  while (truth(expr->interpret())) {
    stmt->interpret();
  }
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

void ReadNode::interpret() {
  symbolTableT::iterator variable = symbolTable.find(ident); 
  float value;
  cin >> value;
  variable->second = value;
}

ReadNode::~ReadNode() {
  if (printDelete) cout << "Deleting StatementNode:ReadStmtNode" << endl;
}

void WriteNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(write_stmt ( " << ident << " )" << endl << node_psp() <<  "write_stmt)";
  level--;
}

void WriteNode::interpret() {
  switch (type) {
    case TOK_STRINGLIT:
      cout << ident.substr(1, ident.length()-2) << endl;
      break;
    case TOK_IDENT:
      symbolTableT::iterator variable = symbolTable.find(ident); 
      cout << variable->second << endl; 
      break;
  }
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

float ExpressionNode::interpret() {
  float value = children.at(0)->interpret();
  if (children.size() != 1) {
    float next = children.at(1)->interpret();
    if (seperator == "=") {
      value = (equality(value, next)) ? 1.0f : 0.0f;
    } else if (seperator == "<") {
      value = (less_than(value, next)) ? 1.0f : 0.0f;
    } else if (seperator == ">"){
      value = (greater_than(value, next)) ? 1.0f : 0.0f;
    } else if (seperator == "<>"){
      value = (equality(value, next)) ? 0.0f : 1.0f;
    }
  }
  return value;
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

float SimpleExpNode::interpret() {
  float value = children[0]->interpret();
  for (int i = 1; i < children.size(); i++) {
    float next = (children[i])->interpret();
    string seperator(seperators[i-1]);
    if (seperator == "+") value += next;
    else if (seperator == "-") value -= next;
    else if (seperator == "OR"){
      if (truth(value) || truth(next)) value = 1.0f;
      else value = 0.0f;
    }
  }
  return value;
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

float TermNode::interpret() {
  float value = children[0]->interpret();
  for (int i = 1; i < children.size(); i++) {
    float next = (children[i])->interpret();
    string seperator(seperators[i-1]);
    if (seperator == "*") value *= next;
    else if (seperator == "/") value /= next;
    else if (seperator == "AND"){
      if (truth(value) && truth(next)) value = 1.0f;
      else value = 0.0f;
    }
  }
  return value;
}

TermNode::~TermNode() {
  if (printDelete) cout << "Deleting TermNode" << endl;
  for (vector<FactorNode*>::iterator ptr = children.begin(); ptr < children.end(); ptr++) {
    delete *ptr;
    *ptr = nullptr;
  }
}

float FactorNode::interpret(){
  return this->interpret();
}

void IntLitNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(factor ( INTLIT: " << value << " ) "<< endl << node_psp() <<  "factor) ";
  level--;
}

float IntLitNode::interpret() {
  return value;
}

IntLitNode::~IntLitNode() {
  if (printDelete) cout << "Deleting FactorNode:IntLitNode" << endl;
}

void FloatLitNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(factor ( FLOATLIT: " << value << " ) "<< endl << node_psp() <<  "factor) ";
  level--;
}

float FloatLitNode::interpret() {
  return value;
}

FloatLitNode::~FloatLitNode() {
  if (printDelete) cout << "Deleting FactorNode:FloatLitNode" << endl;
}

void IdentNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(factor ( IDENT: " << value << " ) "<< endl << node_psp() <<  "factor) ";
  level--;
}

float IdentNode::interpret() {
  symbolTableT::iterator variable = symbolTable.find(value); 
  return variable->second; 
}

IdentNode::~IdentNode() {
  if (printDelete) cout << "Deleting FactorNode:IdNode" << endl;
}

void NestedExpNode::printTo(ostream& os){
  level++;
  os << node_psp() << "(factor ( " << endl << *child << ")" << endl << node_psp() <<  "factor) ";
  level--;
}

float NestedExpNode::interpret() {
  return child->interpret();
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

float NotNode::interpret() {
  float value = child->interpret();
  return (truth(value)) ? 0.0f : 1.0f;
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

float MinusNode::interpret() {
  return -1 * child->interpret();
}

MinusNode::~MinusNode() {
  if (printDelete) cout << "Deleting FactorNode:MinusNode" << endl;
  delete child;
  child = nullptr;
}


