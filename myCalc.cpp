#include <iostream>
#include <algorithm>
#include <fstream>
#include "BinaryTree.h"
#include "HelperLibrary.h"
#include "Token.h"

using namespace std;



struct ListNode{ //Define a ListNode structure for the Vector implementation of each input line from txt file
  string var;
  string expres;
  BinaryTree tree;
  string eval;

  ListNode()
  {
  this->var = "";
  this->expres = "";
  this->tree = BinaryTree();
  this->eval = "";
  }
};

void readFile(const char* filePath, vector<ListNode> & list) {
  //variable declerations
  string input;

  //Define and open input stream
  ifstream textFile(filePath);
  if (textFile.is_open())
     {
       while (getline(textFile, input, '\n')) { //get each line of the txt file
          ListNode node = ListNode();
          bool equalFound = false;
          //input.size() << temp << endl;
          int openBrace = 0, closeBrace = 0;
          WhiteSpace::trim(input);
          const char* temp = input.substr(input.length()-1, 1).c_str();
          if (temp[0] != ';') {
            cout << "Expression terminated: " << input << " - each infix expression in the input text file must terminate with a semi-colon " << endl;
            continue;
          }
          for (int i = 0; i < input.length(); i++) {
            const char* tempLoop = input.substr(i, 1).c_str();
            if (!equalFound && tempLoop[0] == '=') {
                node.var = input.substr(0,i);
                WhiteSpace::trim(node.var);
                node.expres = input.substr(i+1, input.length()- i -2);
                WhiteSpace::trim(node.expres);
                equalFound = true;
            }
            if (equalFound) {
                if (tempLoop[0] == '(')
                    openBrace++;
                else if (tempLoop[0] == ')')
                    closeBrace++;
            }
          }
          if (openBrace!= closeBrace) {
              cout << "Expression terminated: " << input << " - must be properly paranthesized" << endl;
              continue;
          }
          if (!equalFound) {
              cout << "Expression terminated: " << input << " - must contain an equals expression" << endl;
              continue;
          }

          list.push_back(node);
       }
    }
    textFile.close();
    cout << "File successfully loaded into program" << endl;
}

void parseList(vector<ListNode> & list) {
  try {
    for (int i= 0; i < list.size(); i++) {
      TokenEquation eq = TokenEquation();
      if (eq.tokenize(list.at(i).expres))
        eq.print();
      else
        cout << "there's an error in: " << list.at(i).expres << endl;
    }
  ;
  }
  catch (...){

  }
}

bool evaluateList(vector<ListNode> & list) {

  return true;
}

void printList(vector<ListNode> const & list) {

}

int main(int argc, char const *argv[]) {
  //* Read Textfile from CLI
  //declare input flags & variable
  int fileIndex = -1;
  int limitIndex = -1;
  const char* filePath;
  vector<ListNode> list;

  //check if you are given the proper number of terminal inputs
  if (argc != 3) {
    cout << "Please invoke the program in the CLI form: mymachine-promt >> ./myCalc -i <inputfile>" << endl;
    return -1;
  }
  //check inputs to get dictionary and length variable indexes in the array argv
  for (int i = 0; i < argc; i++) {
    if (*argv[i] == '-' && *(argv[i]+1)== 'i')
      fileIndex = i+1;
  }


  //Read txt file into a Vector of ListNode
  try {
    filePath = argv[fileIndex];
    readFile(filePath, list);

  }
  catch (...){
    cout << "An error has occurred in opening the text file, please provide a proper file extension and contents" << endl;
    return -1;
  }

  //Parse Vector of ListNode
  try {
     parseList(list);
  }
  catch (...){
    cout << "An error has occurred in parsing each expression, please check your expressions" << endl;
    return -1;
  }


  return EXIT_SUCCESS;
}
