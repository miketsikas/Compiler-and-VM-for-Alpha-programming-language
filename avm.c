#include "avm.h"

/* h thesi prei na einai h idia me tin arithitiki timi 
tou vmopcode gia to <op> */
execute_func_t executeFuncs[] = {
   execute_assign,
   execute_add,
   execute_sub,
   execute_mul,
   execute_div,
   execute_mod,
   0,//execute_uminus,
   0,//execute_and,
   0,//execute_or,
   0,//execute_not,
   execute_jeq,
   execute_jne,
   execute_jle,
   execute_jge,
   execute_jlt,
   execute_jgt,
   execute_call,
   execute_pusharg,
   execute_ret,//
   execute_getretval,//
   execute_funcenter,
   execute_funcexit,
   execute_jump,//
   execute_newtable,
   execute_tablegetelem,
   execute_tablesetelem,
   0//execute_nop
};

char *typeStrings[8] = {
	"number_m", "string_m", "bool_m", "table_m", 
	"userfunc_m", "libfunc_m", "nil_m", "undef_m"
};

double consts_getnumber (unsigned int index){
	return numConsts[index];
}

char *consts_getstring (unsigned int index){
	return stringConsts[index];
}
char *libfuncs_getused(unsigned int index){
	return namedLibfuncs[index];
}

unsigned int userfuncs_getused(unsigned int index){
	return userFuncs[index].address;
}


avm_memcell *avm_translate_operand(vmarg* arg, avm_memcell* reg){
	switch (arg->type){
		case global_a:
			return &stack[AVM_STACKSIZE-1-arg->value];
		case local_a:
			return &stack[topsp-arg->value];
		case formal_a :
			return &stack[topsp+AVM_STACKENV_SIZE+1+arg->value];
     	case retval_a :
	 		return &retval;
	 	case number_a:{
	 		reg->type = number_m;
	 		reg->data.numVal = consts_getnumber(arg->value);
	 		return reg;
	 	}
	 	case string_a:{
	 		reg->type = string_m;
	 		reg->data.strVal = strdup(consts_getstring(arg->value));
	 		return reg;
	 	}
	 	case bool_a:{
	 		reg->type = bool_m;
	 		reg->data.boolVal = arg->value;
	 		return reg;
	 	}
	 	case nil_a:{
	 		reg->type = nil_m;
	 		return reg;
	 	}
	 	case userfunc_a:{
	 		reg->type = userfunc_m;
	 		reg->data.funcVal = userfuncs_getused(arg->value);
	 		return reg;
	 	}
	 	case libfunc_a:{
	 		reg->type = libfunc_m;
	 		reg->data.libfuncVal = strdup(libfuncs_getused(arg->value));
	 		return reg;
	 	}
	 	default:
	 		assert(0);
	}
}

void execute_cycle(){
	while(1){
		if(executionFinished) 
			return;
		else if(pc == AVM_ENDING_PC){
			executionFinished = 1;
			return;
		}
		else{
			assert(pc < AVM_ENDING_PC);
			instruction *instr = code + pc;
			assert( instr->opcode >= 0 &&
					instr->opcode <= AVM_MAX_INSTRACTIONS); //to opcode ginetai 25 !!
			if(instr->srcLine)
				currLine = instr->srcLine;
			unsigned oldPC = pc;
			(*executeFuncs[instr->opcode])(instr);
			if(pc == oldPC) ++pc;
		}
	}
}

memclear_func_t memclearFuncs[] = {
	0, /*number*/
	memclear_string,
	0, /*bool*/
	memclear_table,
	0, /*userfunc*/
	0, /*libfunc*/
	0, /*nil*/
	0 /*undef*/
};

void avm_memcellclear(avm_memcell* m){
	if(m->type != undef_m){
		memclear_func_t f = memclearFuncs[m->type];
		if(f)
			(*f)(m);
		m->type = undef_m;
	}
}

void memclear_string(avm_memcell *m){
	assert(m->data.strVal);
	free(m->data.strVal);
}

void memclear_table(avm_memcell *m){
	assert(m->data.tableVal);
}

