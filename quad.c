#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quad.h"
#include "symtable.h"
#define CURR_SIZE (totalQuads*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

unsigned int tempcounter = 0;
extern int deepestScope;
extern int deepestFunctionScope;

unsigned int programVarOffset = 0;
unsigned int functionLocalOffset = 0;
unsigned int formalArgOffset = 0;

Offset *OffsetStack = (Offset*) 0; //gia ta definitions twn function mesa se function

/* 
gia global scopespace einai panta 1
eisodos se formalargs: +1
eisodos se func: +1
eksodos apo func: -2
*/
unsigned int scopeSpaceCounter = 1;

quad *quads = (quad*) 0;
unsigned totalQuads = 0; //quad counter
unsigned int currQuad = 0;

SymTable_T oSymTable; // extern sto symtable.h

void expand(void){ 
	assert(totalQuads == currQuad);
	quad* p = (quad*) malloc(NEW_SIZE);
	if (quads){
		memcpy(p, quads, CURR_SIZE);
		free(quads);
	}
	quads = p;
	totalQuads += EXPAND_SIZE;
}

void emit(iopcode op ,expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line){ 
	if(currQuad == totalQuads){
		expand();
	}	
	quad *p = quads + currQuad++;
	p->op = op;
	p->arg1 = arg1;
	p->arg2 = arg2;
	p->result = result;
	p->label = label;
	p->line = line;
}

Node_T newsymbol(symbol_t type,char* name,unsigned scope,unsigned line){
	Node_T sym = malloc(sizeof(struct node));
	sym->type = type;
	sym->name = strdup(name);
	sym->scope = scope;
	sym->line = line;
	return sym;
}

char* newtempname(void){ 
	char *tempname = malloc(STR_SIZE*sizeof(char)); 
	sprintf(tempname , "_t%d" , tempcounter++);
	return tempname;
}

Node_T newtemp(int line, int scope){ // na dwsw to symbol_t san orisma ??
	char *name = newtempname();
	Node_T sym = Scope_lookup(name, unknown /*any type*/, scope);
	/* ama afto to temporary den yparxei sto ST */
	if(sym == NULL){
		/* to dimiourgw kai to eisagw sto ST */
		sym = newsymbol(var_s,name,0,0);
		SymTable_insert(oSymTable, name, unknown, line, scope); // unknown <- temporary
		return sym;
	}else {
		/* alliws epanaxrhsimopoihsh..*/
		return sym;
	}
}

void resettemp(void){ 
	tempcounter = 0;
}

expr* newexpr(expr_t type){ 
	expr* e = (expr*) malloc(sizeof(expr));
	memset(e,0,sizeof(expr));
	e->type = type;
	return e;
}

stmt_t* newstmt(){
	stmt_t *s = malloc(sizeof(stmt_t));
	s->next = NULL;
	return s;
}

int arith_typecheck(expr *e){

	if( e->type == programfunc_e ||
		e->type == libraryfunc_e ||
		e->type == boolexpr_e ||
		e->type == newtable_e ||
		e->type == constbool_e ||
		e->type == conststring_e ||
		e->type == nil_e ){
			printf("Non-arithmetic expression\t"); //comperror
			return 0; //illegal expr for UMINUS
		}
	return 1;
}

/* emit arithmetic quad */
expr *arith_emit(iopcode op, expr *arg1 , expr *arg2,int line, int scope){

	if(!arith_typecheck(arg1)){
		printf("(line: %d)\n", line);
	}
	if(!arith_typecheck(arg2)){
		printf("(line: %d)\n", line);
	}
   
	expr *result = (expr *)malloc(sizeof(expr));
	if(arg1->type == constnum_e && arg1->type == constnum_e){
		result = newexpr(constnum_e);
	}else{
		result = newexpr(var_e);
	}
	result->type = var_e;
	result->sym = newtemp(line,scope);
	emit(op, arg1, arg2, result, -1, line); 
	return(result);
}

expr *boolConst_expr(unsigned char bool){
	expr *e = newexpr(constbool_e);
	e->boolConst = bool;
	e->type = constbool_e;
	return e;
}

