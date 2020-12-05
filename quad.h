#ifndef	FUNCTIONS_H_
#define FUNCTIONS_H_

#include "symtable.h"

#define EXPAND_SIZE 1024
#define STR_SIZE 128

typedef enum expr_t expr_t;
typedef enum iopcode {
	assign,       add,         sub,
	mul,          divide,         mod,
	uminus,       and,         or,
	not,          if_eq,       if_noteq,
	if_lesseq,    if_greatereq, if_less,
	if_greater,   call,        param,
	ret,       	  getretval,   funcstart,
	funcend,      tablecreate, jump,
	tablegetelem, tablesetelem
}iopcode;

/*------------- Expression types ------------
Use only the types you really need for i-code
generation so you may drop some entries */

enum expr_t{
	var_e,
	tableitem_e,
	
	programfunc_e,
	libraryfunc_e,
	
	arithexpr_e,
	boolexpr_e,
	assignexpr_e,
	newtable_e,
	
	constnum_e,
	constbool_e,
	conststring_e,
	nil_e,
};

typedef struct expr{
	expr_t type;
	Node_T sym; // pointer se komvo tou ST

	struct expr *index;
	int isMethodcall;
	char *methodname;
	int iselist;

	double numConst;
	char *strConst;
	unsigned char boolConst;
	
	struct expr	*next; // make slists (call, tablemake)
}expr;

typedef struct method_t{
	expr *elist;
	int isMethod;
	char *name;
}method_t;
/*---------------------------------------------*/

/*offset struct */
typedef struct Offset{
	unsigned int localOffset;
	struct Offset *next;
}Offset;

typedef struct quad {
	iopcode op;
	expr*  result;
	expr*  arg1;
	expr*  arg2;
	unsigned label;
	unsigned line;
	unsigned int taddress;
}quad;

typedef struct stmt_t{
	int quadno;
	int isbreak;
	struct stmt_t *next;
}stmt_t;

typedef struct forval{
	int test;
	int enter;
}forval;

/* o pinakas me ta quads */
extern quad *quads;
extern unsigned totalQuads;
extern unsigned int currQuad;

void expand(void); //expand array of quads
void emit(iopcode op ,expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line);

expr *arith_emit(iopcode op, expr *arg1 , expr *arg2,int line, int scope);
expr *relop_emit(iopcode op, expr * arg1, expr * arg2, int line, int scope);
expr *boolop_emit(iopcode op,expr *arg1, expr *arg2, int line, int scope);

Node_T newsymbol(symbol_t type,char* name,unsigned scope,unsigned line);
expr *newexpr(expr_t type);
stmt_t* newstmt();

char *newtempname(void);
void resettemp(void);
Node_T newtemp(int line, int scope);
int istemp(symbol_t *sym);
unsigned int istemname(char *s);
unsigned int istempexpr(expr *e);

scopespace_t currscopespace(void);
unsigned currscopeoffset(void); //epistrefei to offset sto current scope space
void incurrscopeoffset(void);

void enterscopespace(void);
void exitscopespace(void);

unsigned int nextquadlabel( void );
void resetformalargsoffset( void ); 
void resetfunctionlocaloffset( void );
void restorecurrscopeoffset( unsigned int );

expr *emit_iftableitem(expr* e,int scope,int line); 
expr *emit_table(expr *arg1,expr *arg2,int line); 
expr *func_call(expr *lval, expr *args, unsigned int line);
expr *member_item(expr* value, char* name, int line,int scope);

void patchlabel(unsigned quadNo,unsigned label);

expr* newexpr_conststring(char* s);
void comperror(char *format);
void checkuminus(expr* e);

expr *nilConst_expr();
expr *numConst_expr(double numConst);
expr *strConst_expr(char *str);
expr *boolConst_expr(unsigned char bool);
int arith_typecheck(expr *e);
expr *lvalue_expr(struct node *sym);

void printQuads(void);

stmt_t *initList();
stmt_t *mergeLists(stmt_t *list1, stmt_t *list2);

void pushOffsetStack();
unsigned popOffsetStack();
int topOffset();
void printOffset(); //-

expr *reverseList(expr *head);
expr *make_call(expr* e,expr *list,int scope, int line);

#endif 