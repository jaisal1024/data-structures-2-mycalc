#include <cstdlib>
#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

#include "BinaryTree.h"


BinaryTree::BinaryTree()			// constructor
    : rootObj(NULL), n(0) { }


bool BinaryTree::construct(TokenEquation & eq) {  //construct tree from postfix expression
  stack<Node*> st;
  for (int i = 0; i < eq.getLength(); i++) {
    ++n;
    if (eq.getToken(i)->getType() == "var" || eq.getToken(i)->getType() == "dig") {  // is an operand
      st.push(new BinaryTree::Node(*eq.getToken(i)));

    } else if (eq.getToken(i)->getType() == "oper") {
        Node* ptr;
        Node node(*eq.getToken(i));
        ptr = &node;
        Node* t1 = st.top(); // Store top
        st.pop();      // Remove top
        Node* t2 = st.top();
        st.pop();

        node.right =t1;
        node.left = t2;
        // delete t1;
        // delete t2;
        st.push(ptr);

    } else
    //throw error
    return false;
  }
  rootObj = st.top();
  st.pop();

  return true;
}
int BinaryTree::size() const			// number of nodes
    { return n; }

bool BinaryTree::empty() const			// is tree empty?
    { return size() == 0; }

BinaryTree::Node* BinaryTree::root() const // get the root
    { return rootObj; }

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
    return pow(v1, v2);
  if (oper == "mod") {
    int v1temp = int(v1);
    int v2temp = int(v2);
    double sol = v2temp%v1temp;
    return sol;
  }
  if (oper == "%"){
    int v1temp = int(v1);
    int v2temp = int(v2);
    double sol = v2temp/v1temp;
    return sol;
  }
  //throw error here
  return 0;
}

double BinaryTree::evaluate(Node* v) {
  double leftVal, rightVal;
  if (size() == 0){
    return 0.000000000;
    //throw empty tree error
  } else if (v->left == NULL && v->right == NULL) { //is a leaf node
    cout << "THE OTHER SIDE" << endl;
    if ((*v).elt.getType() == "dig") { //ensure its a digit
      double temp;
      istringstream((*v).elt.getValue()) >> temp;
      return temp;
    }
  } else {
  if (v->left != NULL)					// traverse left subtree
    leftVal = evaluate(v->left);
  if (v->right != NULL)					// traverse right subtree
    rightVal = evaluate(v->right);
  double val = evaluateOperation(leftVal, rightVal, (*v).elt.getValue());
  return val;
  }
}
