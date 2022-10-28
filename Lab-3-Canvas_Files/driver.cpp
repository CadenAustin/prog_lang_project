//*****************************************************************************
// purpose: driver Lab 3
//  author: 
//*****************************************************************************
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "nodes.h"

void nodeExamples(){
  //IntegerNode a(14);
  //cout << a << endl;

  //FloatNode b(99.99);
  //cout << b << endl;

  //StringNode c("testing");
  //cout << c << endl;

  cout << endl;
}

int main( int argc, char* argv[] ) {

  // create and print an example of each of the DataNodes
  nodeExamples();
  cout << endl;
  
  // Create a vector (a resizable list) of pointers to DataNodes
  vector<DataNode*> aVector;

  // Add four data item pointers to the vector: "first", 2, 3.14, "fourth"
  // aVector.push_back(new StringNode("first"));
  

  // Output the size of the vector

  // Output the items pointed to by vector elements using the .at method
  for (int i=0; i < aVector.size(); i = i + 1) {
    cout << *(aVector.at(i)) << endl;
  }
  cout << endl;

  // Add four more data item pointers to the vector: 5, 6.28, "seventh", "eighth"

  // Output the size of the vector

  // Output the items pointed to by vector elements using an iterator

  // Delete the items pointed to by vector elements
  // Do NOT hard code the size of the vector
  // To indicate that the node is deleted, set the item pointer to nullptr


  // Output the size of the vector

  // Clear the vector

  // Output the size of the vector

  return 0;
}

