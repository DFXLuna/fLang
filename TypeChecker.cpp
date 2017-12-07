#include"TypeChecker.h"

TypeChecker::TypeChecker(){
    fTable = new FunctionTable();
    tTable = new TypeTable();
    populateTypeTable();
}

TypeChecker::~TypeChecker(){
    delete fTable;
    delete tTable;
}

bool TypeChecker::exists( string name, vector<string> argTypes ) const{
    vector<TypeDecl*> args;
    TypeDecl* temp = 0;
    for( const auto i : argTypes ){
        if( tTable->tryGetType( i, temp ) ){
            args.push_back( temp );
        }
        else{
            return false;
        }
    }
    return fTable->exists( name, args );
}

void TypeChecker::populateTypeTable(){
    registerType("int");
    registerType("void");
    registerType("bool");
}

void TypeChecker::registerType( string name ){
    tTable->registerType( name );
}

bool TypeChecker::tryResolveType( string name, vector<string> argTypes, string& result ){
   vector<TypeDecl*> args;
    TypeDecl* temp = 0;
    for( const auto i : argTypes ){
        if( tTable->tryGetType( i, temp ) ){
            args.push_back( temp );
        }
        else{
            return false;
        }
    }
    return fTable->tryResolveType( name, args, result );
}

bool TypeChecker::registerFunction( string name, vector<string> argTypes, string retType ){
    vector<TypeDecl*> pArgTypes;
    TypeDecl* temp = 0;
    // Create arg type pointers
    for( const auto i : argTypes ){
        if( tTable->tryGetType( i, temp ) ){
            pArgTypes.push_back( temp );
        }
        else{
            return false;
        }
    }
    // create ret type pointer
    if( tTable->tryGetType( retType, temp ) ){
        fTable->registerFunction( name, pArgTypes, temp );
        return true;
    }
    return false;
}

void TypeChecker::dump() const {
    cout << "Type Table" << endl;
    tTable->dump();
    cout << "/////////////////////////////////////////" << endl;
    cout << "Function Table" << endl;
    fTable->dump();
}

/////////////////////////////////////////

void FunctionTable::registerFunction( string name, 
vector<TypeDecl*> argTypes, TypeDecl* retType ){
    auto it = table.begin();
    if( ( it = table.find(name) ) != table.end() ){
        MethDecl entry( name, argTypes, retType );
        it->second.push_back( entry );
    }
    else{
        MethDecl entry( name, argTypes, retType );
        vector<MethDecl> temp;
        temp.push_back( entry );
        table[name] = temp;
    }
}

bool FunctionTable::exists( string name, vector<TypeDecl*> args ) const{
    auto it = table.begin();
    if( ( it = table.find(name) ) != table.end() ){
        for( const auto j : it->second ){
            if( args == j.getArgTypes() ){
                return true;
            }
        }
        return false;
    }
    return false;
}

bool FunctionTable::tryResolveType( string name, vector<TypeDecl*> args, string& result ){
    auto it = table.begin();
    if( ( it = table.find(name) ) != table.end() ){
        for( const auto j : it->second ){
            if( args == j.getArgTypes() ){
                result = j.getRetType()->getName();
                return true;
            }
        }
        return false;
    }
    return false; 
}

void FunctionTable::dump() const {
    for(const auto overloads : table ){
        for( const auto i : overloads.second ){
            i.print();
        }
    }
}

/////////////////////////////////////////
void TypeTable::registerType( string name ){
    TypeDecl entry( name );
    table[name] = entry;
}

bool TypeTable::tryGetType( string name, TypeDecl*& result ){
    auto it = table.begin();
    if( ( it = table.find(name) ) != table.end() ){
        result = &(it->second);
        return true;
    }
    return false;
}

void TypeTable::dump() const {
    for( const auto i : table ){
        i.second.print();
        cout << endl;
    }
}

/////////////////////////////////////////

TypeDecl::TypeDecl(){}

TypeDecl::TypeDecl( string name ){
    this->name = name;
}

string TypeDecl::getName() const {
    return name;
}

void TypeDecl::print() const {
     cout << name;
}


/////////////////////////////////////////

MethDecl::MethDecl(){
    retType = 0;
}

MethDecl::MethDecl( string name, vector<TypeDecl*> argTypes, 
TypeDecl* retType ){
    this->name = name;
    this->argTypes = argTypes;
    this->retType = retType;
}

vector<TypeDecl*> MethDecl::getArgTypes() const {
    return argTypes;
}

TypeDecl* MethDecl::getRetType() const {
    return retType;
}

string MethDecl::getName() const {
    return name;
}

void MethDecl::print() const {
    cout << name << ": ";
    if(argTypes.size() == 0){
        cout << "() -> ";
    }
    else{
        for(unsigned int i = 0; i < argTypes.size(); i++){
            argTypes[i]->print();
            cout << " -> ";
        }
    }
    retType->print();
    cout << endl;
}

bool MethDecl::operator==(const MethDecl& rhs) const{
    if(this->name == rhs.name &&
       this->argTypes == rhs.argTypes &&
       this->retType == rhs.retType){
           return true;
       }
       return false;
}