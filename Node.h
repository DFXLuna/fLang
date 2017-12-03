#ifndef NODE_H
#define NODE_H
#include<string>
using std::string;

class Node {
public:
    Node( Node* left = 0, Node* right = 0 );
    virtual ~Node();
private:
    Node* left;
    Node* right;
};

// Primitives

class IdNode : public Node {
public:
    IdNode( string val );
private:
    string val;
};

class NumNode : public Node {
public:
    NumNode( int );
private:
    int val;
};

class ProgramNode : public Node {
public:
    ProgramNode( Node* funcdefs = 0, Node* main = 0 );
};

/////////////////////////////////////////
// Function Definiton
class FuncDefsNode : public Node {
public:
    FuncDefsNode( Node* FuncDef = 0, Node* next = 0 );
};


class FuncDefNode : public Node {
public:
    FuncDefNode( Node* type = 0, Node* id = 0, 
                 Node* plist = 0, Node* funcs = 0, Node* ret = 0 );
    ~FuncDefNode();
private:
    Node* ret;
    Node* plist;
    Node* funcs;
};

/////////////////////////////////////////
// Type
class TypeNode : public Node {
public:
    TypeNode( string val );
private:
    string val;
};

/////////////////////////////////////////
// Params
class PlistNode : public Node {
public:
    PlistNode( Node* param = 0, Node* next = 0 );
};

class ParamNode : public Node {
public:
    ParamNode( Node* type = 0, Node* id = 0 );
};

/////////////////////////////////////////
// Args

class AlistNode : public Node {
public:
    AlistNode( Node* arg = 0, Node* next = 0 );
};

class ArgNode : public Node {
public:
    ArgNode( Node* expr = 0 );
};


/////////////////////////////////////////
// FuncCall

class FuncCallsNode : public Node {
public:
    FuncCallsNode( Node* funcCall = 0, Node* next = 0 );
};

class FuncCallNode : public Node {
public:
    FuncCallNode( Node* id = 0, Node* alist = 0 );
};

/////////////////////////////////////////
// Main
class MainNode : public Node {
public:
    MainNode( Node* plist = 0, Node* funccalls = 0 );
};

/////////////////////////////////////////
// Return
class ReturnNode : public Node {
public:
    ReturnNode( Node* expr = 0 );
};


/////////////////////////////////////////
// Primitive Expression
class PrimitiveExpr : public Node {
public:
    PrimitiveExpr( Node* p = 0 );
};

/////////////////////////////////////////
// Expressions

// Sum/Unary Operators
class MinusNode : public Node {
public:
    MinusNode( Node* l = 0, Node* r = 0 );
};

class SumNode : public Node {
public:
    SumNode( Node* l = 0, Node* r = 0 );
};

// Relation Nodes

class EqNode : public Node {
public:
    EqNode( Node* l = 0, Node* r = 0 );
};

class NeqNode : public Node {
public:
    NeqNode( Node* l = 0, Node* r = 0 );
};

class LeqNode : public Node {
public:
    LeqNode( Node* l = 0, Node* r = 0 );
};

class GeqNode : public Node {
public:
    GeqNode( Node* l = 0, Node* r = 0 );
};

class LessNode : public Node {
public:
    LessNode( Node* l = 0, Node* r = 0 );
};

class GreaterNode : public Node {
public:
    GreaterNode( Node* l = 0, Node* r = 0 );
};

// Product Nodes
class TimesNode : public Node {
public:
    TimesNode( Node* l = 0, Node* r = 0 );
};

class DivNode : public Node {
public:
    DivNode( Node* l = 0, Node* r = 0 );
};

class ModNode : public Node {
public:
    ModNode( Node* l = 0, Node* r = 0 );
};

// Unary Nodes

class UMinusNode : public Node {
public:
    UMinusNode( Node* r = 0 );
};

class UPlusNode : public Node {
public:
    UPlusNode( Node* r = 0 );
};

class ParenNode : public Node {
public:
    ParenNode( Node* l = 0 );
};

#endif