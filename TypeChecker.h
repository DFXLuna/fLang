#ifndef TYPECHECKER_H
#define TYPECHECKER_H

#include<map>
using std::map;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<iostream>
using std::cout;
using std::endl;

class FunctionTable;
class TypeTable;
class MethDecl;
class TypeDecl;

class TypeChecker {
public:
    TypeChecker();
    ~TypeChecker();
    // bool contains( string name, vector<string> argTypes, string retType );
    // bool contains( string type );

    bool registerFunction( string name, vector<string> argTypes, string retType );
    void populateTypeTable();

    void dump() const;
private:
    void registerType( string name );
    
    FunctionTable* fTable;
    TypeTable*     tTable;
};

class TypeTable {
public:
    void registerType( string name );
    bool tryGetType( string name, TypeDecl*& result );
    void dump() const;
private:
    map<string, TypeDecl> table;
};

class FunctionTable {
public:
    void registerFunction( string name, vector<TypeDecl*> argTypes,
    TypeDecl* retType );
    void dump() const;
private:
    map< string, vector<MethDecl> > table;
};

class TypeDecl {
public:
    // for map
    TypeDecl();
    TypeDecl( string name );

    string getName() const;
    void print() const;
private:
    string name;
};

class MethDecl {
public:
    // For map
    MethDecl();
    MethDecl( string name, vector<TypeDecl*> argTypes, TypeDecl* retType );
   
    vector<TypeDecl*> getArgTypes() const;
    TypeDecl* getRetType() const;
    string getName() const;
    
    void print() const;
    bool operator==(const MethDecl& rhs) const;
private:
    string name;
    vector<TypeDecl*> argTypes;
    TypeDecl* retType;
};


#endif