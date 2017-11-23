#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

//enum Type {var, dig, oper, paren};

class Token {
  protected:
    string type;
  public:
    Token(string typeInput) {
      type = typeInput;
    }
    virtual ~Token(){}
    const virtual string getValue() const {};
    const virtual bool isOpen() const {};
    const virtual bool isUnary() const {};
    const string getType() const {
      return type;
    }
    friend class TokenEquation;
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
    // virtual ~TokenDig(){};
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
  public:
    TokenOper(string valueInput, bool isUnaryInput) : Token("oper") {
      type = "oper";
      value = valueInput;
      isUnaryOperator = isUnaryInput;
    }
    const virtual string getValue() const {
      return value;
    }
    const virtual bool isUnary() const {
      return isUnaryOperator;
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
    const virtual bool isOpen() const {
      return openParen;
    }
    const virtual string getValue() const {
      return value;
    }
  };

class TokenEquation {
    private:
      vector<Token>* tokens;
      int length;
    public:
      TokenEquation();
      bool tokenize(string expres);
      void prefix();
      const void print() const;
      const vector<Token>* getTokenEquation() const{
        return tokens;
      }
      const int getLength() const {
        return length;
      }
};

#endif
