#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include "Token.h"

using namespace std;

class BinaryTree {
  public:
	struct Node {			// a node of the tree
		Token  elt;					// element value
  		Node*   par;					// parent
		Node*   left;					// left child
		Node*   right;					// right child
		Node(Token token) : elt(token), par(NULL), left(NULL), right(NULL) { };
		};

  public:
    BinaryTree();					// constructor
    int size() const;					// number of nodes
    bool empty() const;					// is tree empty?
    Node* root() const;				// get the root
    void addRoot(Token* token);					// add root to empty tree
    bool construct(TokenEquation & eq);
    bool isEvaluated();
	void inOrder(Node* v);
    double evaluateOperation(double v1, double v2, string val);
    double evaluate(Node* v );	// evaluate function
  private:
    Node* rootObj;					// pointer to the root
    int n;	                // number of nodes
  };

  #endif
