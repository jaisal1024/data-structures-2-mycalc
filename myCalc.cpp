#include <iostream>
#include <fstream>
#include "BinaryTree.h"
#include "HelperLibrary.h"
#include "Token.h"

using namespace std;


struct ListNode { //Define a ListNode structure for the Vector implementation of each input line from txt file
    string var;
    string expres;
    BinaryTree tree;
    double eval;

    ListNode() //Constructor for ListNode
    {
        this->var = "";
        this->expres = "";
        this->tree = BinaryTree();
        this->eval = NULL;
    }
};

void readFile(const char *filePath,
              vector<ListNode> &list) { //readFile Function 1: for basic sanity check and reading text file into program
    //variable declarations
    string input;

    //Define and open input stream
    ifstream textFile(filePath);
    if (textFile.is_open()) {
        while (getline(textFile, input)) { //get each line of the txt file
            ListNode node = ListNode();
            bool equalFound = false;
            int openBrace = 0, closeBrace = 0;
            WhiteSpace::trim(input); //call trim function which rids of white space
            const char *temp = input.substr(input.length() - 1, 1).c_str(); //cast to char array
            if (temp[0] != ';') { //check termination clauses
                cout << "Expression terminated: " << input
                     << " - each infix expression in the input text file must terminate with a semi-colon " << endl;
                continue;
            }
            for (int i = 0; i < input.length(); i++) {
                const char *tempLoop = input.substr(i, 1).c_str();
                if (!equalFound && tempLoop[0] == '=') { //check equal clauses
                    node.var = input.substr(0, i);
                    WhiteSpace::trim(node.var);
                    node.expres = input.substr(i + 1, input.length() - i - 2);
                    WhiteSpace::trim(node.expres);
                    equalFound = true;
                }
                if (equalFound) { //check it's found and continue
                    if (tempLoop[0] == '(')
                        openBrace++;
                    else if (tempLoop[0] == ')')
                        closeBrace++;
                }
            }
            if (openBrace != closeBrace) {
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

void parseList(
        vector<ListNode> &list) { //Function 2: parsing list to tokenize expressions, remove Unary expressions, convert to Postfix, remove variables, construct and evaluate tree
    for (int i = 0; i < list.size(); i++) { //for loop through list
        TokenEquation eq = TokenEquation(); //construct TokenEquation
        if (eq.tokenize(list.at(i).expres)) { //if Tokenize is successful
            cout << "TOKENIZE SUCCESSFUL " << i << endl;
            eq.removeUnary(); //invoke removeUnary
            if (eq.postfix()) {
                eq.print(); //visualize postfix expression
                bool readyForEval = true;
                for (int j = 0; j <
                                eq.getLength(); j++) { //front iteration through list to evaluate each tokenized expression to parse out Variables
                    if (eq.getToken(j)->getType() == "var") {
                        bool lookStill = true;
                        readyForEval = false;
                        for (int z = 0; z < i && lookStill; z++) {
                            if (list.at(z).var ==
                                eq.getToken(j)->getVarValue()) { //Found matching variable & replace variable with digit
                                eq.getToken(j)->setValue(to_string((int) list.at(z).eval));
                                eq.getToken(j)->setType("dig");
                                readyForEval = true;
                                lookStill = false;
                            }
                        }
                    }
                }
                if (readyForEval) { //call construct and evaluate only if readyForEval
                    eq.print();
                    list.at(i).tree.construct(eq);
                    list.at(i).tree.inOrder(list.at(i).tree.root());
                    list.at(i).eval = list.at(i).tree.evaluate(list.at(i).tree.root());
                    cout << "EVALUATION IS : " << list.at(i).eval << endl;


                } else { //print out expression that is not working
                    cerr << "The expression: " << list.at(i).var << " = " << list.at(i).expres
                         << " contains undefined variables" << endl;
                    vector<ListNode>::iterator it = list.begin();
                    list.erase(it + i);
                }
            }
        } else {
            cerr << "there's an error in: " << list.at(i).expres << endl;
            vector<ListNode>::iterator it = list.begin();
            list.erase(it + i);
        }
    }
}

void printList(vector<ListNode> const &list) { //Function 3: printing of list
    cout << "THE EVALUATED EXPRESSIONS ARE: " << endl;
    for (int i = 0; i < list.size(); i++) {
        cout << list.at(i).var << " = " << list.at(i).eval << endl;
    }
}

int main(int argc, char const *argv[]) {
    //* Read Textfile from CLI
    //declare input flags & variable
    int fileIndex = -1;
    const char *filePath;
    vector<ListNode> list;

    //check if you are given the proper number of terminal inputs
    if (argc != 3) {
        cout << "Please invoke the program in the CLI form: mymachine-promt >> ./myCalc -i <inputfile>" << endl;
        return -1;
    }
    //check inputs to get dictionary and length variable indexes in the array argv
    for (int i = 0; i < argc; i++) {
        if (*argv[i] == '-' && *(argv[i] + 1) == 'i')
            fileIndex = i + 1;
    }


    //Read txt file into a Vector of ListNode
    try {
        filePath = argv[fileIndex];
        readFile(filePath, list);

    }
    catch (...) {
        cerr << "An error has occurred in opening the text file, please provide a proper file extension and contents"
             << endl;
        return -1;
    }

    //Parse Vector of ListNode
    try {
        parseList(list);
    }
    catch (...) {
        cerr << "An error has occurred in parsing each expression, please check your expressions" << endl;
        return -1;
    }

    printList(list);


    return EXIT_SUCCESS;
}
