#ifndef NODE_H
#define NODE_H
#include<string>
using std::string;
#include<iostream>
using std::cout;
using std::endl;
#include"TypeChecker.h"


class Node {
public:
    Node( Node* left = 0, Node* right = 0 );
    virtual ~Node();
    virtual void print();
    virtual bool populateTables( TypeChecker* tc );
    virtual bool tryGetId( string& result );
    virtual bool tryGatherParams( vector<string>& result );
    virtual bool gatherArgs( vector<string>, TypeChecker* tc );
    virtual bool typeCheck( TypeChecker* tc );
    virtual bool checkReturn( string type, TypeChecker* tc );
    virtual bool tryGetType( string& result, TypeChecker* tc );
protected:
    Node* left;
    Node* right;
};

// Primitives

class IdNode : public Node {
public:
    IdNode( string val );
    bool tryGetId( string& result ) override;
    void print() override;
private:
    string val;
};

class NumNode : public Node {
public:
    NumNode( int val );
    bool tryGetType( string& result, TypeChecker* tc ) override;
    void print() override;
private:
    int val;
};

class ProgramNode : public Node {
public:
    ProgramNode( Node* funcdefs = 0, Node* main = 0 );
    bool populateTables( TypeChecker* tc ) override;
    bool typeCheck( TypeChecker* tc );
    void print() override;
};

/////////////////////////////////////////
// Function Definiton
class FuncDefsNode : public Node {
public:
    FuncDefsNode( Node* FuncDef = 0, Node* next = 0 );
    bool populateTables( TypeChecker* tc ) override;
    bool typeCheck( TypeChecker* tc ) override;
    void print() override;
};


class FuncDefNode : public Node {
public:
    FuncDefNode( Node* type = 0, Node* id = 0, 
                 Node* plist = 0, Node* funcs = 0, Node* ret = 0 );
    bool populateTables( TypeChecker* tc ) override;
    bool typeCheck( TypeChecker* tc ) override;
    void print() override; 
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
    bool tryGetId( string& result );
    void print() override;
private:
    string val;
};

/////////////////////////////////////////
// Params
class PlistNode : public Node {
public:
    PlistNode( Node* param = 0, Node* next = 0 );
    bool tryGatherParams( vector<string>& result ) override;
    void print() override;
};

class ParamNode : public Node {
public:
    ParamNode( Node* type = 0, Node* id = 0 );
    bool tryGatherParams( vector<string>& result ) override;
    void print() override;
};

/////////////////////////////////////////
// Args

class AlistNode : public Node {
public:
    AlistNode( Node* arg = 0, Node* next = 0 );
    bool gatherArgs( vector<string> args, TypeChecker* tc ) override;
    void print() override;
};

class ArgNode : public Node {
public:
    ArgNode( Node* expr = 0 );
    void print() override;
};


/////////////////////////////////////////
// FuncCall

class FuncCallsNode : public Node {
public:
    FuncCallsNode( Node* funcCall = 0, Node* next = 0 );
    bool typeCheck( TypeChecker* tc ) override;
    void print() override;
};

class FuncCallNode : public Node {
public:
    FuncCallNode( Node* id = 0, Node* alist = 0 );
    bool typeCheck( TypeChecker* tc ) override;
    bool tryGetType( string& result, TypeChecker* tc ) override;
    void print() override;
};

/////////////////////////////////////////
// Main
class MainNode : public Node {
public:
    MainNode( Node* plist = 0, Node* funccalls = 0 );
    void print() override;
};

/////////////////////////////////////////
// Return
class ReturnNode : public Node {
public:
    ReturnNode( Node* expr = 0 );
    bool checkReturn( string type, TypeChecker* tc ) override;
    void print() override;
};


/////////////////////////////////////////
// Primitive Expression
class PrimitiveExprNode : public Node {
public:
    PrimitiveExprNode( Node* p = 0 );
    bool tryGetType( string& type, TypeChecker* tc ) override;
    void print() override;
};

/////////////////////////////////////////
// Expressions

// Sum/Unary Operators
class MinusNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    MinusNode( Node* l = 0, Node* r = 0 );
};

class SumNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    SumNode( Node* l = 0, Node* r = 0 );
};

// Relation Nodes

class EqNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    EqNode( Node* l = 0, Node* r = 0 );
};

class NeqNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    NeqNode( Node* l = 0, Node* r = 0 );
};

class LeqNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    LeqNode( Node* l = 0, Node* r = 0 );
};

class GeqNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    GeqNode( Node* l = 0, Node* r = 0 );
};

class LessNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    LessNode( Node* l = 0, Node* r = 0 );
};

class GreaterNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    GreaterNode( Node* l = 0, Node* r = 0 );
};

// Product Nodes
class TimesNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    TimesNode( Node* l = 0, Node* r = 0 );
};

class DivNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    DivNode( Node* l = 0, Node* r = 0 );
};

class ModNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    ModNode( Node* l = 0, Node* r = 0 );
};

// Unary Nodes

class UMinusNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    UMinusNode( Node* r = 0 );
};

class UPlusNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    UPlusNode( Node* r = 0 );
};

class ParenNode : public Node {
public:
    bool tryGetType( string& result, TypeChecker* tc ) override;
    ParenNode( Node* l = 0 );
};

#endif