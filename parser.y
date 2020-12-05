%{
	//PROLOGOS
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include "symtable.h"
	#include "tcode.h"

	int yyerror(const char* yaccProvidedMessage);
	int yylex(void);

	extern FILE* yyin;
	extern FILE* yyout;
	extern char* yytext;
	extern int yylineno;

	int scope = 0;
	int loop_depth = 0; //elegxei mesa se poses epanaliptikes methodous eimaste
	char *name;	//used for id and func names.
	int in_func = 0; //used to check if i am in a function.
	Type type;
	Node_T node;
	Arg_T arg;

	char anonymous[100];
	int uknownfunc = 0;
	char *fname;

	expr *tmpexpr = NULL;
	int funcQuadNo = 0;

	int whileQuadNo = 0;
	int specialflag = 0; // gia ta break kai continue
	SymTable_T oSymTable;
%}

//TMIMA DILWSEWN

%error-verbose
%start program

%union{
	char* strVal;
	int intVal;
	double doubleVal;
	struct forval *forVal;
	struct stmt_t *stmtVal;
	struct expr *exprVal;
	struct node *symVal; // ST node
	//struct method_t *methodVal; //maybe later
};

%token	<strVal> ID STRING
%token  <intVal> INTEGER TRUE FALSE	
%token	<doubleVal> REAL

%token WHILE FOR IF ELSE FUNCTION RETURN BREAK CONTINUE AND OR NOT NIL PLUS MINUS UMINUS ASSERTION MULT MOD DIV EQUALS DIFF PLUS1 MINUS1 
%token GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS 
COMMA SEMICOLON COLON DOUBLE_COLON DOT DOUBLE_DOT LOCAL

//proteraiotita

%right ASSERTION
%left OR
%left AND
%nonassoc EQUALS DIFF
%nonassoc GREATER_THAN GREATER_OR_EQUAL LESS_THAN LESS_OR_EQUAL
%left PLUS MINUS
%left MULT DIV MOD
%right NOT PLUS1 MINUS1 UMINUS
%left DOT DOUBLE_DOT
%left LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS

%type <exprVal> call lvalue const expr exprs term assignexpr member primary objectdef elist methodcall callsuffix normcall indexed indexedelem index indexedelems
%type <strVal> idlist
%type <symVal> funcdef funprefix funcname
%type <intVal> id ids ifprefix elseprefix whilestart whilecond N M funcbody
%type <stmtVal> stmt stmts ifstmt whilestmt forstmt returnstmt block blstmts
%type <forVal> forprefix
%%

//PERIGRAFI GRAMMATIKIS

program:	stmts	{printf("Start Program\n");}
			;

stmt:		expr SEMICOLON	{
					$$ = newstmt(); //$$ = malloc(sizeof(stmt_t));
					resettemp(); // midenizw ta temporaries
					printf("stmt -> expr;\n\n");
				}
			| ifstmt		{$$ = $1; printf("stmt -> ifstmt\n");}
			| whilestmt		{$$ = $1; printf("stmt -> whilestmt\n");}
			| forstmt		{$$ = $1; printf("stmt -> forstmt\n");}
			| returnstmt	{
				$$ = newstmt();
				printf("stmt -> returnstmt\n");
				if(in_func == 0) {
					printf("\033[0;31m");
					printf("Error: return out of function at line %d\n",yylineno);
					printf("\033[0m");
				}
			}
			| BREAK SEMICOLON	{
				if(loop_depth == 0) {
					printf("\033[0;31m");
					printf("Error: break out of loop at line %d\n",yylineno);
					printf("\033[0m");
				}else{
					specialflag = 1;
					$$ = newstmt();
					$$->next = initList(nextquadlabel());
					$$->next->isbreak = 1;
					emit(jump,NULL,NULL,NULL,0,yylineno);
				}
				printf("stmt -> break;\n\n");
			}
			| CONTINUE SEMICOLON {
					$$ = newstmt();
					if(loop_depth == 0) {
						printf("\033[0;31m");
						printf("Error: continue out of loop at line %d\n",yylineno);
						printf("\033[0m");
					}else{
						$$ = newstmt();
						specialflag = 1;
						$$->next = initList(nextquadlabel());
						$$->next->isbreak = 0;
						emit(jump,NULL,NULL,NULL,0,yylineno);
					}
				printf("stmt -> continue;\n\n");
			}
			| block			{$$ = $1; printf("stmt -> block\n");}
			| funcdef		{$$ = newstmt(); printf("stmt -> funcdef\n");}
			| SEMICOLON 	{$$ = newstmt(); printf("stmt -> ;\n\n");}
			;

