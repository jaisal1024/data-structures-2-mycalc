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
    if (eq.getToken(i)->getType() == "dig") {  // is an operand
      st.push(new Node(*eq.getToken(i)));
        continue;
    } else if (eq.getToken(i)->getType() == "oper") {
        Node* ptr = new Node(*eq.getToken(i));
        Node* t1 = st.top(); // Store top
        st.pop();      // Remove top
        Node* t2 = st.top();
        st.pop();

        ptr->right =t1;
        ptr->left = t2;
        t1->par = ptr;
        t2->par = ptr;
        st.push(ptr);
        continue;

    } else
    cerr << "This expression is invalid: " << endl;
    return false;
  }
  rootObj = st.top();
    cout << rootObj->elt.getValue() << endl;
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
    cout << v->elt.getValue() << endl;
  double leftVal, rightVal;
   if (v->left == NULL || v->right == NULL) { //is a leaf node
    if ((*v).elt.getType() == "dig") { //ensure its a digit
      double temp;
      istringstream((*v).elt.getValue()) >> temp;
      return temp;
    }
      cerr << "NON-DIG Passed" << endl;
  } else {
  if (v->left != NULL)					// traverse left subtree
    leftVal = evaluate(v->left);
  if (v->right != NULL)					// traverse right subtree
    rightVal = evaluate(v->right);
  return evaluateOperation(leftVal, rightVal, (*v).elt.getValue());
  }
}

void BinaryTree::inOrder(Node* v) {
    if (v->left == NULL || v->right == NULL)  {
        return;
    } else {
        inOrder(v->left);
        cout << (*v).elt.getValue();
        inOrder(v->right);
    }
}
