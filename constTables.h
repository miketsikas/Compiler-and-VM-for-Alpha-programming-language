#ifndef CONST_ARRAYS_H_
#define CONST_ARRAYS_H_

#include "symtable.h"

typedef struct userfunc {
    unsigned address;
    unsigned localSize;
    char* id;
}userFunc;

double *numConsts; /* pinakas me const numbers tou programmatos */
unsigned totalNumConsts;

char **stringConsts; /* pinakas me const strings tou programmatos */
unsigned totalStringConsts;

char **namedLibfuncs; /* pinakas me onomata twn libfunc pou xrisimopoiountai sto programma */
unsigned totalNamedLibfuncs;

userFunc userFuncs[100]; /* pinakas me synartiseis xristi */
unsigned totalUserFuncs;

void init_constTables();
unsigned consts_newstring(char* s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(char* s);
unsigned userfuncs_newfunc(Node_T sym);

#endif