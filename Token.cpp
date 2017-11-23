#include "Token.h"


TokenEquation::TokenEquation(){
  vector<Token>* tokenInput;
  tokens = tokenInput;
  length = 0;
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
      tokens->push_back(TokenParen(true));
      i++; continue;
    } else if (character[i] == ')') {
      tokens->push_back(TokenParen(false));
      i++; continue;
    } else if (isalpha(character[i])) {
      int j = 1;
      string identifier = expres.substr(i, j);
      while (j+i < expres.length() && isalpha(character[i+j])) {
        identifier = expres.substr(i, ++j);
      }
      if (identifier == "mod") {
        if (i!=0) {
          tokens->push_back(TokenOper("mod", false));
          i++; continue;
        } else {
          //throw exception - operator at start of method
          return false;
        }
      }
      tokens->push_back(TokenVar(identifier));
      i++;
      continue;
    } else if (isdigit(character[i])) {
      int j = 1;
      string digits = expres.substr(i, j);
      while (j+i < expres.length() && isdigit(character[i+j])) {
        digits = expres.substr(i, ++j);
      }
      tokens->push_back(TokenDig(digits));
      i++; continue;
    } else if (i == 0) {
      if ((character[i] == '+' && character[i+1] == '+') || (character [i] == '*' && character[i+1] == '*')) {
        tokens->push_back(TokenOper(expres.substr(i,2), true));
        i=i+2; continue;
      } else if (character[i] == '-') {
        if (character[i+1] == '-'){
          tokens->push_back(TokenOper(expres.substr(i,2), true));
          i=i+2; continue;
        }
        tokens->push_back(TokenOper(expres.substr(i,1), true));
        i++; continue;
      }
    } else if (i < expres.length()-1) {
      if (tokens->at(tokens->size()-1).getType() == "oper" || (tokens->at(tokens->size()-1).getType() == "paren" && tokens->at(tokens->size()-1).isOpen())) { //We are only looking for unary operators now
        if ((character[i] == '+' && character[i+1] == '+') || (character [i] == '*' && character[i+1] == '*') || (character [i] == '-' && character[i+1] == '-')) {
          tokens->push_back(TokenOper(expres.substr(i,2), true));
          i+=2; continue;
        } else if (character[i] == '-') {
          tokens->push_back(TokenOper(expres.substr(i,1), true));
          i++; continue;
        } else {
          //throw invalid operator in expression
          return false;
        }
      } else if (character[i] == '%' || character[i] == '/') {
        tokens->push_back(TokenOper(expres.substr(i,1), false));
        i++; continue;
      } else if (character[i] == '*') {
        if (character[i+1] == '*'){
          tokens->push_back(TokenOper(expres.substr(i,2), true));
          i=i+2; continue;
        }
        tokens->push_back(TokenOper(expres.substr(i,1), false));
        i++; continue;
      } else if (character[i] == '+') {
        if (character[i+1] == '+'){
          tokens->push_back(TokenOper(expres.substr(i,2), true));
          i=i+2; continue;
        }
        tokens->push_back(TokenOper(expres.substr(i,1), false));
        i++; continue;
      } else if (character[i] == '-') {
        if (character[i+1] == '-'){
          tokens->push_back(TokenOper(expres.substr(i,2), true));
          i=i+2; continue;
        }
        tokens->push_back(TokenOper(expres.substr(i,1), false));
        i++; continue;
      }
    } else {
      //throw generic invalid token in expression
      return false;
  }
}
  cout << tokens->at(0).getValue() << endl;
  return true;

}
void TokenEquation::prefix(){

}
const void TokenEquation::print() const {
  string output = "";
  for (int i = 0; i < tokens->size(); i++) {
    output += tokens->at(i).getValue();
  }
  cout << output << endl;
}
