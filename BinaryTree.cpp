#include <cstdlib>
#include <iostream>
using namespace std;

#include "BinaryTree.h"

BinaryTree::BinaryTree()			// constructor
    : rootObj(NULL), n(0) { }

bool BinaryTree::construct(TokenEquation & eq) {  //construct tree from postfix expression
  stack<Position> st;
  for (int i = 0; i < eq.getLength(); i++) {
    if (eq.at(i)->getType() == "var" || eq.at(i)->getType() == "dig") {  // is an operand
      st.push(Node(eq.at(i)));

    } else if (eq.at(i)->getType() == "oper") {
        Node(eq.at(i)) n;
        Node t1 = st.top(); // Store top
        st.pop();      // Remove top
        Node t2 = st.top();
        st.pop();

        pos.right =t1;
        pos.left = t2;
        st.push(Node(pos));

    } else
    //throw error
    return false;
  }
  rootObj = &st.top();
  st.pop();
  roo
  return true;
}
int BinaryTree::size() const			// number of nodes
    { return n; }

bool BinaryTree::empty() const			// is tree empty?
    { return size() == 0; }

BinaryTree::Position BinaryTree::root() const // get the root
    { return Position(rootObj); }

void BinaryTree::addRoot(Token* token){ // add root to empty tree
      rootObj = new Node(*token);
      n = 1;
    }
double BinaryTree::evaluateOperation(double v1, double v2, string oper) {
  if (oper == "+")
    return v1+v2;
  if (oper == "-")
    return v1-v2;
  if (oper == "*")
    return v1*v2;
  if (oper == "/")
    return v1/v2;
  if (oper == "^")
    return v1^v2;
  if (oper == "mod")
    return v1%v2;
  if (oper == "%"){
    int v1temp = int(v1);
    int v2temp = int(v2);
    double sol = v2temp/v1temp;
    return sol;
  }
  //throw error here
  return 0;
}

double BinaryTree::evaluatePostOrder(Node* v) const {
  double leftValue, rightValue;
  if (v->left != NULL)					// traverse left subtree
    leftValue = evaluatePostOrder(v->left);
  if (v->right != NULL)					// traverse right subtree
    rightValue =evaluatePostOrder(v->right);
    return
  return evaluateOperation(leftValue, rightValue, (*v).elt.getValue());
}
