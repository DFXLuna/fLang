#ifndef NODE_H
#define NODE_H
#include<string>
#include<iostream>
using std::cout;
using std::endl;
using std::string;

class Node {
public:
    Node( Node* left = 0, Node* right = 0 );
    virtual ~Node();
    virtual void print();
protected:
    Node* left;
    Node* right;
};

// Primitives

class IdNode : public Node {
public:
    IdNode( string val );
    void print();
private:
    string val;
};

class NumNode : public Node {
public:
    NumNode( int );
    void print();
private:
    int val;
};

class ProgramNode : public Node {
public:
    ProgramNode( Node* funcdefs = 0, Node* main = 0 );
    void print();
};

/////////////////////////////////////////
// Function Definiton
class FuncDefsNode : public Node {
public:
    FuncDefsNode( Node* FuncDef = 0, Node* next = 0 );
    void print();
};


class FuncDefNode : public Node {
public:
    FuncDefNode( Node* type = 0, Node* id = 0, 
                 Node* plist = 0, Node* funcs = 0, Node* ret = 0 );
    void print(); 
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
    void print();
private:
    string val;
};

/////////////////////////////////////////
// Params
class PlistNode : public Node {
public:
    PlistNode( Node* param = 0, Node* next = 0 );
    void print();
};

class ParamNode : public Node {
public:
    ParamNode( Node* type = 0, Node* id = 0 );
    void print();
};

/////////////////////////////////////////
// Args

class AlistNode : public Node {
public:
    AlistNode( Node* arg = 0, Node* next = 0 );
    void print();
};

class ArgNode : public Node {
public:
    ArgNode( Node* expr = 0 );
    void print();
};


/////////////////////////////////////////
// FuncCall

class FuncCallsNode : public Node {
public:
    FuncCallsNode( Node* funcCall = 0, Node* next = 0 );
    void print();
};

class FuncCallNode : public Node {
public:
    FuncCallNode( Node* id = 0, Node* alist = 0 );
    void print();
};

/////////////////////////////////////////
// Main
class MainNode : public Node {
public:
    MainNode( Node* plist = 0, Node* funccalls = 0 );
    void print();
};

/////////////////////////////////////////
// Return
class ReturnNode : public Node {
public:
    ReturnNode( Node* expr = 0 );
    void print();
};


/////////////////////////////////////////
// Primitive Expression
class PrimitiveExprNode : public Node {
public:
    PrimitiveExprNode( Node* p = 0 );
    void print();
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