stmts:  	stmts stmt 	{
				if($1 && $2 && specialflag){
					$$->next = mergeLists($1->next,$2->next);
					//$$->contlist = mergeLists($1->contlist,$2->contlist,0);
				}else if(!$1) {
					$$ = $2;
				}
				else {
					$$ = $1;
				}
				//specialflag = 0;
				printf("stmts -> stmt stmts\n");
				printf("stmts -> stmt stmts\n");}
			| /*empty*/	{$$ = newstmt(); printf("stmts -> empty \n");}
			;

expr:		assignexpr {
				$$ = $1;
				printf("expr -> assignexpr\n");
			}
			| expr PLUS expr{
				$$ = arith_emit(add,$1,$3,yylineno,scope);
				printf("expr -> expr + expr, %.2lf ADD %.2lf\n",$1->numConst,$3->numConst);	
			}
			| expr MINUS expr{
				$$ = arith_emit(sub,$1,$3,yylineno,scope);
				printf("expr -> expr - expr, %.2lf SUB %.2lf\n",$1->numConst,$3->numConst);				
			}
			| expr MULT expr{
				$$ = arith_emit(mul,$1,$3,yylineno,scope);
				printf("expr -> expr * expr, %.2lf MULT %.2lf\n",$1->numConst,$3->numConst);				
			}
			| expr DIV expr{
				$$ = arith_emit(divide,$1,$3,yylineno,scope);
				printf("expr -> expr / expr, %.2lf DIV %.2lf\n",$1->numConst,$3->numConst);			
			}
			| expr MOD expr{
				$$ = arith_emit(mod,$1,$3,yylineno,scope);
				printf("expr -> expr mod expr, %.2lf MOD %.2lf\n",$1->numConst,$3->numConst);		
			}
			| expr DIFF expr{
				$$ = relop_emit(if_noteq,$1,$3,yylineno,scope);
				printf("expr -> expr != expr, %.2lf != %.2lf\n",$1->numConst,$3->numConst);				
			}
			| expr EQUALS expr{
				$$ = relop_emit(if_eq,$1,$3,yylineno,scope);
				printf("expr -> expr == expr, %.2lf == %.2lf\n",$1->numConst,$3->numConst);			
			}
			| expr GREATER_THAN expr{
				$$ = relop_emit(if_greater,$1,$3,yylineno,scope);
				printf("expr -> expr > expr, %.2lf > %.2lf\n",$1->numConst,$3->numConst);	
			}
			| expr GREATER_OR_EQUAL expr{
				$$ = relop_emit(if_greatereq,$1,$3,yylineno,scope);
				printf("expr -> expr >= expr, %.2lf >= %.2lf\n",$1->numConst,$3->numConst);	
			}
			| expr LESS_THAN expr{
				$$ = relop_emit(if_less,$1,$3,yylineno,scope);
				printf("expr -> expr < expr, %.2lf < %.2lf\n",$1->numConst,$3->numConst);	
			}
			| expr LESS_OR_EQUAL expr{
				$$ = relop_emit(if_lesseq,$1,$3,yylineno,scope);
				printf("expr -> expr <= expr, %.2lf <= %.2lf\n",$1->numConst,$3->numConst);	
			}
			| expr AND expr{
				$$ = boolop_emit(and,$1,$3,yylineno,scope);
				printf("expr -> expr and expr, %u AND %u\n",$1->boolConst,$3->boolConst);	
			}
			| expr OR expr{
				$$ = boolop_emit(or,$1,$3,yylineno,scope);
				printf("expr -> expr or expr, %u OR %u\n",$1->boolConst,$3->boolConst);	
			}
			| term	{
				$$ = $1;
				printf("expr -> term\n");
			}
			;

