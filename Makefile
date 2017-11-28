output: myCalc.o BinaryTree.o HelperLibrary.o Token.o
	g++ myCalc.o BinaryTree.o HelperLibrary.o Token.o -o output
	./output -i file2.txt

myCalc.o: myCalc.cpp
	g++ -c myCalc.cpp

Token.o:  Token.cpp Token.h
	g++ -c Token.cpp

BinaryTree.o: BinaryTree.cpp BinaryTree.h
	g++ -c BinaryTree.cpp

HelperLibrary.o:  HelperLibrary.cpp HelperLibrary.h
	g++ -c HelperLibrary.cpp


clean:
	rm -f 	myCalc.o \
		BinaryTree.o \
		HelperLibrary.o \
		Token.o \
		output
