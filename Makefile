###
### Makefile for gerp (CS15 Project 3):
### 	gerp is a program similar to the UNIX commandline function GREP 
### 	for searching files
###
### Authors: Valerie Zhang, Charlotte Versavel
###

CXX      = clang++
CXXFLAGS = -g3 -Ofast -Wall -Wextra -std=c++11 

gerp: main.o gerp.o HashTable.o FileInfo.o FSTree.o DirNode.o \
	stringProcessing.o
	${CXX} ${CXXFLAGS} -o gerp $^

treeTraversal: FSTreeTraversal.o FSTree.o DirNode.o
	${CXX} -o $@ $^

stringProcessing: stringProcessing.o FSTree.o DirNode.o
	${CXX} -o $@ $^

gerp.o: gerp.cpp gerp.h HashTable.h FileInfo.h FSTree.h DirNode.h 
	${CXX} ${CXXFLAGS} -c gerp.cpp

unit_test: unit_test_driver.o FileInfo.o DirNode.o FSTree.o  \
	HashTable.o stringProcessing.o gerp.o
	$(CXX) $(CXXFLAGS) $^

treeTraversal.o: treeTraversal.cpp 
	${CXX} ${CXXFLAGS} treeTraversal.cpp

FileInfo.o: FileInfo.cpp FileInfo.h HashTable.h FSTree.h DirNode.h 
	${CXX} ${CXXFLAGS} -c FileInfo.cpp

HashTable.o: HashTable.cpp HashTable.h FSTree.h DirNode.h stringProcessing.h
	${CXX} ${CXXFLAGS} -c HashTable.cpp

stringProcessing.o: stringProcessing.cpp stringProcessing.h FSTree.h DirNode.h
	${CXX} ${CXXFLAGS} -c stringProcessing.cpp 



# provide commands:
providePhase1:
	provide comp15 proj3_gerp_phase1 FSTreeTraversal.cpp \
	stringProcessing.cpp stringProcessing.h \
	README Makefile unit_tests.h \

provide:
	provide comp15 proj3_gerp FSTreeTraversal.cpp \
	stringProcessing.cpp stringProcessing.h \
	FileInfo.h FileInfo.cpp HashTable.h HashTable.cpp \
	main.cpp gerp.h gerp.cpp \
	README Makefile unit_tests.h \
	output.txt newoutputfile.txt diff_tinydata.txt \
	my_output.txt my_cerr.txt my_cout.txt \
	diff1_input.txt diff2_input.txt diff3_input.txt \
	diff4_input.txt diff5_input.txt 

provideLeaderboard:
	provide comp15 proj3_gerp_leaderboard \
	FSTreeTraversal.cpp stringProcessing.cpp \
	stringProcessing.h \
	FileInfo.h FileInfo.cpp HashTable.h HashTable.cpp \
	Makefile README main.cpp gerp.h gerp.cpp \


