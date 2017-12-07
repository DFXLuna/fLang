#include"Node.h"

Node::Node( Node* left, Node* right ){
    this->left = left;
    this->right = right;
}

bool Node::populateTables( TypeChecker* tc ){
    // ERROR
    return false;
}

bool Node::tryGetId( string& result ){
    // ERROR
    return false;
}

bool Node::tryGatherParams( vector<string>& result ){
    // ERROR
    return false;
}

bool Node::gatherArgs( vector<string> args, TypeChecker* tc ){
    //Error
    return false;
}

bool Node::checkReturn( string type, TypeChecker* tc ){
    // ERROR
    return false;
}

bool Node::typeCheck( TypeChecker* tc ){
    // ERROR
    return false;
}

bool Node::tryGetType( string& result, TypeChecker* tc ){
    // ERROR
    return false;
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
bool NumNode::tryGetType( string& result, TypeChecker* tc ){
    result = "int";
    return true;
}

void NumNode::print(){
    cout << "NumNode" << endl;
}

IdNode::IdNode( string val ): Node( 0, 0 ){
    this->val = val;
}

bool IdNode::tryGetId( string& result ){
    result = val;
    return true;
}

void IdNode::print(){
    cout << "IdNode" << endl;
}

/////////////////////////////////////////
// Program Node

ProgramNode::ProgramNode( Node* funcdefs, Node* main ):
Node( funcdefs, main ){}

bool ProgramNode::populateTables( TypeChecker* tc ){
    if( left ){ return left->populateTables( tc ); }
    else{
        return false;
    }
}

bool ProgramNode::typeCheck( TypeChecker* tc ){
    return left->typeCheck( tc ) && right->typeCheck( tc );
}

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

bool FuncDefsNode::populateTables( TypeChecker* tc ){
    if( right ){
        return left->populateTables( tc ) && right->populateTables( tc );
    }
    return left->populateTables( tc );
}

bool FuncDefsNode::typeCheck( TypeChecker* tc ){
    if( right ){ 
        return left->typeCheck( tc ) && right->typeCheck( tc );
    }
    return left->typeCheck( tc );
}

FuncDefNode::FuncDefNode( Node* type, Node* id, Node* plist, 
Node* funcs, Node* ret ): Node( type, id ){
    this->plist = plist;
    this->funcs = funcs;
    this->ret   = ret;
}

bool FuncDefNode::populateTables( TypeChecker* tc ){
    string type;
    string name;
    vector<string> params;
    if( !left->tryGetId( type ) ){
        // ERROR
        return false;
    }
    if( !right->tryGetId( name ) ){
        // ERROR
        return false;
    }
    if( plist && !plist->tryGatherParams( params ) ){
        // ERROR
        return false;
    }
    if( !tc->registerFunction( name, params, type ) ){
        // ERROR
        return false;
    }
    return true;
}

bool FuncDefNode::typeCheck( TypeChecker* tc ){
    bool funcCheck = true;
    bool retCheck = true;
    // Check all function calls
    if( funcs ){
        funcCheck = funcs->typeCheck( tc );
    }
    // Check return type
    string type;
    if( !left->tryGetId( type ) ){
        // ERROR
        return false;
    }
    if( ret ){
        retCheck = ret->checkReturn( type, tc );
    }
    else{
        // ERROR
        return false;
    }
    return retCheck && funcCheck;

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

bool TypeNode::tryGetId( string& result ){
    result = val;
    return true;
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

bool PlistNode::tryGatherParams( vector<string>& result ){
    if( left && left->tryGatherParams( result ) ){  
        if( right ){ return right->tryGatherParams( result ); }
        return true;
    }
    return false;
}

ParamNode::ParamNode( Node* type, Node* id ): Node( type, id ){}

bool ParamNode::tryGatherParams( vector<string>& result ){
    string entry;
    if( !left->tryGetId( entry ) ){
        // ERROR
        return false;
    }
    result.push_back( entry );
    return true;
}

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

bool AlistNode::gatherArgs( vector<string>, TypeChecker* tc ){
    return false;
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

bool FuncCallsNode::typeCheck( TypeChecker* tc ){
    if( right ){
        return left->typeCheck( tc ) && right->typeCheck( tc );
    }
    return left->typeCheck( tc );
}

void FuncCallsNode::print(){
    cout << "FuncCallsNode" << endl;
    left->print();
    if(right){ right->print(); }
}


FuncCallNode::FuncCallNode( Node* id, Node* alist ): Node( id, alist ){}

bool FuncCallNode::typeCheck( TypeChecker* tc ){
    // gather args and then see if a function with this signature exists
    vector<string> args;
    string name;
    if( right && !right->gatherArgs( args, tc ) ){
        // ERROR
        return false;
    }
    if( left->tryGetId( name ) ){
        return tc->exists( name, args );
    }
    // ERROR
    return false;
}

bool FuncCallNode::tryGetType( string& result, TypeChecker* tc ){
   // gather args and then see if a function with this signature exists
    vector<string> args;
    string name;
    if( right && !right->gatherArgs( args, tc ) ){
        // ERROR
        return false;
    }
    if( left->tryGetId( name ) ){
        return tc->tryResolveType( name, args, result );
    }
    // ERROR
    return false; 
}

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

bool ReturnNode::checkReturn( string type, TypeChecker* tc ){
    string retType ;
    if( left->tryGetType( retType, tc ) ){
        // return tc->checkTypes( type, retType );
    }
    // Error
    return false;
}

void ReturnNode::print(){
    cout << "ReturnNode" << endl;
    left->print();
}


/////////////////////////////////////////
// Primitive Expression

PrimitiveExprNode::PrimitiveExprNode( Node* p ): Node( p, 0 ){}

bool PrimitiveExprNode::tryGetType( string& result, TypeChecker* tc ){
    return left->tryGetType( result, tc );
}

void PrimitiveExprNode::print(){
    cout << "PrimitiveExprNode" << endl;
    left->print();
}

/////////////////////////////////////////
// Expression Nodes
// Sum nodes

SumNode::SumNode( Node* l, Node* r ): Node( l, r ){}

bool SumNode::tryGetType( string& result, TypeChecker* tc ){
    // string ltype;
    // string rtype;
    // if( !left->tryGetType( ltype, tc ) || !right->tryGetType( rtype, tc ) ){
    //     // ERROR
    //     return false;
    // }
    // if( ltype != rtype || ltype != "int" ){
    //     // ERROR
    //     return false;
    // }
    result = "int";
    return true;
}

//// 

MinusNode::MinusNode( Node* l, Node* r ): Node( l, r ){}

bool MinusNode::tryGetType( string& result, TypeChecker* tc ){
    // string ltype;
    // string rtype;
    // if( !left->tryGetType( ltype, tc ) || !right->tryGetType( rtype, tc ) ){
    //     // ERROR
    //     return false;
    // }
    // if( ltype != rtype || ltype != "int" ){
    //     // ERROR
    //     return false;
    // }
    result = "int";
    return true;
}

// Relation Nodes
EqNode::EqNode( Node* l, Node* r ): Node( l, r ){}

bool EqNode::tryGetType( string& result, TypeChecker* tc ){
    result = "bool";
    return true;
}

//// 

NeqNode::NeqNode( Node* l, Node* r ): Node( l, r ){}

bool NeqNode::tryGetType( string& result, TypeChecker* tc ){
    result = "bool";
    return true;
}

//// 

LeqNode::LeqNode( Node* l, Node* r ): Node( l, r ){}

bool LeqNode::tryGetType( string& result, TypeChecker* tc ){
    result = "bool";
    return true;
}

//// 

GeqNode::GeqNode( Node* l, Node* r ): Node( l, r ){}

bool GeqNode::tryGetType( string& result, TypeChecker* tc ){
    result = "bool";
    return true;
}

//// 

LessNode::LessNode( Node* l, Node* r ): Node( l, r ){}

bool LessNode::tryGetType( string& result, TypeChecker* tc ){
    result = "bool";
    return true;
}

//

GreaterNode::GreaterNode( Node* l, Node* r ): Node( l, r ){}

bool GreaterNode::tryGetType( string& result, TypeChecker* tc ){
    result = "bool";
    return true;
}

/////////////////////////////////////////
// Product nodes

TimesNode::TimesNode( Node* l, Node* r ): Node( l, r ){}

bool TimesNode::tryGetType( string& result, TypeChecker* tc ){
    result = "int";
    return true;
}

//// 

DivNode::DivNode( Node* l, Node* r ): Node( l, r ){}

bool DivNode::tryGetType( string& result, TypeChecker* tc ){
    result = "int";
    return true;
}

//// 

ModNode::ModNode( Node* l, Node* r ): Node( l, r ){}

bool ModNode::tryGetType( string& result, TypeChecker* tc ){
    result = "int";
    return true;
}


// Unary nodes

UMinusNode::UMinusNode( Node* r ): Node( 0, r ){}

bool UMinusNode::tryGetType( string& result, TypeChecker* tc ){
    result = "int";
    return true;
}

//// 

UPlusNode::UPlusNode( Node* r ): Node( 0, r ){}

bool UPlusNode::tryGetType( string& result, TypeChecker* tc ){
    result = "int";
    return true;
}

////

ParenNode::ParenNode( Node* l ): Node( l, 0 ){}

bool ParenNode::tryGetType( string& result, TypeChecker* tc ){
    return left->tryGetType( result, tc );
}