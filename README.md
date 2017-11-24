# data-structures-2-mycalc
## A calculator for Data Structures CS-105
### Program Implementation:
####Functions:
A. readFile
readFile is used to do a sanity check and read the .txt file lines into a <ListNode> list containing all the neccesary information. It checks that the expression has been properly paranthesized and has an equality sign.

B. parseList
parseList is the second function called. This contains the bulk of the code. It begins by looping through the list. First, it tokenizes the expression string. The tokenize function seperates operators, variables, digits, and paranthesis into a List of Tokens each defined by a subclass of Token respectively. This is one of the main Data Structures implemented. Dynamic casting, virtual functions, and polymorphism are used heavily. After it successfully tokenizes it then removes unary expressions and then turns the expression into postfix form. Next, it replaces all instances of variables by searching for the variables defined in earlier expressions. Lastly, once it is cleared to evaluate, it then constructs and evaluates the expression using a binary tree.

C. printList
This simply prints the list in a pretty format for output using a forloop.


####Data Structures:
#####Token Class:
1. Token - Base Class
2. TokenDig, TokenVar, TokenParen, TokenOper - Derived Classes
3. TokenEquation
#####Binary Tree:
1. Binary Tree
2. Node
Friend classes

####Invokation:
To invoke the file, cd into the proper directory. Then $ make. After file is made, you can invoke the program using ./output -i <pathfile>

####Remaining Bugs:
The program is not fully functional. Currently it suffers from a Segmentation 11 bug which I am working out. There is a memory location being referenced that does not exist. 

Jaisal Friedman - NYU Abu Dhabi
