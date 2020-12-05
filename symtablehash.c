#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "symtable.h"
#include "quad.h"

#define HASH_MULTIPLIER 65599
#define MAXSIZE 300

struct symtable {
   /* array of MAXSIZE positions, each one 
	with a -pointer to- list node */
	Node_T hashtable[MAXSIZE];
};

/* hash function: return a hash code for pcKey */
static unsigned int SymTable_hash(const char *pcKey){
  size_t ui;
  unsigned int uiHash = 0U;
  for (ui = 0U; pcKey[ui] != '\0'; ui++)
    uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
  return uiHash;
}

/* SymTable_new: creates a new empty symbol table */
SymTable_T SymTable_new(void){

	SymTable_T st;
	int i;
	st = malloc(sizeof(struct symtable));
	if(st==NULL){
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<MAXSIZE; i++){
		st->hashtable[i]=NULL;
	}
	for(i=0; i<L_SIZE; i++){
		ScopeLink[i] = NULL;
	}
	return st;
}

/* SymTable_getLength: returns the length of the symbol table */
unsigned int SymTable_getLength(SymTable_T oSymTable){

	Node_T tmp; 
	int i, count = 0;

	assert(oSymTable!=NULL);

	for(i=0; i<MAXSIZE; i++){
		tmp = oSymTable->hashtable[i];
		/* count nodes */
		while(tmp != NULL){
			count++;
			tmp = tmp->next;
		}
	}
	return count;
}

