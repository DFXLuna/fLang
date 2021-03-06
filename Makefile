# Makefile
# Date: -1 Dec 1440
CXX=g++
CXXFLAGS=-ggdb -Wall -std=c++11
YACC=bison
YFLAGS=--report=state -W -d
LEX=flex++
LEXFLAGS=--warn

.PHONY: clean test

flang: flang.cpp flang_lex.cpp flang.tab.h flang.tab.c Node.h Node.cpp TypeChecker.h TypeChecker.cpp
	${CXX} ${CXXFLAGS} flang.cpp flang_lex.cpp flang.tab.c Node.cpp TypeChecker.cpp -o flang


flang_lex.cpp: flang.lpp Node.h
	${LEX} ${LEXFLAGS} flang.lpp

flang.tab.h: flang.y Node.h
	${YACC} ${YFLAGS} flang.y

clean:
	/bin/rm -f flang flang_lex.cpp flang.tab.c flang.tab.h	

