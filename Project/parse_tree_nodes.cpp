//*****************************************************************************
// (part 3)
// purpose: node classes used while building a parse tree for
//              the arithmetic expression
// version: Fall 2022
//  author: Joe Crumpton / Ed Swan
//*****************************************************************************

#include "parse_tree_nodes.h"

bool printDelete = false;   // shall we print deleting the tree?

ostream& operator<<(ostream& os, BaseNode& dn) {
    dn.printTo(os);
    return os;
}

void ProgramNode::printTo(ostream& os){
  os << "(Program";
}