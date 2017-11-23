output: myCalc.o BinaryTree.o HelperLibrary.o Token.o
	g++ myCalc.o BinaryTree.o HelperLibrary.o Token.o -o output
	./output -i file1.txt

myCalc.o: myCalc.cpp
	g++ -c myCalc.cpp

BinaryTree.o: BinaryTree.cpp BinaryTree.h
	g++ -c BinaryTree.cpp

HelperLibrary.o:  HelperLibrary.cpp HelperLibrary.h
	g++ -c HelperLibrary.cpp

Token.o:  Token.cpp Token.h
	g++ -c Token.cpp

clean:
	rm -f 	myCalc.o \
		BinaryTree.o \
		HelperLibrary.o \
		Token.o \
		output
