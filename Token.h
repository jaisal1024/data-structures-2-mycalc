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
  public:
    Token(string typeInput) {
      type = typeInput;
    }
    virtual ~Token(){};
    const virtual string getValue() const {return "";};
    const string getType() const {
      return type;
    }
    bool isOpenParen();
    bool isUnaryOperator();
    int getPrecedence();
    void setPrecedence(); 
  };
  class TokenDig : public Token {
  protected:
    string type;
    string value;
  public:
    TokenDig(string valueInput) : Token("dig") {
      type = "dig";
      value = valueInput;
    }
    const virtual string getValue() const {
      return value;
    }
    void setValue(int valueInput) {
      value = valueInput;
        }
  };
  class TokenVar : public Token {
  protected:
    string type;
    string value;
  public:
    TokenVar(string valueInput) : Token("var") {
      type = "var";
      value = valueInput;
    }
    const virtual string getValue() const {
      return value;
    }
    void setValue(string valueInput) {
      value = valueInput;
        }
  };
  class TokenOper : public Token {
  protected:
    string type;
    string value;
    bool isUnaryOperator;
    int precedence;
  public:
    TokenOper(string valueInput, bool isUnaryInput) : Token("oper") {
      type = "oper";
      value = valueInput;
      isUnaryOperator = isUnaryInput;
    }
    TokenOper(string valueInput, bool isUnaryInput, int precedenceInput) : Token("oper") {
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
    void setPrecedence(int precedenceInput) {
      precedence = precedenceInput;
        }
    void setValue(string valueInput) {
      value = valueInput;
        }
  };
  class TokenParen : public Token {
  protected:
    string type;
    string value;
    bool openParen;
  public:
    TokenParen(bool openParenInput) : Token("paren") {
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
  };

class TokenEquation {
    private:
      vector<Token*> tokens;
      int length;
    public:
      TokenEquation();
      ~TokenEquation();
      bool tokenize(string expres);
      void prefix();
      const void print() const;
      const vector<Token*> getTokenEquation() const{
        return tokens;
      }
      const int getLength() const {
        return length;
      }
};

#endif
