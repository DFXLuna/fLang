# Makefile
# Date: -1 Dec 1440
CXX=g++
CXXFLAGS=-ggdb -Wall
YACC=bison
YFLAGS=--report=state -W -d
LEX=flex++
LEXFLAGS=--warn

.PHONY: clean test

flang: flang.cpp flang.lpp
	${CXX} ${CXXFLAGS} program5.cpp flang_lex.cpp -o flang


flang_lex.cpp: flang.lpp
	${LEX} ${LEXFLAGS} flang.lpp

clean:
	/bin/rm -f flang flang_lex.cpp	

