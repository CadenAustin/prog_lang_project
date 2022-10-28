/********************************************************************* 
  Name: Caden Austin             NetID: CBA169 
  Course: CSE 4714              Assignment: Lab 3
  Programming Environment: Linux/VSCODE
  Purpose of File: Node header file
*********************************************************************/


#ifndef NODES_H
#define NODES_H

#include <iostream>
#include <string>

using namespace std;

// Abstract class. Base class for StringNode, IntegerNode, and FloatNode
//
// Do NOT change this class
class DataNode {
public:
    virtual void printTo(ostream &os) = 0; // pure virtual method, makes the class Abstract
    virtual ~DataNode();                   // labeling the destructor as virtual allows 
	                                       // the subclass destructors to be called
};
ostream& operator<<(ostream&, DataNode&);  // print method
// ---------------------------------------------------------------------
class StringNode : public DataNode {
public:
    string* mystring = nullptr;

    // Add constructor, destructor, and printTo methods
    StringNode(string set_str);
    ~StringNode();
    void printTo(ostream &os);
};
// ---------------------------------------------------------------------
class IntegerNode : public DataNode {
public:
    int myinteger = 0;

    // Add constructor, destructor, and printTo methods
    IntegerNode(int set_int);
    ~IntegerNode();
    void printTo(ostream &os);
};
// ---------------------------------------------------------------------
class FloatNode : public DataNode {
public:
    float myfloat = 0.0;

    // Add constructor, destructor, and printTo methods
    FloatNode(float set_flt);
    ~FloatNode();
    void printTo(ostream &os);
};

#endif /* NODES_H */
