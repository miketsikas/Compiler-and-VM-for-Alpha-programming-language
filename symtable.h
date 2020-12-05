#ifndef SYMTABLE_H
#define SYMTABLE_H
typedef struct symtable *SymTable_T;
typedef struct node *Node_T;
typedef struct argument *Arg_T;

#define L_SIZE 50

extern SymTable_T oSymTable;

typedef enum scopespace_t {
	programvar, functionlocal, formalarg
}scopespace_t;

typedef enum symbol_t {
	var_s, programfunc_s, libraryfunc_s, unknown_s
}symbol_t;

typedef enum SymbolType {
	global, local, formal, userfunc, libfunc, unknown
} Type;

struct argument {
	char *name;
	Arg_T next;
};

/* a hashtable node */
struct node {

	char *name;
	enum SymbolType type;
	symbol_t stype;
	unsigned int line;
	unsigned int scope;
	int isActive;
	unsigned offset;
	scopespace_t space;
	int funcQuadNo;
	
	Arg_T arguments; //list of func arguments

	unsigned iaddress;
	unsigned taddress;
	unsigned totallocals;
	
	Node_T next;
	Node_T scope_next;
};

Node_T ScopeLink[L_SIZE];

/* SymTable_new: creates a new empty symbol table */
SymTable_T SymTable_new(void);

/* SymTable_getLength: returns the length of the symbol table */
unsigned int SymTable_getLength(SymTable_T oSymTable);

/* Symtable_insert: adds a new node at the sybol table */
int SymTable_insert(SymTable_T oSymTable, const char *name, Type type, unsigned int line, unsigned int scope);

/* SymTable_lookup: returns the node with this name and scope */
Node_T SymTable_lookup(SymTable_T oSymTable, const char *name);

/* Scope_lookup: returns the node of a specific scope */
Node_T Scope_lookup(const char *name, Type type, unsigned int scope);

/* Symtable_hide: deactivation of a single scope variables */
void SymTable_hide(SymTable_T oSymTable, unsigned int scope);

/* prints the entire symbol table */
void SymTable_print(SymTable_T oSymTable);

/* prints the nodes of a specific scope  */
void Scope_print(SymTable_T oSymTable, unsigned int scope);

/* search agrument list of funcName function for argument argName */
Arg_T ArgumentSearch(char *funcName, char *argName, unsigned int scope);

/* inserts an argument to the list of arguments of function funcName */
void ArgumentInsert(char *funcName, char *argName, unsigned int scope, SymTable_T oSymTable);

/* returns the current maxScope */
int ScopelinkSize();

/* Checks for any function in a certain range of scopes */
int FuncBetween(int start, int end);

/* Type enum to string */
char *enumtostr(Type type);
#endif