#include"Node.h"
#include<iostream>
#include<FlexLexer.h>
#include"flang.tab.h"
using namespace std;

Node* tree;
yyFlexLexer scanner;

int main(){
    tree = 0;
    yyparse();
    if( tree != 0 ){
        cout << "Success!" << endl;
        tree->print();
    }
    return 0;
}