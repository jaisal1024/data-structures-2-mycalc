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
int Token::getOperPrecedence() {
  int prec = -1;
  if (this->type == "oper") { //cast to
    TokenOper* temp = dynamic_cast<TokenOper*>(this);
     prec = temp->getPrecedence();
  }
  return prec;
}
string Token::getVarValue() {
  string val;
  if (this->type == "var") { //cast to
    TokenVar* temp = dynamic_cast<TokenVar*>(this);
    val = temp->getVariableValue();
  }
  return val;
}

TokenEquation::TokenEquation(){
  vector<Token*> tokenInput;
  tokens = tokenInput;
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
      tokens.push_back(new TokenParen(true, "("));
      i++; continue;
    } else if (character[i] == ')') {
      tokens.push_back(new TokenParen(false, ")"));
      i++; continue;
    } else if (isalpha(character[i])) {
      int j = 1;
      string identifier = expres.substr(i, j);
      while (j+i < expres.length() && isalpha(character[i+j])) {
        identifier = expres.substr(i, ++j);
      }
      if (identifier == "mod") {
        if (i!=0) {
          tokens.push_back(new TokenOper("mod", false, 2));
          i++; continue;
        } else {
          //throw exception - operator at start of method
          return false;
        }
      }
      tokens.push_back(new TokenVar(identifier));
      i++; continue;
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
        tokens.push_back(new TokenOper(expres.substr(i,2), true, 3));
        i=i+2; continue;
      } else if (character[i] == '-') {
        if (character[i+1] == '-'){
          tokens.push_back(new TokenOper(expres.substr(i,2), true, 3));
          i=i+2; continue;
        }
        tokens.push_back(new TokenOper(expres.substr(i,1), true, 3));
        i++; continue;
      }
      //throw first character exception error
      return false;
    } else if (i < expres.length()-1) {
      bool checkOpen = tokens.at(tokens.size()-1)->isOpenParen();
      if (tokens.at(tokens.size()-1)->getType() == "oper" || (checkOpen)) { //We are only looking for unary operators now
        if ((character[i] == '+' && character[i+1] == '+') || (character [i] == '*' && character[i+1] == '*') || (character [i] == '-' && character[i+1] == '-')) {
          tokens.push_back(new TokenOper(expres.substr(i,2), true, 3));
          i+=2; continue;
        } else if (character[i] == '-') {
          tokens.push_back(new TokenOper(expres.substr(i,1), true, 3));
          i++; continue;
        } else {
          //throw invalid operator in expression
          return false;
        }
      } else if (character[i] == '%' || character[i] == '/') {
        tokens.push_back(new TokenOper(expres.substr(i,1), false, 2));
        i++; continue;
      } else if (character[i] == '*') {
        if (character[i+1] == '*'){
          tokens.push_back(new TokenOper(expres.substr(i,2), true, 3));
          i=i+2; continue;
        }
        tokens.push_back(new TokenOper(expres.substr(i,1), false, 2));
        i++; continue;
      } else if (character[i] == '+') {
        if (character[i+1] == '+'){
          tokens.push_back(new TokenOper(expres.substr(i,2), true, 3));
          i=i+2; continue;
        }
        tokens.push_back(new TokenOper(expres.substr(i,1), false, 1));
        i++; continue;
      } else if (character[i] == '-') {
        if (character[i+1] == '-'){
          tokens.push_back(new TokenOper(expres.substr(i,2), true, 3));
          i=i+2; continue;
        }
        tokens.push_back(new TokenOper(expres.substr(i,1), false, 1));
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

void TokenEquation::removeUnary(){
  vector<Token*>::iterator i;
  i = tokens.begin();
  while (i < tokens.end()) {
    if ((*i)->getType() == "oper") {
      if ((*i)->isUnaryOperator()) {
        if ((*i)->getValue() == "**") {
          if ((*(i+1))->getType() == "paren" && (*(i+1))->isOpenParen()) {
            int j = 1;
            bool found = false;
            while(((i+j) < tokens.end()) && !found) {
              if ((*(i+j))->getType() == "paren" && !(*(i+j))->isOpenParen()) {
                tokens.erase(i);
                tokens.insert(i+j,new TokenDig("2"));
                tokens.insert(i+j,new TokenOper("^", false, 4));
                i++; continue;
              }
              j++;
            }
          } else {
            tokens.erase(i);
            tokens.insert(i,new TokenOper("^", false, 4));
            tokens.insert(i,new TokenDig("2"));
            i+=2; continue;
          }

        } else if ((*i)->getValue() == "++") {
          tokens.erase(i);
          tokens.insert(i,new TokenOper("+", false, 1));
          tokens.insert(i,new TokenDig("1"));
          i+=2; continue;

        } else if ((*i)->getValue() == "--") {
          tokens.erase(i);
          tokens.insert(i,new TokenOper("-", false, 1));
          tokens.insert(i,new TokenDig("1"));
          i+=2; continue;
        } else { //it's a negatation value
          tokens.erase(i);
          tokens.insert(i,new TokenOper("*", false, 2));
          tokens.insert(i,new TokenDig("-1"));
          i+=2; continue;
        }
      } i++; continue;
    } i++; continue;
  }
}
bool TokenEquation::postfix(){
  vector<Token*> tokensOutput;
  stack<Token*> operationStack;
  for (int i = 0; i < tokens.size(); i++) {
    if (tokens.at(i)->getType() == "dig" || tokens.at(i)->getType() == "var") {
      tokensOutput.push_back(tokens.at(i));
      continue;
    } else if (tokens.at(i)->getType() == "oper") {
      while (!operationStack.empty() && !operationStack.top()->isUnaryOperator() && (operationStack.top()->getOperPrecedence() >= tokens.at(i)->getOperPrecedence())) {
          tokensOutput.push_back(operationStack.top());
          operationStack.pop();
      }
      operationStack.push(tokens.at(i));
      continue;
    } else if (tokens.at(i)->getType() == "paren") {
      if (tokens.at(i)->isOpenParen()) { //open paranthesis
        operationStack.push(tokens.at(i));
      } else { //closed paranthesis
        bool found = false;
        while (!operationStack.empty() && !found) {
            if (operationStack.top()->getType()== "paren" && operationStack.top()->isOpenParen()) {
              found = true;
              operationStack.pop();
              break;
            }
            tokensOutput.push_back(operationStack.top());
            operationStack.pop();

        }
        continue;  //else
        //throw mismatch paranthesis exception
        return false;
      }
    } else {
      //throw exception shouldn't exist!! another check...
      return false;
    }
  }
  while (!operationStack.empty()) {
    if (operationStack.top()->getType() == "paren") {
      //throw mismatch paranthesis exception
      return false;
    }
    tokensOutput.push_back(operationStack.top());
    operationStack.pop();
  }
  tokens = tokensOutput;
  return true;

}
const void TokenEquation::print() const {
  string output = "";
  for (int i = 0; i < tokens.size(); i++) {
    cout << "[ " << tokens.at(i)->getValue() << " , " << tokens.at(i)->getType() << " ] ";
  }
  cout << endl;
}
 Token* TokenEquation::getToken(int i) {
  return tokens.at(i);
}
// void TokenEquation::replace(int i, Token* tokenInput) {
//   Token* temp = tokens.at(i);
//   tokens.at(i) = tokenInput;
//   delete temp;
// }
