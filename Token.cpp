#include "Token.h"

bool Token::isOpenParen() {
  bool checkOpen = false;
  if (this->type == "paren") { //cast to TokenParen to determine if the previous token is an open paranthesis)
    TokenParen* temp = dynamic_cast<TokenParen*>(this);
    if (temp->isOpen())
      checkOpen = true;
  }
  return checkOpen;
}

bool Token::isUnaryOperator() {
  bool checkOpen = false;
  if (this->type == "oper") { //cast to TokenParen to determine if the previous token is an open paranthesis)
    TokenOper* temp = dynamic_cast<TokenOper*>(this);
    if (temp->isUnary())
      checkOpen = true;
  }
  return checkOpen;
}

TokenEquation::TokenEquation(){
  vector<Token*> tokenInput;
  tokens = tokenInput;
  length = 0;
}
TokenEquation::~TokenEquation() {
  for (vector<Token*>::iterator it = tokens.begin(); it != tokens.end(); it++) {
      delete *it;
  }

  tokens.clear();
  }

// TokenEquation::TokenEquation(vector<Token*> tokenInput, int lengthInput)
//   : tokens(tokenInput), length(lengthInput) {}

bool TokenEquation::tokenize(string expres) {
  bool multicharacter = false;
  int i = 0;
  const char* character = expres.c_str();

  while (i < expres.length()) {
    if (character[i] == ' ') {
      i=i+1; continue;
    } else if (character[i] == '(' ){
      tokens.push_back(new TokenParen(true));
      i++; continue;
    } else if (character[i] == ')') {
      tokens.push_back(new TokenParen(false));
      i++; continue;
    } else if (isalpha(character[i])) {
      int j = 1;
      string identifier = expres.substr(i, j);
      while (j+i < expres.length() && isalpha(character[i+j])) {
        identifier = expres.substr(i, ++j);
      }
      if (identifier == "mod") {
        if (i!=0) {
          tokens.push_back(new TokenOper("mod", false));
          i++; continue;
        } else {
          //throw exception - operator at start of method
          return false;
        }
      }
      tokens.push_back(new TokenVar(identifier));
      i++;
      continue;
    } else if (isdigit(character[i])) {
      int j = 1;
      string digits = expres.substr(i, j);
      while (j+i < expres.length() && isdigit(character[i+j])) {
        digits = expres.substr(i, ++j);
      }
      tokens.push_back(new TokenDig(digits));
      i+=j; continue;
    } else if (i == 0) {
      if ((character[i] == '+' && character[i+1] == '+') || (character [i] == '*' && character[i+1] == '*')) {
        tokens.push_back(new TokenOper(expres.substr(i,2), true));
        i=i+2; continue;
      } else if (character[i] == '-') {
        if (character[i+1] == '-'){
          tokens.push_back(new TokenOper(expres.substr(i,2), true));
          i=i+2; continue;
        }
        tokens.push_back(new TokenOper(expres.substr(i,1), true));
        i++; continue;
      }
      //throw first character exception error
      return false;
    } else if (i < expres.length()-1) {
      bool checkOpen = tokens.at(tokens.size()-1)->isOpenParen();
      if (tokens.at(tokens.size()-1)->getType() == "oper" || (checkOpen)) { //We are only looking for unary operators now
        if ((character[i] == '+' && character[i+1] == '+') || (character [i] == '*' && character[i+1] == '*') || (character [i] == '-' && character[i+1] == '-')) {
          tokens.push_back(new TokenOper(expres.substr(i,2), true));
          i+=2; continue;
        } else if (character[i] == '-') {
          tokens.push_back(new TokenOper(expres.substr(i,1), true));
          i++; continue;
        } else {
          //throw invalid operator in expression
          return false;
        }
      } else if (character[i] == '%' || character[i] == '/') {
        tokens.push_back(new TokenOper(expres.substr(i,1), false));
        i++; continue;
      } else if (character[i] == '*') {
        if (character[i+1] == '*'){
          tokens.push_back(new TokenOper(expres.substr(i,2), true));
          i=i+2; continue;
        }
        tokens.push_back(new TokenOper(expres.substr(i,1), false));
        i++; continue;
      } else if (character[i] == '+') {
        if (character[i+1] == '+'){
          tokens.push_back(new TokenOper(expres.substr(i,2), true));
          i=i+2; continue;
        }
        tokens.push_back(new TokenOper(expres.substr(i,1), false));
        i++; continue;
      } else if (character[i] == '-') {
        if (character[i+1] == '-'){
          tokens.push_back(new TokenOper(expres.substr(i,2), true));
          i=i+2; continue;
        }
        tokens.push_back(new TokenOper(expres.substr(i,1), false));
        i++; continue;
      }
      //throw invalid token at i error
      return false;
    } else {
      //throw generic invalid token in expression
      return false;
  }
}
  return true;

}
void TokenEquation::prefix(){
  vector<Token*> tokensOutput;
  stack<Token*> operationStack;
  for (int i = 0; i < tokens.size(); i++) {
    if (tokens.at(i)->getType == "dig" || tokens.at(i)->getType == "var") {
      operationStack.push_back(tokens.at(i));
    } else if (tokens.at(i)->getType == "oper") {
      while ()
    } else if (tokens.at(i)->getType == "paren") {
      if (tokens.at(i).isOpenParen()) { //open paranthesis
      } else { //closed paranthesis
      }

    } else {

    }
  }

}
const void TokenEquation::print() const {
  string output = "";
  for (int i = 0; i < tokens.size(); i++) {
    cout << "[ " << tokens.at(i)->getValue() << " , " << tokens.at(i)->getType() << " ] ";
  }
  cout << endl;
}
