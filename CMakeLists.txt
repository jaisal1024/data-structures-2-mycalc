cmake_minimum_required(VERSION 3.8)
project(data_structures_2_mycalc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        myCalc.cpp
        Token.cpp
        Token.h
        BinaryTree.cpp
        BinaryTree.h
        HelperLibrary.cpp
        HelperLibrary.h
        file1.txt)

set (data_structures_2_mycalc $myCalc.cpp} -i file1.txt)

add_executable(data_structures_2_mycalc ${SOURCE_FILES})