/* emit relational quad */
expr *relop_emit(iopcode op, expr *arg1, expr *arg2, int line, int scope){
	expr *tmp ;
	tmp = newexpr(boolexpr_e);
	tmp->sym = newtemp(line,scope);

	emit(op,arg1,arg2,tmp,nextquadlabel()+2,line);
	emit(jump,NULL,NULL,NULL,nextquadlabel()+3,line);
	emit(assign,boolConst_expr('1'),NULL,tmp,0,line);
	emit(jump,NULL,NULL,NULL,nextquadlabel()+2,line);
	emit(assign,boolConst_expr('0'),NULL,tmp,0,line);

	return tmp;
}

/* emit boolean quad */
expr *boolop_emit(iopcode op,expr *arg1, expr *arg2, int line, int scope){
	expr *e = newexpr(boolexpr_e);
	e->sym = newtemp(line,scope);
	emit(op,arg1,arg2,e,0,line);
	return e;
}

expr *strConst_expr(char * str){
	expr * tmp = (expr *) malloc (sizeof(expr));
	assert (str);
	tmp->type = conststring_e;
	tmp->strConst = strdup(str);
	return (tmp);
}

void resetformalargsoffset(void){ 
	formalArgOffset=0;
}
void resetfunctionlocaloffset(void){ 
	functionLocalOffset=0;
}

void restorecurrscopeoffset(unsigned n){ 
	switch(currscopespace()){
		case programvar:
			programVarOffset = n; 
			break;
		case functionlocal: 
			functionLocalOffset = n; 
			break;
		case formalarg:
			formalArgOffset = n;
			break;
		default: assert(0);	
	}
}

unsigned nextquadlabel(void){ 
	return currQuad;
}

void patchlabel(unsigned quadNo, unsigned label){ 
	assert(quadNo < currQuad);
	quads[quadNo].label = label;
}

scopespace_t currscopespace(void){ 
	if(scopeSpaceCounter == 1){
		return programvar;
	}
	else if(scopeSpaceCounter % 2 == 0){
		return formalarg;
	}
	return functionlocal;
}

unsigned currscopeoffset(void){ 
	switch( currscopespace() ){
		case programvar		: return programVarOffset;
		case functionlocal 	: return functionLocalOffset;
		case formalarg		: return formalArgOffset;
		default		: assert(0);
	}
}

void incurrscopeoffset(void){ 
	switch( currscopespace() ){
		case programvar		: ++programVarOffset; break;
		case functionlocal 	: ++functionLocalOffset; break;
		case formalarg		: ++formalArgOffset; break;
		default		: assert(0);
	}
}

void enterscopespace(void){ 
	++scopeSpaceCounter;
}

void exitscopespace(void){ 
	assert(scopeSpaceCounter>1);
	--scopeSpaceCounter;
}

expr *lvalue_expr(Node_T sym){   
   assert(sym);
   expr *e = (expr *)malloc(sizeof(expr));
   memset(e, 0, sizeof(expr));
   
   e->next = (expr*) 0;
   e->sym = sym;
   switch(sym->type){
	   case global:
	   case local:
	   case formal:
	   		e->type = var_e;
			break;
	   case userfunc: 
			e->type = programfunc_e;
	   		break;
	   case libfunc: 
	   		e->type = libraryfunc_e;
	   		break;
	   default:
	   		assert(0);   	   		
   }  
   return(e);
}

expr* newexpr_conststring(char* s){ 
	expr* e = newexpr(conststring_e);
	e->strConst = strdup(s);
	return e;
}

char *exprtostring(expr *e){

   if (!e) return " ";
   expr_t etype = e->type;
   char *tmp;
   tmp = malloc(STR_SIZE*sizeof(char));

   if(etype == var_e || etype == tableitem_e || etype == programfunc_e || etype == libraryfunc_e 
	|| etype == arithexpr_e || etype == boolexpr_e || etype == assignexpr_e || etype == newtable_e){
      return (e->sym)->name;
   }
   else if(etype == constnum_e){
		sprintf(tmp,"%lf", e->numConst);
		return tmp;
   }
   else if(etype == constbool_e){
		if (e->boolConst == '0') return "FALSE";
		else return "TRUE";
   }
   else if(etype == conststring_e){
		char *tmp = malloc(strlen(e->strConst)+2);
		tmp[0]= '\"';
		tmp = strcat(tmp,e->strConst);
		tmp[strlen(tmp)] = '\"';
		return tmp;
   }
   else if(etype == nil_e){
      	return "NIL";
   }else{
		printf("kanenas apo tous gnostous typous: %d\n", etype); 
     	assert(0);
   }
   return NULL;
}

