#ifndef _AMV_
#define _AVM_
#include "constTables.h"
#include "tcode.h"

#define AVM_STACKSIZE 4096
#define AVM_TABLE_HASHSIZE 211
#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))
#define AVM_STACKENV_SIZE 4
#define AVM_MAX_INSTRACTIONS (unsigned int) nop_v
#define AVM_ENDING_PC codeSize

/*Structs*/
typedef enum avm_memcell_t{
	number_m	=0,
	string_m	=1,
	bool_m		=2,
	table_m		=3,
	userfunc_m	=4,
	libfunc_m	=5,
	nil_m		=6,
	undef_m		=7
}avm_memcell_t;

extern char* typeStrings[];

typedef struct avm_memcell{
	avm_memcell_t type;
	union {
		double numVal;
		char *strVal;
		unsigned int boolVal;
		struct avm_table *tableVal;
		unsigned int funcVal;
		char *libfuncVal;
	}data;
}avm_memcell;

typedef struct avm_table_bucket{
	avm_memcell *key;
	avm_memcell *value;
	struct avm_table_bucket *next;
}avm_table_bucket;

typedef struct avm_table{
	unsigned int refCounter;
	avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket* tableIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket* libfuncIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket* userfuncIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket* boolIndexed[AVM_TABLE_HASHSIZE];
	unsigned int total;
}avm_table;

unsigned char executionFinished;
unsigned int pc;
unsigned int currLine;
unsigned int codeSize;
instruction *code;

extern char *avm_toString(avm_memcell *m);

/* KATAXWRHTES KAI STOIVA */
avm_memcell ax,bx,cx;
avm_memcell retval;
avm_memcell stack[AVM_STACKSIZE];
unsigned int top, topsp;

typedef void (*execute_func_t)(instruction*);
typedef void (*memclear_func_t)(avm_memcell*);

avm_memcell *avm_translate_operand(vmarg* arg, avm_memcell* reg);

void avm_warning(char *msg);
void avm_error(char *msg);

void avm_initstack();
/*Clears*/
void avm_memcellclear(avm_memcell* m);
void memclear_string(avm_memcell* m);
void memclear_table(avm_memcell* m);

/*Tables*/
avm_table *avm_tablenew();
void avm_tabledestroy(avm_table *t);
avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* index);
void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content);

void avm_tabledecrefcounter(avm_table* t);
void avm_tableincrefcounter(avm_table* t);
void avm_tablebucketsinit(avm_table_bucket **p);
void avm_tablebucketsdestroy(avm_table_bucket** p);

/*Omades entolwn*/

void execute_assign (instruction* i);
void avm_assign(avm_memcell *lv,avm_memcell *rv);
/*Arithms*/
void execute_add(instruction *i);
void execute_sub(instruction *i);
void execute_mul(instruction *i);
void execute_div(instruction *i);
void execute_mod(instruction *i);
/*Jumps*/
void execute_jeq(instruction *i);
void execute_jne(instruction *i);
void execute_jle(instruction *i);
void execute_jge(instruction *i);
void execute_jlt(instruction *i);
void execute_jgt(instruction *i);
void execute_jump(instruction *i);
/*Functions*/
void execute_call(instruction *i);
void execute_pusharg(instruction *i);
void execute_funcenter(instruction *i);
void execute_funcexit(instruction *i);
void execute_ret(instruction *instr);
void execute_getretval(instruction *instr);
/*Tables*/
void execute_newtable(instruction *i);
void execute_tablegetelem(instruction *i);
void execute_tablesetelem(instruction *i);
/*Mazi me No-OP*/
void execute_nop(instruction *instr);

void execute_cycle();

unsigned int magic_number;
#endif