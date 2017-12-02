#ifndef NODE_H
#define NODE_H
#include<string>
using std::string;

class Node {
public:
    virtual ~Node();
    virtual void print();
private:
    Node* left;
    Node* right;
};

class IdNode : public Node {
public:
    IdNode( string v );
private:
    string val;
};

class NumNode : public Node {
public:
    NumNode( int );
private:
    int val;
};

#endif