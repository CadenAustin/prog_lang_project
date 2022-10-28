/********************************************************************* 
  Name: Caden Austin             NetID: CBA169 
  Course: CSE 4714              Assignment: Lab 3
  Programming Environment: Linux/VSCODE
  Purpose of File: Node implimentation file
*********************************************************************/

#include "nodes.h"

// ---------------------------------------------------------------------
// Do NOT change this method
DataNode::~DataNode() {}
// Uses double dispatch to call the overloaded method printTo in the 
// DataNodes: StringNode, IntegerNode, and FloatNode
//
// Do NOT change this method
ostream& operator<<(ostream& os, DataNode& fn) {
	os << "Data: ";
	fn.printTo(os);
	return os;
}

StringNode::StringNode(string set_str) {
	mystring = new string(set_str);
}

StringNode::~StringNode() {
	cout << "Deleting DataNode:StringNode:" << *mystring << endl;
}

void StringNode::printTo(ostream &os) {
	os << "(string: " << *mystring << ") ";
}

IntegerNode::IntegerNode(int set_int) {
	myinteger = set_int;
}

IntegerNode::~IntegerNode() {
	cout << "Deleting DataNode:IntegerNode:" << myinteger << endl;
}

void IntegerNode::printTo(ostream &os) {
	os << "(integer: " << myinteger << ") ";
}

FloatNode::FloatNode(float set_flt) {
	myfloat = set_flt;
}

FloatNode::~FloatNode() {
	cout << "Deleting DataNode:FloatNode:" << myfloat << endl;
}

void FloatNode::printTo(ostream &os) {
	os << "(float: " << myfloat << ") ";
}
