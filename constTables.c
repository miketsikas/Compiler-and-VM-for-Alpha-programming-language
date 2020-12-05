#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constTables.h"
#include "tcode.h"

void init_constTables(){
	totalNumConsts = 0;
	totalStringConsts = 0;
	totalNamedLibfuncs = 0;
	totalUserFuncs = 0;
	numConsts = NULL;
	stringConsts = NULL;
	namedLibfuncs = NULL;
	//userFuncs = NULL;
	totalGlobals = 0;
}

unsigned consts_newstring(char* s){
	int position;
	for( position = 0; position < totalStringConsts; ++position){
		if(!strcmp(s,stringConsts[position])) return position;
	}
	totalStringConsts++;
	stringConsts = realloc(stringConsts,totalStringConsts*sizeof(char*));
	stringConsts[totalStringConsts-1] = strdup(s);
	return totalStringConsts - 1;
}

unsigned consts_newnumber(double numConst){
	int position;
	for(position = 0; position < totalNumConsts; ++position){
		if(numConsts[position] == numConst) return position;
	}
	totalNumConsts++;
	numConsts = realloc(numConsts,totalNumConsts*sizeof(double));
	numConsts[totalNumConsts-1] = numConst;
	return totalNumConsts-1;
}

unsigned libfuncs_newused(char* s){
	int position;
	for( position = 0; position < totalNamedLibfuncs; ++position){
		if(!strcmp(s,namedLibfuncs[position])) return position;
	}
	totalNamedLibfuncs++;
	namedLibfuncs = realloc(namedLibfuncs,totalNamedLibfuncs*sizeof(char*));
	namedLibfuncs[totalNamedLibfuncs-1] = strdup(s);
	return totalNamedLibfuncs-1;
}

unsigned userfuncs_newfunc(Node_T sym){
	userFunc f; 
	f.address = sym->taddress;
	f.localSize = sym->totallocals;
	f.id = strdup(sym->name);
	//printf("\n%s LOCAAAAAAAAAAAAAAAALS:  %u\n\n",f.id, f.localSize);
	totalUserFuncs++;
	//userFuncs = realloc(userFuncs,totalUserFuncs*sizeof(userfunc)); // abort
	userFuncs[totalUserFuncs-1] = f;
	return totalUserFuncs-1;
}