term:		LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  {
						$$ = $2;
						printf("term -> (expr)\n");
					}
					|MINUS expr %prec UMINUS  {
						arith_typecheck($2);
						$$ = newexpr(arithexpr_e);
						$$->sym = newtemp(yylineno,scope);
						emit(uminus,$2,NULL,$$,0,yylineno);
						printf("term -> -expr\n");
					}
					|NOT expr  {
						$$ = newexpr(boolexpr_e);
						$$->sym = newtemp(yylineno,scope);
						emit(not,$2,NULL,$$,0,yylineno);
						printf("term -> !expr\n");}

					|PLUS1 lvalue {	
						if ( Scope_lookup($2->sym->name, userfunc, scope) || Scope_lookup($2->sym->name, libfunc, scope) ){
							printf("\033[0;31m");
							printf("Error: (line %d) cannot increase value of a function\n", yylineno);
							printf("\033[0m");
						}
						if($2->type == tableitem_e){
							$$ = emit_iftableitem($2,scope,yylineno);
							emit(add,$$,numConst_expr(1),$$,0,yylineno);
							emit(tablesetelem,$2,$2->index,$$,0,yylineno);
						} else {
							emit(add,$2,numConst_expr(1),$2,0,yylineno);
							$$ = newexpr(arithexpr_e);
							$$->sym = newtemp(yylineno,scope);
							emit(assign,$2,NULL,$$,0,yylineno);
						}
						printf("term -> ++lvalue\n");
					}
					|lvalue PLUS1  {
						if ( Scope_lookup($1->sym->name, userfunc, scope) || Scope_lookup($1->sym->name, libfunc, scope) ){
							printf("\033[0;31m");
							printf("Error: (line %d) cannot increase value of a function\n", yylineno);
							printf("\033[0m");
						}
						$$ = newexpr(var_e);
						$$->sym = newtemp(yylineno,scope);
						if($1->type == tableitem_e)  {
							expr *e = emit_iftableitem($1,scope,yylineno);
							emit(assign,e,NULL,$$,0,yylineno);
							emit(add,e,numConst_expr(1),e,0,yylineno);
							emit(tablesetelem,$1,$1->index,e,0,yylineno);
						} else {
							emit(assign,$1,NULL,$$,0,yylineno);
							emit(add,$1,numConst_expr(1),$1,0,yylineno);
						}
						printf("term -> lvalue++\n");
					}
					|MINUS1 lvalue  {
						if ( Scope_lookup($2->sym->name, userfunc, scope) || Scope_lookup($2->sym->name, libfunc, scope) ){
							printf("\033[0;31m");
							printf("Error: (line %d) cannot decrease value of a function\n", yylineno);
							printf("\033[0m");
						}
						if($2->type == tableitem_e){
							$$ = emit_iftableitem($2,scope,yylineno);
							emit(sub,$$,numConst_expr(1),$$,0,yylineno);
							emit(tablesetelem,$2,$2->index,$$,0,yylineno);
						} else {
							emit(sub,$2,numConst_expr(1),$2,0,yylineno);
							$$ = newexpr(arithexpr_e);
							$$->sym = newtemp(yylineno,scope);
							emit(assign,$2,NULL,$$,0,yylineno);
						}
						printf("term -> --lvalue\n");
					}
					|lvalue MINUS1  {
						if ( Scope_lookup($1->sym->name, userfunc, scope) || Scope_lookup($1->sym->name, libfunc, scope) ){
							printf("\033[0;31m");
							printf("Error: (line %d) cannot decrease value of a function\n", yylineno);
							printf("\033[0m");
						}
						$$ = newexpr(var_e);
						$$->sym = newtemp(yylineno,scope);
						if($1->type == tableitem_e)  {
							expr *e = emit_iftableitem($1,scope,yylineno);
							emit(assign,e,NULL,$$,0,yylineno);
							emit(sub,e,numConst_expr(1),e,0,yylineno);
							emit(tablesetelem,$1,$1->index,e,0,yylineno);
						} else {
							emit(assign,$1,NULL,$$,0,yylineno);
							emit(sub,$1,numConst_expr(1),$1,0,yylineno);
						}
						printf("term -> lvalue--\n");
					}
					|primary  {
							$$ = $1;
							printf("term -> primary\n");}
					;

