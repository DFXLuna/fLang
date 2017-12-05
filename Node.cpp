#include"Node.h"

Node::Node( Node* left, Node* right ){
    this->left = left;
    this->right = right;
}

void Node::print(){
    cout << "Base Node / Expr Node" << endl;
}

Node::~Node(){
    delete left;
    delete right;
}

/////////////////////////////////////////
// Primitives

NumNode::NumNode( int val ): Node( 0, 0 ){
    this->val = val;
}
void NumNode::print(){
    cout << "NumNode" << endl;
}

IdNode::IdNode( string val ): Node( 0, 0 ){
    this->val = val;
}

void IdNode::print(){
    cout << "IdNode" << endl;
}

/////////////////////////////////////////
// Program Node

ProgramNode::ProgramNode( Node* funcdefs, Node* main ):
Node( funcdefs, main ){}

void ProgramNode::print(){
    cout << "ProgramNode" << endl;
    left->print();
    right->print();
}

/////////////////////////////////////////
// Function Definiton

FuncDefsNode::FuncDefsNode( Node* funcdef, Node* next ):
Node( funcdef, next ){}

void FuncDefsNode::print(){
    cout << "FuncDefsNode" << endl;
}


FuncDefNode::FuncDefNode( Node* type, Node* id, Node* plist, 
Node* funcs, Node* ret ): Node( type, id ){
    this->plist = plist;
    this->funcs = funcs;
    this->ret   = ret;
}

void FuncDefNode::print(){
    cout << "FuncDefNode" << endl;
    left->print();
    if(right){ right->print(); }
}

FuncDefNode::~FuncDefNode(){
    delete plist;
    delete funcs;
    delete ret;
}

TypeNode::TypeNode( string val ){
    this->val = val;
}

void TypeNode::print(){
    cout << "TypeNode" << endl;
}

/////////////////////////////////////////
// Params
PlistNode::PlistNode( Node* param, Node* next ): Node( param, next ){}

void PlistNode::print(){
    cout << "PlistNode" << endl;
    left->print();
    if(right){ right->print(); }
}

ParamNode::ParamNode( Node* type, Node* id ): Node( type, id ){}

void ParamNode::print(){
    cout << "ParamNode" << endl;
    left->print();
    right->print();
}


/////////////////////////////////////////
// Arglist
AlistNode::AlistNode( Node* arg, Node* next ): Node( arg, next ){}

void AlistNode::print(){
    cout << "AlistNode" << endl;
    left->print();
    if(right){ right->print(); }
}


ArgNode::ArgNode( Node* expr ): Node( expr, 0 ){}

void ArgNode::print(){
    cout << "ArgNode" << endl;
    left->print();
}


/////////////////////////////////////////
// FuncCall

FuncCallsNode::FuncCallsNode( Node* funcCall, Node* next ):
Node( funcCall, next ){}

void FuncCallsNode::print(){
    cout << "FuncCallsNode" << endl;
    left->print();
    if(right){ right->print(); }
}


FuncCallNode::FuncCallNode( Node* id, Node* alist ): Node( id, alist ){}

void FuncCallNode::print(){
    cout << "FuncCallNode" << endl;
    left->print();
    if(right){ right->print(); }
}


/////////////////////////////////////////
// Main

MainNode::MainNode( Node* plist, Node* funccalls ): Node( plist, funccalls ){}

void MainNode::print(){
    cout << "MainNode" << endl;
    if(left) { left->print(); }
    if(right){ right->print(); }
}


/////////////////////////////////////////
// Return

ReturnNode::ReturnNode( Node* expr ): Node( expr, 0 ){}

void ReturnNode::print(){
    cout << "ReturnNode" << endl;
    left->print();
}


/////////////////////////////////////////
// Primitive Expression

PrimitiveExprNode::PrimitiveExprNode( Node* p ): Node( p, 0 ){}

void PrimitiveExprNode::print(){
    cout << "PrimitiveExprNode" << endl;
    left->print();
}

/////////////////////////////////////////
// Expression Nodes
// Sum nodes

SumNode::SumNode( Node* l, Node* r ): Node( l, r ){}

//// 

MinusNode::MinusNode( Node* l, Node* r ): Node( l, r ){}

// Relation Nodes
EqNode::EqNode( Node* l, Node* r ): Node( l, r ){}

//// 

NeqNode::NeqNode( Node* l, Node* r ): Node( l, r ){}

//// 

LeqNode::LeqNode( Node* l, Node* r ): Node( l, r ){}

//// 

GeqNode::GeqNode( Node* l, Node* r ): Node( l, r ){}

//// 

LessNode::LessNode( Node* l, Node* r ): Node( l, r ){}

//

GreaterNode::GreaterNode( Node* l, Node* r ): Node( l, r ){}

/////////////////////////////////////////
// Product nodes

TimesNode::TimesNode( Node* l, Node* r ): Node( l, r ){}

//// 

DivNode::DivNode( Node* l, Node* r ): Node( l, r ){}

//// 

ModNode::ModNode( Node* l, Node* r ): Node( l, r ){}

// Unary nodes

UMinusNode::UMinusNode( Node* r ): Node( 0, r ){}

//// 

UPlusNode::UPlusNode( Node* r ): Node( 0, r ){}

////

ParenNode::ParenNode( Node* l ): Node( l, 0 ){}