%{
    #include<FlexLexer.h>
    #include"Node.h"
    #include<vector>
    #include<string>
    using std::vector;
    using std::string;

    void yyerror(const char*){}

    extern yyFlexLexer scanner;
    extern vector<Node*> tree;

    #define yylex() scanner.yylex()
%}


%union{ 
    Node* ttype;
}

%type<ttype> funcdefs funcdef type plist param stmts stmt main funccalls
%type<ttype> funccall alist arg expr
%token<ttype> NUM ID 
%token SEMICOLON DOT COMMA
%token INT RETURN VOID MAIN
%token LPAREN RPAREN LBRACE RBRACE LSBRACE RSBRACE
%left EQ NEQ LEQ GEQ LESS GREATER
%left PLUS MINUS
%left TIMES DIV MOD
%precedence UNARYOP

%%

program: funcdefs main {}
;

funcdefs: funcdef {}
        | funcdef funcdefs {}
;

funcdef: type ID LPAREN plist RPAREN LSBRACE stmts RSBRACE {}
;

plist: param {}
     | param plist {}
;

param: type ID {}
;

type: INT {}
;

stmts: stmt {}
     | stmt stmts {}
;

stmt: expr SEMICOLON {}
;

main: MAIN LPAREN plist RPAREN LSBRACE funccalls RSBRACE {}
;

funccalls: funccall {}
         | funccall funccalls {}
;

funccall: ID LPAREN alist RPAREN SEMICOLON {}
;

alist: arg {}
     | arg alist {}
;

arg: ID {}
;

expr: 
    NUM {
        $$ = $1;
    }
    | ID LPAREN alist RPAREN {
        //$$ = new MethodCallNode($1, $3);
    }
    | expr PLUS expr  {
        //$$ = new SumNode($1, $3);
    }
    | expr MINUS expr {
        //$$ = new MinusNode($1, $3);
    }
    | expr EQ expr {
        //$$ = new EqNode($1, $3);
    }
    | expr NEQ expr {
        //$$ = new NeqNode($1, $3);
    }
    | expr LEQ expr {
        //$$ = new LeqNode($1, $3);
    }
    | expr GEQ expr {
        //$$ = new GeqNode($1, $3);
    }
    | expr LESS expr {
        //$$ = new LessNode($1, $3);
    }
    | expr GREATER expr {
        //$$ = new GreaterNode($1, $3);
    }
    | expr TIMES expr {
        //$$ = new TimesNode($1, $3);
    }
    | expr DIV expr {
        //$$ = new DivNode($1, $3);
    }
    | expr MOD expr {
        //$$ = new ModNode($1, $3);
    }
    | PLUS expr %prec UNARYOP {
        //$$ = new UPlusNode($2);
    }
    | MINUS expr %prec UNARYOP {
        //$$ = new UMinusNode($2);
    }
    | LPAREN expr RPAREN {
        //$$ = new ParenNode($2);
    }
;
