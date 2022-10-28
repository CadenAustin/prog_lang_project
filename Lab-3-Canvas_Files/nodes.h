//*****************************************************************************
// purpose:  
//
//  author: 
//*****************************************************************************

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
};
// ---------------------------------------------------------------------
class IntegerNode : public DataNode {
public:
    int myinteger = 0;

    // Add constructor, destructor, and printTo methods
};
// ---------------------------------------------------------------------
class FloatNode : public DataNode {
public:
    float myfloat = 0.0;

    // Add constructor, destructor, and printTo methods
};

#endif /* NODES_H */
