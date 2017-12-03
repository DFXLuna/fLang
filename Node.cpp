#include"Node.h"

Node::Node( Node* left, Node* right ){
    this->left = left;
    this->right = right;
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

IdNode::IdNode( string val ): Node( 0, 0 ){
    this->val = val;
}

/////////////////////////////////////////
// Program Node

ProgramNode::ProgramNode( Node* funcdefs, Node* main ):
Node( funcdefs, main ){}

/////////////////////////////////////////
// Function Definiton

FuncDefsNode::FuncDefsNode( Node* funcdef, Node* next ):
Node( funcdef, next ){}

FuncDefNode::FuncDefNode( Node* type, Node* id, Node* plist, Node* funcs ):
Node( type, id ){}

FuncDefNode::~FuncDefNode(){
    delete plist;
    delete funcs;
}

TypeNode::TypeNode( string val ){
    this->val = val;
}

/////////////////////////////////////////
// Params
PlistNode::PlistNode( Node* param, Node* next ): Node( param, next ){}

ParamNode::ParamNode( Node* type, Node* id ): Node( type, id ){}

/////////////////////////////////////////
// Arglist
AlistNode::AlistNode( Node* arg, Node* next ): Node( arg, next ){}

ArgNode::ArgNode( Node* expr ): Node( expr, 0 ){}

/////////////////////////////////////////
// FuncCall

FuncCallsNode::FuncCallsNode( Node* funcCall, Node* next ):
Node( funcCall, next ){}

FuncCallNode::FuncCallNode( Node* id, Node* alist ): Node( id, alist ){}

/////////////////////////////////////////
// Main

MainNode::MainNode( Node* plist, Node* funccalls ): Node( plist, funccalls ){}

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