assignexpr:	lvalue {
				if ( Scope_lookup($1->sym->name, userfunc, scope) || Scope_lookup($1->sym->name, libfunc, scope) )
				{
						printf("\033[0;31m");
						printf("Error: (line %d) cannot assign a value to a function\n", yylineno);
						printf("\033[0m");
				}
			}
			ASSERTION expr  {
				printf("assignexpr -> lvalue = expr\n");
				if($1->type == tableitem_e){
					emit(tablesetelem,$$->index,$4,$$,0,yylineno);
					$$ = emit_iftableitem($$,scope,yylineno);				
				}else{	
					$$ = newexpr(assignexpr_e);
					$$->sym = newtemp(yylineno,scope);
					emit(assign,$4,NULL,$1,0,yylineno);
					emit(assign,$1,NULL,$$,0,yylineno);
				}
			}
			;

primary:	lvalue  { 
				$$ = emit_iftableitem($1,scope,yylineno); printf("primary -> lvalue\n");}
			| call  { $$ = $1;
				printf("primary -> call\n");}
			| objectdef  {
				$$ = $1;
				printf("primary -> objectdef\n");
			}
			| LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS  {printf("primary -> (funcdef)\n");
				$$ = newexpr(programfunc_e);
				$$->sym = $2;
				}
			| const   { $$ = $1; printf("primary -> const\n");}
			;

lvalue:		ID  {

				Node_T sym;
				int i;
				/* an h metavliti den yparxei sto symtable se opoiodipote scope */
				sym = SymTable_lookup(oSymTable, $1);
				if(!sym){
					if(scope == 0) type = global;
					else type = local;
					/* tin eisagoume sto trexon scope */
					SymTable_insert(oSymTable, $1, type, yylineno, scope);

					sym = newsymbol(var_s,$1,scope,yylineno);
					sym->space = currscopespace();
					sym->offset = currscopeoffset();
					incurrscopeoffset();

				} else { 
						if(Scope_lookup($1, libfunc, 0)){
							printf("Calling libfunc %s\n", $1);
						}else {					
							for(i=scope; i>=0; i--){
								sym = Scope_lookup($1, unknown, i);

								if(Scope_lookup($1, userfunc, i)){
									printf("Calling userfunc %s\n",$1);
									break;
								}
								/* an vrethei ekxwrhsh sto ST sto idio h ekswterikotero scope*/
								if(sym){
									if(sym->isActive == 1 && sym->scope != 0){
										/* an mesolavei function anamesa sto current scope kai se afto pou vrethike 
												metavliti me to idio onoma */
										if ( FuncBetween(i, scope-1) && sym->scope != 0){ 
											printf("\033[0;31m");
											printf("Error: (line %d) ID %s is not visible\n",yylineno,$1);
											printf("\033[0m");
										}
										break;							
									} else {
										if(sym->scope != 0){
											SymTable_insert(oSymTable, $1, type, yylineno, scope);
											break;
										}
									}
								} else {
									if(i==0){
										SymTable_insert(oSymTable, $1, global, yylineno, scope); // local ??
										break;
									}
								}
							}
						}
				}
				$$ = lvalue_expr(SymTable_lookup(oSymTable, $1));
				printf("lvalue -> ID\n");
			}
			| LOCAL ID  {
					 	Node_T sym;
						sym = Scope_lookup($2,unknown,scope);
						if(!sym){
							if(!Scope_lookup($2,libfunc,0)){
								if(scope == 0) type = global;
								else type = local;
								SymTable_insert(oSymTable,$2,type,yylineno,scope);

								sym = newsymbol(var_s,$2,scope,yylineno);
								sym->space = currscopespace();
								sym->offset = currscopeoffset();
								incurrscopeoffset();
							}else{
								printf("\033[0;31m");
								printf("Error: (line %d) trying to shadow library function %s\n",yylineno,$2);
								printf("\033[0m");
							}
						}else{
							if(Scope_lookup($2,userfunc,scope)){
								printf("Warning: (line %d) Trying to define local ID %s which is a function name\n",yylineno,$2);
							}else{
								$$ = lvalue_expr(sym);
							}
						}
						$$ = lvalue_expr(SymTable_lookup(oSymTable, $2));
						printf("lvalue -> local ID\n");
			}
			| DOUBLE_COLON ID  {
				node = Scope_lookup($2, unknown, 0);
				if(node == NULL){	
					printf("\033[0;31m");
					printf("Error: (line:%d) trying to access (global) ID: %s, which is not defined\n",yylineno,$2);
					printf("\033[0m");
				}
				$$ = lvalue_expr(SymTable_lookup(oSymTable, $2));
				printf("lvalue -> ::ID\n");
			}
			| member  {
				$$ = $1;
				printf("lvalue -> member\n");
			}
			;

