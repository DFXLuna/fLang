#include"Node.h"
#include<iostream>
#include<FlexLexer.h>
#include"flang.tab.h"
#include"TypeChecker.h"
using std::cout;
using std::endl;

Node* tree;
yyFlexLexer scanner;

int main(){
    TypeChecker tc;
    tree = 0;
    yyparse();
    if( tree != 0 ){
        tree->populateTables( &tc );
        tc.dump();
    }
    return 0;
}