void avm_initstack(){
	for(unsigned i=0; i<AVM_STACKSIZE; ++i){
		AVM_WIPEOUT(stack[i]);
		stack[i].type = undef_m;
	}
	executionFinished = 0;
	pc = 0;
	currLine = 0;
	codeSize = 0;
	code = NULL;
}
/*
void readBinary(FILE * f){
	fread(&magic_number,sizeof(unsigned int),1,f);
	fread(&totalGlobals,sizeof(unsigned int),1,f);
	
	fread(&totalStringConsts,sizeof(unsigned int),1,f);
	stringConsts = malloc(totalStringConsts*sizeof(char *));
	int i;
	for(i = 0; i<totalStringConsts;++i){
		unsigned int size;
		fread(&size,sizeof(unsigned int),1,f);
		stringConsts[i] = malloc(size*sizeof(char));
		fread(stringConsts[i],sizeof(char),size,f);
	}

	fread(&totalNumConsts,sizeof(unsigned int),1,f);
	numConsts = malloc(totalNumConsts*sizeof(double));
	for(i=0;i<totalNumConsts;++i){
		fread(&numConsts[i],sizeof(double),1,f);
	}

	fread(&totalUserFuncs,sizeof(unsigned int),1,f);
	//userFuncs = malloc(totalUserFuncs*sizeof(userfunc));
	for(i=0;i<totalUserFuncs;++i){
		fread(&userFuncs[i].address,sizeof(unsigned int),1,f);
		fread(&userFuncs[i].localSize,sizeof(unsigned int),1,f);
		unsigned int length;
		fread(&length,sizeof(unsigned int),1,f);
		userFuncs[i].id = malloc(length*sizeof(char));
		fread(userFuncs[i].id,sizeof(char),length,f);
	}

	fread(&totalNamedLibfuncs,sizeof(unsigned int),1,f);
	namedLibfuncs = malloc(totalNamedLibfuncs*sizeof(char *));
	for(i=0;i<totalNamedLibfuncs;++i){
		unsigned int length;
		fread(&length,sizeof(unsigned int),1,f);
		namedLibfuncs[i] = malloc(length*sizeof(char));
		fread(namedLibfuncs[i],sizeof(char),length,f);
	}

	fread(&codeSize,sizeof(unsigned int),1,f);
	code = malloc(codeSize*sizeof(instruction));
	for(i=0;i<codeSize;++i){
		unsigned int lucky,unlucky;
		fread(&code[i].opcode,sizeof(unsigned int),1,f);
		fread(&code[i].srcLine,sizeof(unsigned int),1,f);
		fread(&lucky,sizeof(unsigned int),1,f);
		fread(&unlucky,sizeof(unsigned int),1,f);
		if(unlucky == 666){
			code[i].arg1 = NULL;
		}
		else{
			code[i].arg1 = malloc(sizeof(vmarg));
			code[i].arg1->type = lucky;
			code[i].arg1->value = unlucky;
		}
		fread(&lucky,sizeof(unsigned int),1,f);
		fread(&unlucky,sizeof(unsigned int),1,f);
		if(unlucky == 666){
			code[i].arg2 = NULL;
		}
		else{
			code[i].arg2 = malloc(sizeof(vmarg));
			code[i].arg2->type = lucky;
			code[i].arg2->value = unlucky;
		}
		fread(&lucky,sizeof(unsigned int),1,f);
		fread(&unlucky,sizeof(unsigned int),1,f);
		if(unlucky == 666){
			code[i].result = NULL;
		}
		else{
			code[i].result = malloc(sizeof(vmarg));
			code[i].result->type = lucky;
			code[i].result->value = unlucky;
		}
	}
	top=AVM_STACKSIZE -totalGlobals-2;
    topsp=top;
}
*/
void readBinary(){

    FILE *readfd;
    unsigned i, unknown = 11, whenargisnull, garbage;
    unsigned strsize;

    readfd = fopen("binary.bin","rb");  // r for read, b for binary
    if (!readfd){
        printf("Unable to open binary file for reading.\n");
        return;
    }
    fread(&magic_number,sizeof(unsigned int),1,readfd);

    /* constTables: Numbers */
    fread(&totalNumConsts,sizeof(unsigned),1,readfd);
    numConsts = malloc(totalNumConsts*sizeof(double));
	//fread(numConsts,totalNumConsts*sizeof(double),1,readfd);
	for(i=0; i<totalNumConsts; i++){
		fread(&numConsts[i],sizeof(double),1,readfd);
		printf("%d:	%f\n",i,numConsts[i]);
	}

    /* constTables: Strings */
    fread(&totalStringConsts,sizeof(unsigned),1,readfd);
	stringConsts = malloc(totalStringConsts*sizeof(char *));
	for(i = 0; i<totalStringConsts; i++){
		
		fread(&strsize,sizeof(unsigned),1,readfd);
		stringConsts[i] = malloc(strsize*sizeof(char));
		fread(stringConsts[i],strsize,1,readfd);
	}
    /* constTables: Libfuncs */
    fread(&totalNamedLibfuncs, sizeof(unsigned), 1, readfd);
    namedLibfuncs = malloc(totalNamedLibfuncs*sizeof(char *));
    for(i=0; i<totalNamedLibfuncs; i++){

        fread(&strsize, sizeof(unsigned), 1, readfd);
        namedLibfuncs[i] = malloc(strsize*sizeof(char));
        fread(namedLibfuncs[i], strsize, 1, readfd);
    }
    /* constTables: Userfuncs */
    fread(&totalUserFuncs, sizeof(unsigned), 1, readfd);
    //userFuncs = malloc(totalUserFuncs*sizeof(userFunc));
    for(i=0; i<totalUserFuncs; i++){
        fread(&userFuncs[i].address, sizeof(unsigned), 1, readfd);
        fread(&userFuncs[i].localSize, sizeof(unsigned), 1, readfd);
		fread(&strsize, sizeof(unsigned), 1, readfd);
        userFuncs[i].id = malloc(strsize); //+1 gia to null ?
        fread(userFuncs[i].id, strsize, 1, readfd);
    }

    /* t-code */
    fread(&codeSize, sizeof(unsigned), 1, readfd);
    code = malloc(codeSize*sizeof(instruction));
    for(i=0; i<codeSize; i++){
        /* opcode, type value, type value, type value */
        fread(&code[i].opcode,sizeof(unsigned int),1,readfd);

		fread(&whenargisnull, sizeof(vmarg_t),1,readfd);
		if(whenargisnull != unknown){
			code[i].arg1 = malloc(sizeof(vmarg));
        	code[i].arg1->type = whenargisnull;
        	fread(&code[i].arg1->value,sizeof(unsigned int),1,readfd);
		}else{
			code[i].arg1 = NULL;
			fread(&garbage,sizeof(unsigned int),1,readfd);
		}

		fread(&whenargisnull, sizeof(vmarg_t),1,readfd);
		if(whenargisnull != unknown){
			code[i].arg2 = malloc(sizeof(vmarg));
        	code[i].arg2->type = whenargisnull;
        	fread(&code[i].arg2->value,sizeof(unsigned int),1,readfd);
		}else{
			code[i].arg2 = NULL;
			fread(&garbage,sizeof(unsigned int),1,readfd);
		}

		fread(&whenargisnull, sizeof(vmarg_t),1,readfd);
		if(whenargisnull != unknown){
			code[i].result = malloc(sizeof(vmarg));
        	code[i].result->type = whenargisnull;
        	fread(&code[i].result->value,sizeof(unsigned int),1,readfd);
		}else{
			code[i].result = NULL;
			fread(&garbage,sizeof(unsigned int),1,readfd);
		}
    }
    fclose(readfd);
}

/*
char *avm_toString(avm_memcell *m){

	char *str;
	switch (m->type){
		case number_m:
			sprintf(str, "%fl",m->data.numVal);
			break;
		case bool_m:
			sprintf(str, "%u",m->data.boolVal);
			break;
		case userfunc_m:
			sprintf(str, "%u",m->data.funcVal);
			break;
		case string_m:
			return m->data.strVal;
		case libfunc_m:
			return m->data.libfuncVal;
		default:
			return "";
	}
	return str;
}
*/

void avm_error(char* format){
	executionFinished = 1;
	printf("\nRuntime Error: %s\n", format);
}

void avm_warning(char* format){
	printf("\nRuntime Warning: %s\n ",format);
}

int main(int argc, char** argv){
/*	FILE *fd = fopen(argv[1],"r");
	if(!fd){
		perror("Could not open file\n");
		return 1;
	}*/
	avm_initstack();
	readBinary();

	execute_cycle();
	//fclose(fd);
	return 0;
}