member:		lvalue DOT ID  {
				$$ = member_item($1,$3, yylineno,scope);
				printf("member -> lvalue.ID\n");
			}
			| lvalue LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {
				$1 = emit_iftableitem($1,scope,yylineno);
				$$ = newexpr(tableitem_e);
				$$->sym = $1->sym;
				$$->index = $3;
				printf("member -> lvalue[expr]\n");
			}
			| call DOT ID  {printf("member -> call.ID\n");}
			| call LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {printf("member -> call[expr]\n");}
			;

call:		call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  {
				expr *tmp = $3;
				while(tmp){
					emit(param ,tmp, NULL, NULL, -1, yylineno);
					tmp = tmp->next;
				}
				expr *e = newexpr(programfunc_e);
				e->sym = $1->sym;
				emit(call ,e, NULL, NULL, -1, yylineno);
				expr* d = newexpr(var_e);
				d->sym = newtemp(yylineno,scope);
				emit(getretval,d,NULL,NULL,0,yylineno);
				$$ = d;
				printf("call -> (elist)\n");
			}
			| lvalue callsuffix  {

				expr *tmp = $2;
				expr *tobecalled = $2;
				if($2 && $2->isMethodcall){
					expr *e2 = malloc(sizeof(expr));
					memcpy(e2,$1,sizeof(expr));
					expr *tmp2 = $2;
					while(tmp2->next){
						tmp2 = tmp2->next;
					}
					tmp2->next = e2;
					tmp = tmp->next;
					expr *e = newexpr(tableitem_e);
					e->sym = newtemp(yylineno,scope);
					emit(tablegetelem,$1,tobecalled,e,-1,yylineno);
				}
				while(tmp){
					emit(param ,tmp, NULL, NULL, -1, yylineno);
					tmp = tmp->next;
				}
				if($2 && $2->isMethodcall){		
					emit(call ,tobecalled, NULL, NULL, -1, yylineno);
				}else{
					emit(call ,$1, NULL, NULL, -1, yylineno);
				}
				expr *e = newexpr(var_e);
				e->sym = newtemp(yylineno,scope);
				emit(getretval,e,NULL,NULL,0,yylineno);
				$$ = e;
				printf("call -> lvalue callsuffix\n");
			}
			| LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS 
				{
					expr *tmp = $5;
					while(tmp){
						emit(param ,tmp, NULL, NULL, -1, yylineno);
						tmp = tmp->next;
					}
					expr *e = newexpr(programfunc_e);
					e->sym = $2;
					emit(call ,e, NULL, NULL, -1, yylineno);
					expr* d = newexpr(var_e);
					d->sym = newtemp(yylineno,scope);
					emit(getretval,d,NULL,NULL,0,yylineno);
					$$ = d;
					printf("call -> (funcdef)(elist)\n");
				}
			;

callsuffix:	normcall  {
				$$ = $1;
				printf("callsuffix -> normcall\n");}
			| methodcall  {
				$$ = $1;
				printf("callsyffix -> methodcall\n");}
			;

normcall:	LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  {
				$$ = $2;
				if($$)
					$$->isMethodcall = 0;
				printf("normacall -> (elist)\n");}
			;

methodcall:	DOUBLE_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS 
			{
				$$ = newexpr(programfunc_e);
				$$->sym = SymTable_lookup(oSymTable,$2);
				$$->next = $4;
				$$->isMethodcall = 1;
				printf("methodcall -> ..ID(elist)\n");
				} //lvalue.id(lvalue, elist)
			;

