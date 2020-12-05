#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "quad.h"
#include "constTables.h"

extern unsigned int magic_number;

typedef struct incomplete_jump incomplete_jump;
typedef void (*generator_func_t) (quad*);

extern generator_func_t generators[];

typedef enum vmopcode {
    assign_v = 0,   add_v = 1,      sub_v = 2,
    mul_v = 3,      div_v = 4,      mod_v = 5,
    uminus_v = 4,   and_v = 5,      or_v = 6,
    not_v = 7,      jeq_v = 8,      jne_v = 9,
    jle_v = 10,     jge_v = 11,     jlt_v = 12,
    jgt_v = 13,     call_v = 14,    pusharg_v = 15,
    ret_v = 16,     getretval_v = 17, funcenter_v = 18, 
    funcexit_v = 19, jump_v = 20,   newtable_v = 21, 
    tablegetelem_v = 22, tablesetelem_v = 23, nop_v = 24
}vmopcode;

typedef enum vmarg_t {
    label_a = 0,
    global_a = 1,
    formal_a = 2,
    local_a = 3,
    number_a = 4,
    string_a = 5,
    bool_a = 6,
    nil_a = 7,
    userfunc_a = 8,
    libfunc_a = 9,
    retval_a = 10,
    unknown_a = 11
}vmarg_t;

typedef struct vmarg {
    vmarg_t type;
    unsigned value;
}vmarg;

typedef struct instruction {
    vmopcode opcode;
    vmarg *result;
    vmarg *arg1;
    vmarg *arg2;
    unsigned srcLine;
}instruction;

/* o pinakas me ta instructions */
extern instruction *instructions;
extern unsigned totalInstr;
extern unsigned int currInstr;

typedef struct returnList{
    unsigned int label;
    struct returnList *next;
}returnList;

typedef struct funcstack{
    Node_T funcSym;
    returnList* rlist;
    unsigned int line;
    struct funcstack *next;
}funcstack;

struct incomplete_jump {
    unsigned instrNo; //the jump instruction number
    unsigned iaddress; //the i-code jump-target address
    incomplete_jump* next;
};

extern incomplete_jump* ij_head;
extern unsigned ij_total;

unsigned totalGlobals; //??

void add_incomplete_jump (unsigned instrNo, unsigned iaddress);
void patch_incomplete_jump();

extern int nextInstructionLabel();

extern void generate (vmopcode op, quad* quad);
extern void generate_ADD (quad*);
extern void generate_SUB (quad*);
extern void generate_MUL (quad*);
extern void generate_DIV (quad*);
extern void generate_MOD (quad*);
extern void generate_NEWTABLE (quad*);
extern void generate_TABLEGETELEM (quad*);
extern void generate_TABLESETELEM (quad*);
extern void generate_ASSIGN (quad*);
extern void generate_NOP ();
extern void generate_JUMP (quad*);
extern void generate_IF_EQ (quad*);
extern void generate_IF_NOTEQ (quad*);
extern void generate_IF_GREATER (quad*);
extern void generate_IF_GREATEREQ (quad*);
extern void generate_IF_LESS (quad*);
extern void generate_IF_LESSEQ (quad*);
extern void generate_UMINUS (quad*);
extern void generate_NOT (quad*);
extern void generate_AND (quad*);
extern void generate_OR (quad*);
extern void generate_PARAM (quad*);
extern void generate_CALL (quad*);
extern void generate_GETRETVAL (quad*);
extern void generate_FUNCSTART (quad*);
extern void generate_RETURN (quad*);
extern void generate_FUNCEND (quad*);

extern void produce_tcode();

void generateText();
void generateBinary();