void printQuads(){
	
	FILE *quad_fd;
	int i;
	iopcode op;
	char* opcodes[26] = {"assign","add","sub","mul","divide","mod","uminus","and","or","not","if_eq","if_noteq",
		"if_lesseq","if_greatereq","if_less","if_greater","call","param","return","getretval","funcstart",
		"funcend","tablecreate","jump","tablegetelem","tablesetelem"};   
	
	if ((quad_fd = fopen("icode.txt","w")) == NULL){
		perror("fopen() failed"); 
		exit(1);
	}

	fprintf(quad_fd,"\n--------------------- QUADS ---------------------\n\n");
		
	for(i=0; i<currQuad; i++){
		op = (quads[i]).op;
		fprintf(quad_fd,"%d: %s\t\t ",i+1,opcodes[op]);

		if(op == add || op == sub ||op == mul || op == divide || op == mod
		|| op == and || op == or) {
			fprintf(quad_fd,"\t%s\t ", exprtostring(quads[i].result));
			fprintf(quad_fd,"%s\t", exprtostring(quads[i].arg1));
			fprintf(quad_fd,"%s\t", exprtostring(quads[i].arg2));
		}else if((op == not) || (op == uminus)	|| (op == assign)){
			fprintf(quad_fd,"%s\t", exprtostring(quads[i].result));
			fprintf(quad_fd,"%s\t ", exprtostring(quads[i].arg1));
      	}else if( op == if_eq || op == if_greater || op == if_greatereq
		  || op == if_less | op == if_lesseq || op == if_noteq){
			fprintf(quad_fd,"%s\t ", exprtostring(quads[i].arg1));
			fprintf(quad_fd,"%s\t ", exprtostring(quads[i].arg2));
			fprintf(quad_fd,"%u\t ", quads[i].label+1);
		}else if(op == funcstart || op == funcend || op == ret || op == param 
		|| op == call || op == getretval || op == tablecreate){
			fprintf(quad_fd,"%s\t ", exprtostring(quads[i].arg1));
		}else if(op == jump){
			fprintf(quad_fd,"\t\t%d", quads[i].label+1);
		}else if(op == tablegetelem){
			fprintf(quad_fd,"\t%s\t ", exprtostring(quads[i].result));
			fprintf(quad_fd,"%s\t", exprtostring(quads[i].arg1));
			fprintf(quad_fd,"%s\t", exprtostring(quads[i].arg2));
		}else if(op == tablesetelem){
			fprintf(quad_fd,"%s\t", exprtostring(quads[i].arg1));
			fprintf(quad_fd,"\t%s\t ", exprtostring(quads[i].result));
			fprintf(quad_fd,"%s\t", exprtostring(quads[i].arg2));
		}

		fprintf(quad_fd,"\n");
	}
	fclose(quad_fd);
}

expr* emit_iftableitem(expr* e,int scope, int line){ 
	if(e->type!=tableitem_e) {
		return e;
	}else{
		expr* result = newexpr(var_e);
		result->sym = newtemp(line,scope);
		emit(tablegetelem,e,e->index,result,0,0);
		return result;		
	}	
}