elist:	 	expr exprs {
						$$ = $1;
						$1->next = $2;
						if($$->next)
							$$ = reverseList($$);
						printf("elist -> expr exprs\n");
			}
			| /* empty */ {$$ = NULL;printf("elist -> empty\n");}
			;

exprs:	COMMA expr exprs {
			$$ = $2;
			$2->next = $3;
			printf("exprs -> ,expr exprs\n");
		}
		| /* empty */	{$$ = NULL; printf("exprs -> empty\n");}
		;

objectdef:	LEFT_SQUARE_BRACKET index RIGHT_SQUARE_BRACKET {
				expr *e = newexpr(newtable_e);
				e->sym = newtemp(yylineno,scope);
				emit(tablecreate,e,NULL,NULL,-1,yylineno);
				if($2 && $2->iselist){
					expr *tmp = $2;
					int i = 0;
					tmp = reverseList(tmp);
					while(tmp){
						//expr *toemit = numConst_expr(i);
						emit(tablesetelem,e,tmp,numConst_expr(i),-1,yylineno);
						i++;
						tmp = tmp->next;
					}
				}else if($2){
					expr *tmp = $2;
					while(tmp){
						emit(tablesetelem,e,tmp,tmp->index,-1,yylineno);
						tmp = tmp->next;
					}
				}
				$$ = e;
				printf("objectdef -> [index]");
			}
			;

index:		elist {
				$$ = $1;
				if($$)
					$$->iselist = 1;
				printf("index-> elist");}
			| indexed {
				$$ = $1;
				if($$)
					$$->iselist = 0;
				printf("index -> indexed\n");}
			;

indexed:	indexedelem indexedelems {
				$1->next = $2;
				$$ = $1;
				printf("indexed -> indexedelem indexedelems\n");
			}
			;

indexedelem: LEFT_BRACKET expr COLON expr RIGHT_BRACKET {
				$$ = $4;
				$$->index = $2;
				printf("indexedelem -> {expr : expr}\n");}
			 ;

indexedelems:	COMMA indexedelem indexedelems {
					$2->next = $3;
					$$ = $2;
					printf("indexedelems -> ,indexedelem indexedelems\n");}
				| /* empty */ {
					$$ = NULL;
					printf("indexedelems -> empty\n");}
				;

block:	 	LEFT_BRACKET{
				scope++;
			} blstmts RIGHT_BRACKET {
				$$ = $3;
				SymTable_hide(oSymTable, scope);
				printf("block -> [blstmts]\n");
				scope--;
			}
			;

blstmts:	stmts {
				$$ = $1;
				printf("blstmts -> stmts\n");}
			;

funcdef:	funprefix funcargs funcbody
			{
				//exitscopespace(); // -1 gia locals (func definition)
				Node_T sym = Scope_lookup($1->name,userfunc,scope);
				$1->totallocals = currscopeoffset();

				unsigned offset = popOffsetStack();
				restorecurrscopeoffset(offset);

				$$ = $1;
				emit(funcend ,lvalue_expr($1), NULL, NULL, -1, yylineno);

				patchlabel(sym->funcQuadNo,nextquadlabel());
				printf("funcdef -> function funcname (idlist) block\n");
			}
			;

funcname:		ID {					
					node = Scope_lookup($1, libfunc, 0); //elegxos gia shadowing twn libfunc
					if(node != NULL){
						printf("\033[0;31m");
						printf("Error: (line %d) trying to shadow library function %s\n",yylineno,$1);
						printf("\033[0m");
					}else{
						node = Scope_lookup($1, unknown, scope); //elegxos gia function/ variable me to idio onoma sto idio scope
						/* an yparxei */
						if(node != NULL /* && node->isActive == 1 */){
							printf("\033[0;31m");
							printf("Error: (line %d) ID %s already exists in scope %d\n",yylineno,$1,scope);
							printf("\033[0m");
						}else{
							fname = strdup($1);
							SymTable_insert(oSymTable, $1, userfunc, yylineno, scope);
						}
					}
					$$ = Scope_lookup($1,userfunc,scope);
					if($$)
						$$->funcQuadNo = nextquadlabel();
					printf("funcname -> ID\n");
				}
				| /* empty */ {

					sprintf(anonymous,"_f%d",uknownfunc);
					fname = strdup(anonymous);

					SymTable_insert(oSymTable, anonymous, userfunc, yylineno, scope);
					$$ = Scope_lookup(anonymous,userfunc,scope);
					if($$)
						$$->funcQuadNo = nextquadlabel();
					uknownfunc++;
					printf("funcname -> empty\n");
				}
				;

