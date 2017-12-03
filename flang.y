%{
    #include<FlexLexer.h>
    #include"Node.h"
    #include<vector>
    #include<string>
    using std::vector;
    using std::string;

    void yyerror(const char*){}

    extern yyFlexLexer scanner;
    extern Node* tree;

    #define yylex() scanner.yylex()
%}


%union{ 
    Node* ttype;
}

%type<ttype> funcdefs funcdef type plist param main funccalls
%type<ttype> funccall alist arg expr program ret primexpr
%token<ttype> NUM ID 
%token SEMICOLON COMMA
%token INT RETURN VOID MAIN
%token LPAREN RPAREN LBRACE RBRACE LSBRACE RSBRACE
%left EQ NEQ LEQ GEQ LESS GREATER
%left PLUS MINUS
%left TIMES DIV MOD
%precedence UNARYOP

%%

program: funcdefs main {
           $$ = 0;
           tree = new ProgramNode( $1, $2 );
       }
;

funcdefs: funcdef {
            $$ = new FuncDefsNode( $1, 0 );
        }
        | funcdef funcdefs {
            $$ = new FuncDefsNode( $1, $2 );
        }
;

funcdef: type ID LPAREN plist RPAREN LSBRACE funccalls ret RSBRACE {
           $$ = new FuncDefNode( $1, $2, $4, $7, $8 );
       }
       |
       type ID LPAREN plist RPAREN LSBRACE funccalls RSBRACE {
           $$ = new FuncDefNode( $1, $2, $4, $7, 0 );
       }
       |
       type ID LPAREN plist RPAREN LSBRACE ret RSBRACE {
           $$ = new FuncDefNode( $1, $2, $4, 0, $7 );
       }
       | type ID LPAREN plist RPAREN LSBRACE RSBRACE {
           $$ = new FuncDefNode( $1, $2, $4, 0, 0 );
       }
;

plist: %empty {
         $$ = 0;
     }
     | param {
         $$ = new PlistNode( $1, 0 );
     }
     | param COMMA plist {
         $$ = new PlistNode( $1, $3 );
     }
;

param: type ID {
         $$ = new ParamNode( $1, $2 );
     }
;

type: INT {
        $$ = new TypeNode( "int" );
    }
    |
    VOID {
        $$ = new TypeNode("void");
    }
;

main: MAIN LPAREN plist RPAREN LSBRACE funccalls RSBRACE {
        $$ = new MainNode( $3, $6 );
    }
    | MAIN LPAREN plist RPAREN LSBRACE RSBRACE {
        $$ = new MainNode( $3, 0 );
    }
;

funccalls:  funccall SEMICOLON {
             $$ = new FuncCallsNode( $1, 0 );
         }
         | funccalls funccall SEMICOLON {
             $$ = new FuncCallsNode( $2, $1 );
         }
;

funccall: ID LPAREN alist RPAREN {
            $$ = new FuncCallNode( $1, $3 );
        }
;

alist: %empty {
         $$ = 0;
     }
     | arg {
         $$ = new AlistNode( $1, 0 );
     }
     | arg COMMA alist {
         $$ = new AlistNode( $1, $3 );
     }
;

arg: expr {
       $1 = new ArgNode( $1 );
   }
;

ret: RETURN SEMICOLON {
       $$ = new ReturnNode( 0 );
   }
   | RETURN expr SEMICOLON {
       $$ = new ReturnNode( $2 );
   }
   | RETURN primexpr SEMICOLON {
       $$ = new ReturnNode( $2 );
   }
;

primexpr: NUM {
            $$ = new PrimitiveExpr( $1 );
        }
;

expr: funccall {
        $$ = $1;
    }
    | expr PLUS expr  {
        $$ = new SumNode( $1, $3 );
    }
    | expr MINUS expr {
        $$ = new MinusNode( $1, $3 );
    }
    | expr EQ expr {
        $$ = new EqNode( $1, $3 );
    }
    | expr NEQ expr {
        $$ = new NeqNode( $1, $3 );
    }
    | expr LEQ expr {
        $$ = new LeqNode( $1, $3 );
    }
    | expr GEQ expr {
        $$ = new GeqNode( $1, $3 );
    }
    | expr LESS expr {
        $$ = new LessNode( $1, $3 );
    }
    | expr GREATER expr {
        $$ = new GreaterNode( $1, $3 );
    }
    | expr TIMES expr {
        $$ = new TimesNode( $1, $3 );
    }
    | expr DIV expr {
        $$ = new DivNode( $1, $3 );
    }
    | expr MOD expr {
        $$ = new ModNode( $1, $3 );
    }
    | PLUS expr %prec UNARYOP {
        $$ = new UPlusNode( $2 );
    }
    | MINUS expr %prec UNARYOP {
        $$ = new UMinusNode( $2 );
    }
    | LPAREN expr RPAREN {
        $$ = new ParenNode( $2 );
    }
;