expr* reverseList(expr *head){
	struct expr *p, *q, *r;
 	if(head ->next == NULL){
 		return head;
 	}
    p = head;
    q = head;
    r = head;
    p = p->next->next;
    q = q->next;
    r->next = NULL;
    q->next = r;
 
    while (p != NULL)
    {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    return q;
}

expr *nilConst_expr(){
	expr *e = newexpr(nil_e);
	e->type = nil_e;
	return e;
}
expr *numConst_expr(double numConst){
	expr *tmp = newexpr(constnum_e);
	tmp->numConst = numConst;
	return tmp;
}

expr *numStrConst_expr(int numConst, char * strConst){
	expr *tmp = newexpr(conststring_e);
	tmp->numConst = numConst;
	tmp->strConst = malloc (100);
	sprintf(tmp->strConst,"%s",strConst);
	return tmp;
}

expr *member_item(expr* value, char* name, int line,int scope){
	value = emit_iftableitem(value,scope,line);
	expr *tableitem = newexpr(tableitem_e);
	tableitem->sym = value->sym;
	tableitem->index = strConst_expr(name);
	return tableitem;
}
/*
expr *func_call(expr *lval, expr *args, unsigned int line){
	expr *functionName = emit_iftableitem(lval, line);
	expr * tmp=args;
	expr * paramTable[1024];
	int i = 0;
	while(tmp!=NULL){
		paramTable[i] = tmp;
		i++;
		tmp=tmp->next;
		assert(i<1024);
	}
	i--;
	for (i; i>=0; i--){
		emit(param,NULL,NULL, paramTable[i],-1,line);
	}
		
	emit(call, NULL, NULL,functionName, -1, line);
	expr *result = newexpr(var_e);
	result -> sym = newtemp();
	emit(getretval, NULL, NULL, result, -1, line);
	return result;
}
*/

/*Synartiseis gia stoiva twn Offsets*/

// push stin OffsetStack to localOffset
void pushOffsetStack(){

	Offset *tmp = malloc(sizeof(Offset));
	tmp->localOffset = functionLocalOffset;
	tmp->next = NULL;

	if(OffsetStack == NULL){
		OffsetStack = tmp;
	}else{
		tmp->next = OffsetStack;
		OffsetStack = tmp;
	}
}

//pop to localOffset
unsigned popOffsetStack(){
	if(!OffsetStack) return 0;
	functionLocalOffset = OffsetStack->localOffset;
	Offset *tmp = OffsetStack;
	if(OffsetStack->next){
		OffsetStack = OffsetStack->next;
	}
	free(tmp);
	return functionLocalOffset;
}

void printOffset(){
	int i = 0;
	Offset *tmp = malloc(sizeof(Offset));
	tmp = OffsetStack;
	while(tmp){
		printf("####################### Offset%d: %d\n",i,tmp->localOffset);
		i++;
		tmp = tmp->next;
	}
}

int topOffset(){ //den to xrisimopoiw kapou
	assert(OffsetStack);
	return OffsetStack->localOffset;
}

stmt_t *initList(int quadno){
	stmt_t *tmp = malloc(sizeof(stmt_t));
	tmp->quadno = quadno;
	tmp->next = NULL;
	return tmp;
}

stmt_t *mergeLists(stmt_t *list1, stmt_t *list2){

	if(!list1) return list2;
	else if(!list2) return list1;
	
	stmt_t *tmp = list1;

	while(tmp->next){ 
		tmp = tmp->next;
	}
	tmp->next = list2;
	return list1;
}

/*expr *make_call(expr* e,expr *list,int scope, int line){
	expr *func = emit_iftableitem(e);
	reverseList(e);
	expr *tmp = list;
	while(list){
		emit(param,tmp,NULL,NULL,0,line);
		list = list->next;
	}
	emit(call,func,NULL,NULL,0,line);
	expr *result = newexpr(var_e);
	result->sym = newtemp(line,scope);
	emit(getretval,result,NULL,NULL,0,line);
	return result;
}
expr *emit_table(expr *arg1,expr *arg2,int line){
      expr *tmp = emit_iftableitem(arg1,line);
      expr *new = newexpr(tableitem_e);
      new->sym = tmp->sym;
      new->index = arg2;
      return(new);
}
int istemp(Symbol *sym){
   char tmp[2];
   
   tmp[0] = sym->name[0];
   tmp[1] = '\0';
  
   if(!strcmp(tmp,"_s")){
      return(1);
   }   
   return(0);
}
unsigned int istemname(char *s){ 
	return *s == '_';
}
unsigned int istempexpr(expr *e){ 
	return e->sym &&
		   e->sym->type == var_s &&
		   istemname(e->sym->name);
}
*/