funprefix:	FUNCTION funcname {

				Node_T sym = Scope_lookup($2->name,userfunc,scope);
				fname = strdup(sym->name);
	
				emit(jump ,NULL, NULL, NULL, -1, yylineno);

				sym->iaddress = nextquadlabel();
				emit(funcstart ,lvalue_expr(sym), NULL, NULL, -1, yylineno);
				$$ = sym;
				if(in_func) pushOffsetStack();

				enterscopespace(); // scopespacecount++;
				resetformalargsoffset(); // ormalargsoffset = 0;
				scope++;
			}
			;

funcargs:	LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS{
				scope--; in_func++;
				enterscopespace();
				resetfunctionlocaloffset();
			}
			;

funcbody:	block {
				//exitscopespace(); // -1 gia formals
				Node_T sym = Scope_lookup(fname,userfunc,scope);
				SymTable_hide(oSymTable, scope);
				in_func--;
			}
			;

const:	 	INTEGER {
				$$ = numConst_expr((double)$1);
				printf("const -> INTEGER\n");
			} 
			| REAL {
				$$ = numConst_expr($1);
				printf("const -> REAL\n");
			} 
			| STRING {
				$$ = strConst_expr($1);
				printf("const -> STRING\n");
			}
			| NIL {
				$$ = nilConst_expr();
				printf("const -> NIL\n");
			}
			| TRUE {
				$$ = boolConst_expr('1');
				printf("const -> TRUE\n");
			}
			| FALSE {
				$$ = boolConst_expr('0');
				printf("const -> FALSE\n");
			}
			;

idlist:		id ids {printf("idlist -> id ids\n");}
			;

id:			ID {
				struct argument *tmparg;
				tmparg = ArgumentSearch(fname, $1,scope);
				node = Scope_lookup($1, libfunc, 0);
				if(tmparg != NULL){
					printf("\033[0;31m");
					printf("Error: (line %d) argument %s already defined in function %s\n",yylineno,$1,fname);
					printf("\033[0m");
				}else if(node != NULL){
					printf("\033[0;31m");
					printf("Error: (line %d) trying to shadow library function %s\n",yylineno,$1);
					printf("\033[0m");
				}else{
					ArgumentInsert(fname,$1,scope,oSymTable);
					SymTable_insert(oSymTable, $1, formal, yylineno, scope);
					incurrscopeoffset();
				}
				printf("id -> ID\n");
			}
			| /* empty */ {printf("id -> empty\n");}
			;

ids:		COMMA id ids {printf("ids -> ,id ids\n");}
			| /* empty */	{printf("ids -> empty\n");}
			;

ifstmt:	 	ifprefix stmt
			{
				$$ = $2;
				patchlabel($1,nextquadlabel());
				printf("ifstmt -> if (expr) stmt elsestmt\n");
			}
			| ifprefix stmt elseprefix stmt
			{
				patchlabel($1,$3+1);
				patchlabel($3,nextquadlabel());
			}
			;

ifprefix:	IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS{
				emit(if_eq,$3,boolConst_expr(1),NULL,nextquadlabel()+2,yylineno);
				$$ = nextquadlabel();
				emit(jump,NULL,NULL,NULL,0,yylineno);
			}
			;

elseprefix: ELSE{
				$$ = nextquadlabel();
				emit(jump,NULL,NULL,NULL,0,yylineno);
			}
			;

whilestart: WHILE{
				loop_depth++;
				$$ = nextquadlabel();
			}
			;

whilecond:	LEFT_PARENTHESIS expr RIGHT_PARENTHESIS
			{
				emit(if_eq,$2,boolConst_expr(1),NULL,nextquadlabel()+2,yylineno);
				$$ = nextquadlabel();
				emit(jump,NULL,NULL,NULL,0,yylineno);
			}
			;
