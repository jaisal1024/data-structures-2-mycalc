#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "HelperLibrary.h"
#include <stack>

using namespace std;

//enum Type {var, dig, oper, paren};

class Token {
  protected:
    string type;
    string value;
  public:
    Token(string typeInput, string valueInput) {
      type = typeInput;
      value = valueInput;
    }
    virtual ~Token(){};
    const string getValue() const {
      return value;
    }
    const string getType() const {
      return type;
    }
    const void setValue(string valueInput) {
        value = valueInput;
    };
    const void setType(string typeInput) {
      type = typeInput;
    }
    bool isOpenParen();
    bool isUnaryOperator();
    int getOperPrecedence();
    string getVarValue();
  };
  class TokenDig : public Token {
  protected:
    string type;
    string value;
  public:
    TokenDig(string valueInput) : Token("dig", valueInput) {
      type = "dig";
      value = valueInput;
    }
    const virtual string getValue() const {
      return value;
    }
//     const virtual void setValue(string valueInput) {
//      value = valueInput;
//        }
  };
  class TokenVar : public Token {
  protected:
    string type;
    string value;
  public:
    TokenVar(string valueInput) : Token("var", valueInput) {
      type = "var";
      value = valueInput;
    }
    const virtual string getValue() const {
      return value;
    }
    string getVariableValue() {
      return value;
    }
//    const void setValue(string valueInput){
//      value = valueInput;
//        }
  };
  class TokenOper : public Token {
  protected:
    string type;
    string value;
    bool isUnaryOperator;
    int precedence;
  public:
    TokenOper(string valueInput, bool isUnaryInput) : Token("oper", valueInput) {
      type = "oper";
      value = valueInput;
      isUnaryOperator = isUnaryInput;
    }
    TokenOper(string valueInput, bool isUnaryInput, int precedenceInput) : Token("oper", valueInput) {
      type = "oper";
      value = valueInput;
      isUnaryOperator = isUnaryInput;
      precedence = precedenceInput;
    }
    const virtual string getValue() const {
      return value;
    }
    const bool isUnary() const {
      return isUnaryOperator;
    }
    const int getPrecedence() const {
      return precedence;
    }
    // void setPrecedence(int precedenceInput) {
    //   precedence = precedenceInput;
    //     }
    const virtual void setValue(string valueInput) {
      value = valueInput;
        }
  };
  class TokenParen : public Token {
  protected:
    string type;
    string value;
    bool openParen;
  public:
    TokenParen(bool openParenInput, string valueInput) : Token("paren", valueInput ) {
      type = "paren";
      openParen = openParenInput;
      if (openParen)
        value = "(";
      else
        value = ")";
    }
    const bool isOpen() const {
      return openParen;
    }
    const virtual string getValue() const {
      return value;
    }
    const virtual void setValue(string valueInput) {
     value = valueInput;
       }
  };

class TokenEquation {
    private:
      vector<Token*> tokens;
    public:
      TokenEquation();
      ~TokenEquation();
      bool tokenize(string expres);
      bool postfix();
      const void print() const;
      const vector<Token*> getTokenEquation() const{
        return tokens;
      }
      Token* getToken(int i);
      const int getLength() const {
        return tokens.size();
      }
      void removeUnary();
      void replace(int i);
};

#endif