/* Symtable_insert: adds a new node at hashtable initialized with parameters */
int SymTable_insert(SymTable_T oSymTable, const char *name, Type type, unsigned int line, unsigned int scope){

	Node_T tmp;
	char *copy;
	int bucket;

	assert(oSymTable!=NULL);

	if(name == NULL) return 0;

	/* katakermatismos -> apothikevo to index tou neou binding ston pinaka */
	bucket = SymTable_hash(name)%MAXSIZE;

	/* Dimiourgia copy tou name */
	copy = malloc(strlen(name)*sizeof(char));
	strcpy(copy, name);
	
	/* Prosthiki tou neou binding */
	tmp = malloc(sizeof(struct node));
	if(tmp==NULL){
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	printf("insert node\n");

	tmp->name = malloc(strlen(copy)*sizeof(char));
	strcpy(tmp->name, copy);

	tmp->type = type;
	tmp->line = line;
	tmp->scope = scope;
	tmp->isActive = 1;

	if(type == libfunc){
		tmp->stype = libraryfunc_s;
	}

	tmp->next = oSymTable->hashtable[bucket];
	oSymTable->hashtable[bucket] = tmp;

	/* insert to scopelink */
	if(ScopeLink[scope] == NULL){
		ScopeLink[scope] = oSymTable->hashtable[bucket]; /* header */
		
	} else {

		tmp = ScopeLink[scope];
		ScopeLink[scope] = oSymTable->hashtable[bucket];
		oSymTable->hashtable[bucket]->scope_next = tmp;
	}

	printf("------------------------- name: %s, line: %d, scope: %d\n\n", ScopeLink[scope]->name, ScopeLink[scope]->line, ScopeLink[scope]->scope);
	return 1;
}

/* SymTable_lookup: returns the node with this name and scope */
Node_T SymTable_lookup(SymTable_T oSymTable, const char *name){

	Node_T tmp; int i;
	assert(oSymTable!=NULL);

	if(name == NULL) return NULL;

	i=SymTable_hash(name)%MAXSIZE;
	tmp = oSymTable->hashtable[i];

	while(tmp != NULL){
		if(strcmp(tmp->name, name)==0)
			return tmp;
		tmp = tmp->next;
	}

	return NULL;
}

/* Scope_lookup: returns the node of a specific scope */
Node_T Scope_lookup(const char *name, Type type, unsigned int scope){

	Node_T tmp = ScopeLink[scope];

	/* elenxo gia function anamesa se dilwsi kai xrisi */
	if(name == NULL){
		printf("ELENXOS gia function anamesa se dilwsi kai xrisi\n");
		if(type == userfunc){
			while(tmp != NULL){
				if( tmp->type == type && tmp->isActive == 1 ){ // isActive ??
					printf("VRETHIKE FUNCTION ANAMESA: %s\n", tmp->name);
					return tmp;
				} 
				tmp = tmp->scope_next;
			}
		}else return NULL;
	}

	if(tmp != NULL && type == unknown){
		while(tmp != NULL){
			if(!strcmp(tmp->name, name))
				return tmp;
			tmp = tmp->scope_next;
		}
	} else {
		while(tmp != NULL){
			if(!strcmp(tmp->name, name) && (tmp->type == type))
				return tmp;
			tmp = tmp->scope_next;
		}
	}

	return NULL;
}

/* Symtable_hide: deactivation of a single scope variables */
void SymTable_hide(SymTable_T oSymTable, unsigned int scope){

	Node_T tmp;

	assert(oSymTable!=NULL);

	tmp = ScopeLink[scope];

	while(tmp != NULL){
		tmp->isActive = 0;
		tmp = tmp->scope_next;
	}
}

/* prints the entire symbol table */
void SymTable_print(SymTable_T oSymTable) {

	Node_T tmp; 
	int i;

	assert(oSymTable!=NULL);

	for(i=0; i<MAXSIZE; i++){
		tmp = oSymTable->hashtable[i];

		while(tmp != NULL){
			printf("name: %s\n", tmp->name);
			tmp = tmp->next;
		}
	}
	return;
}

/* prints the nodes of a specific scope  */
void Scope_print(SymTable_T oSymTable, unsigned int scope) {
	FILE *f = fopen("scopes.txt","a");
	Node_T tmp;
	assert(oSymTable!=NULL);

	tmp = ScopeLink[scope];

	fprintf(f,"\n--------- Scope #%u --------\n", scope);

	while(tmp != NULL){
		fprintf(f,"\"%s\" [%s] (line %d) (scope %d)\n", tmp->name, enumtostr(tmp->type), tmp->line, tmp->scope);
		tmp = tmp->scope_next;
	}
	fclose(f);
	return;
}

/* search agrument list of funcName function for argument argName */
Arg_T ArgumentSearch(char *funcName, char *argName, unsigned int scope){

	Arg_T tmparg = NULL;
	Node_T tmpnode;

	tmpnode = Scope_lookup(funcName, userfunc, scope-1);

	if(tmpnode)
		tmparg = tmpnode->arguments;
	while(tmparg != NULL){

		if(!strcmp(tmparg->name, argName)){
			return tmparg;
		}
		tmparg = tmparg->next;
	}
	return NULL;
}

/* inserts an argument to the list of arguments of function funcName */
void ArgumentInsert(char *funcName, char *argName, unsigned int scope, SymTable_T oSymTable){
	printf("%s, %d\n",funcName,scope-1);
	
	struct argument *tmparg, *newArg;

	newArg = malloc(sizeof(struct argument));
	Node_T tmpNode = malloc(sizeof(struct node));

	//printf("name %s type %d\n",argName,userfunc);
	scope--;
	tmpNode = Scope_lookup(funcName,userfunc,scope);

	newArg->name = strdup(argName); // strdup den xreiazetai malloc
	newArg->next = NULL;

	if(tmpNode && tmpNode->arguments == NULL){	
		tmpNode->arguments = newArg;
	} else if(tmpNode) {
		tmparg = malloc(sizeof(struct argument));
		tmparg = tmpNode->arguments;
		tmpNode->arguments = newArg;
		newArg = tmparg;
	}
	return;
}

/* returns the current maxScope */
int ScopelinkSize() {

	Node_T tmp; 
	int i, maxScope = 0;

	for(i=0; i<L_SIZE; i++){
		if(ScopeLink[i] != NULL){
			maxScope++;
		} else break;
	}
	return maxScope;
}

/* Checks for any function in a certain range of scopes */
int FuncBetween(int start, int end){
	int i;
	for (i=start; i<=end; i++){
		if (Scope_lookup(NULL, userfunc, i))
			return 1;
	}
	return 0;
}

/* Type enum to string */
char *enumtostr(Type type){

	if(type==global) return "global";
  	else if(type==local) return "local";
  	else if(type==formal) return "formal";
  	else if(type==userfunc) return "userfunc";
  	else if(type==libfunc) return "libfunc";
  	return NULL;
}