whilestmt:		whilestart whilecond stmt{
					stmt_t* tmp;
					emit(jump,NULL,NULL,NULL,$1,yylineno);
					patchlabel($2,nextquadlabel());
					$$ = newstmt();

					if(specialflag){
						stmt_t *tmp = $3->next;
						while(tmp){
							if(tmp->isbreak){
								patchlabel(tmp->quadno, nextquadlabel());
							}
							else{
								patchlabel(tmp->quadno, $1);
							}
							tmp = tmp->next;
						}
					}
					loop_depth--;
					specialflag = 0;
					printf("whilestmt -> while (expr) stmt\n");
				}
				;

N : { $$ = nextquadlabel(); emit(jump,NULL,NULL,NULL,0,yylineno); };

M : { $$ = nextquadlabel(); };
			
forprefix:	FOR {loop_depth++;} LEFT_PARENTHESIS elist SEMICOLON M expr SEMICOLON
			{
				$$ = malloc(sizeof(forval));
				$$->test = $6;
				$$->enter = nextquadlabel();
				emit(if_eq,$7,boolConst_expr(1),NULL,0,yylineno);
			}
			;

forstmt:	forprefix N elist RIGHT_PARENTHESIS N stmt {loop_depth--;} N				
			{
				patchlabel($1->enter,$5+1);
				patchlabel($2,nextquadlabel());
				patchlabel($5,$1->test);
				patchlabel($8,$2+1);

				$$ = newstmt();
				if(specialflag){
						stmt_t *tmp = $6->next;
						while(tmp){
							if(tmp->isbreak){
								patchlabel(tmp->quadno, nextquadlabel());
							}
							else{
								patchlabel(tmp->quadno, $2+1);
							}
							tmp = tmp->next;
						}
					}
				printf("forstmt -> for (elist; expr; elist) stmt\n");}
			;


returnstmt:	RETURN SEMICOLON {
				emit(ret,NULL,NULL,NULL,-1,yylineno);
				printf("returnstmt -> return;\n\n");
			}
			|RETURN expr SEMICOLON {
				emit(ret,$2,NULL,NULL,-1,yylineno);
				printf("returnstmt -> return expr;\n\n");
			}
			;

%%
//EPILOGOS

int yyerror (const char* yaccProvidedMessage){
	fprintf(stderr,"%s: at line %d, before token: %s\n",yaccProvidedMessage,yylineno,yytext);
	fprintf(stderr,"INPUT NOT VALID\n");
}

int main(int argc, char** argv){

	int i;
	
	if(argc > 1){
		if(!(yyin = fopen(argv[1],"r"))){
			fprintf(stderr,"Cannot read file: %s\n",argv[1]);
		}
	}else
		yyin = stdin;

	oSymTable = SymTable_new();

	SymTable_insert(oSymTable, "print", libfunc, 0, 0);
	SymTable_insert(oSymTable, "input", libfunc, 0, 0);
	SymTable_insert(oSymTable, "objectmemberkeys", libfunc, 0, 0);
	SymTable_insert(oSymTable, "objecttotalmembers", libfunc, 0, 0);
	SymTable_insert(oSymTable, "objectcopy", libfunc, 0, 0);
	SymTable_insert(oSymTable, "totalarguments", libfunc, 0, 0);
	SymTable_insert(oSymTable, "argument", libfunc, 0, 0);
	SymTable_insert(oSymTable, "typeof", libfunc, 0, 0);
	SymTable_insert(oSymTable, "strtonum", libfunc, 0, 0);
	SymTable_insert(oSymTable, "sqrt", libfunc, 0, 0);
	SymTable_insert(oSymTable, "cos", libfunc, 0, 0);
	SymTable_insert(oSymTable, "sin", libfunc, 0, 0);

	yyparse();

	printf("\n");

	for(i=0; i < ScopelinkSize(); i++){
		Scope_print(oSymTable, i);
	}
	printQuads();

	init_constTables();

	produce_tcode();

	generateText();
	generateBinary();

	return 0;
 }