%{
    #include<FlexLexer.h>
    #include<vector>
    #include<string>
    using std::vector;
    using std::string;
    extern yyFlexLexer scanner;
    extern vector<Node*> tree;

    #define yylex() scanner.yylex()
%}


%union{ 
    Node* ttype;
}

%token<ttype> NUM ID
%token SEMICOLON DOT COMMA
%token THIS NULLOP READ INT NEW PRINT WHILE RETURN IF VOID CLASS
%right THEN ELSE
%token LPAREN RPAREN LBRACE RBRACE LSBRACE RSBRACE
%left EQ NEQ LEQ GEQ LESS GREATER
%left PLUS MINUS OR
%left TIMES DIV MOD AND
%token EXCL
%precedence UNARYOP

%%