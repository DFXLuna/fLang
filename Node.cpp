#include"Node.h"

Node::Node( Node* left, Node* right ){
    this->left = left;
    this->right = right;
}

Node::~Node(){
    delete left;
    delete right;
}


NumNode::NumNode( int val ): Node( 0, 0 ){
    this->val = val;
}

IdNode::IdNode( string val ): Node( 0, 0 ){
    this->val = val;
}


MethodCallNode::MethodCallNode( Node* name, Node* arglist ):
Node( name, arglist ){}

////

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