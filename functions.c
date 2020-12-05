#include "avm.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define AVM_NUMACTUALS_OFFSET 		  4
#define AVM_SAVEDPC_OFFSET 	  		  3
#define AVM_SAVEDTOP_OFFSET  		  2
#define AVM_SAVEDTOPSP_OFFSET 		  1
#define PI 3.14159265

typedef char* (*tostring_func_t)(avm_memcell*);

char *avm_toString(avm_memcell *);
void avm_calllibfunc(char *id);
void avm_callsaveenviroment();

userFunc *avm_getfuncinfo(unsigned address);
userFunc *avm_getfuncinfo(unsigned address);

unsigned int totalActuals = 0;

char *libfunc_tostring(avm_memcell *m){
	char *function;// = malloc(sizeof(char)*100);
	function = strdup(m->data.libfuncVal);
	return function;
}

char *number_tostring(avm_memcell *m){
	char *num = malloc(sizeof(char)*100);
	gcvt(m->data.numVal,10,num);
	return num;
}

char *string_tostring(avm_memcell *m){
	char *string = strdup(m->data.libfuncVal);
	return string;
}

char *bool_tostring(avm_memcell *m){
	if(m->data.boolVal == 0)
		return "false";
	else
		return "true";
}

char *userfunc_tostring(avm_memcell *m){
	char *num = malloc(sizeof(char)*100);
	gcvt(m->data.funcVal,10,num);
	return num;
}

char *nil_tostring(avm_memcell *m){
	char *nil = malloc(sizeof(char)*100);
	char *new = "NIL";
	strcat(nil,new);
	return nil;
}

char *undef_tostring(avm_memcell *m){
	char *undef = malloc(sizeof(char)*100);
	char *new = "Undefinged Value";
	strcat(undef,new);
	return undef;
}

char *table_tostring(avm_memcell *m){
	char *str = malloc(sizeof(10000));
	avm_table_bucket *tmp;
	avm_table_bucket *tmp2;
	avm_table_bucket *tmp3;
	avm_table_bucket *tmp4;
	avm_table_bucket *tmp5;
	avm_table_bucket *tmp6;
	int i;
	strcat(str,"[");
	for(i = 0; i < AVM_TABLE_HASHSIZE;i++){
		tmp = m->data.tableVal->numIndexed[i];
		tmp2 = m->data.tableVal->strIndexed[i];
		tmp3 = m->data.tableVal->tableIndexed[i];
		tmp4 = m->data.tableVal->libfuncIndexed[i];
		tmp5 = m->data.tableVal->userfuncIndexed[i];
		tmp6 = m->data.tableVal->boolIndexed[i];
		if(tmp){
			strcat(str,avm_toString(tmp->key));
			strcat(str,":");
			strcat(str,avm_toString(tmp->value));
			strcat(str,",");
		}
		if(tmp2){
			strcat(str,avm_toString(tmp2->key));
			strcat(str,":");
			strcat(str,avm_toString(tmp2->value));
			strcat(str,",");
		}
		if(tmp3){
			strcat(str,avm_toString(tmp3->key));
			strcat(str,":");
			strcat(str,avm_toString(tmp3->value));
			strcat(str,",");
		}
		if(tmp4){
			strcat(str,avm_toString(tmp4->key));
			strcat(str,":");
			strcat(str,avm_toString(tmp4->value));
			strcat(str,",");
		}
		if(tmp5){
			strcat(str,avm_toString(tmp5->key));
			strcat(str,":");
			strcat(str,avm_toString(tmp5->value));
			strcat(str,",");
		}
		if(tmp6){
			strcat(str,avm_toString(tmp6->key));
			strcat(str,":");
			strcat(str,avm_toString(tmp6->value));
			strcat(str,",");
		}
	}
	str[strlen(str) - 1] = ']';
	strcat(str,"\0");
	return str;
}

tostring_func_t tostringFuncs[] = {
	number_tostring,
	string_tostring,
	bool_tostring,
	table_tostring,
	userfunc_tostring,
	libfunc_tostring,
	nil_tostring,
	undef_tostring
};

void avm_dec_top(){
	if(!top)
		avm_error("stack overflow");		
	else
		--top;
}

void execute_call(instruction *instr){
	avm_memcell *func = avm_translate_operand(instr->result,&ax);
	avm_memcell *call;
	assert(func);
	switch(func->type){
		case userfunc_m:
			avm_callsaveenviroment();
			pc = func->data.funcVal;
			assert(pc < AVM_ENDING_PC);
			assert(code[pc].opcode == funcenter_v);
			break;

		case string_m:
			avm_callsaveenviroment();
			avm_calllibfunc(func->data.strVal);
			break;

		case libfunc_m:
			avm_callsaveenviroment();
			avm_calllibfunc(func->data.libfuncVal);
			break;

		case table_m:
			//avm_callsaveenviroment();
			call = malloc(sizeof(avm_memcell));//psaxnw to () sto table
			call->type = string_m;
			call->data.strVal = "()";

			avm_memcell *new = avm_tablegetelem(func->data.tableVal, call);
			if(!new)
				avm_error("This table doesnt have function ()");
			avm_assign(&stack[top], func);//vazw to this (table) sto top tou stack

			totalActuals++;
			avm_dec_top();
			avm_callsaveenviroment();

			pc = new->data.funcVal;
			assert(pc < AVM_ENDING_PC);
			assert(code[pc].opcode == funcenter_v);
			/*avm_tablegetelem
			kai memcell me "()"
			kai tables san indexing(me4 thesi)*/
			break;

		default: {
			char *s = avm_toString(func);
			avm_error("cannot bind to function");
			free(s);
		}
	}
}

void avm_push_envvalue(unsigned int val){
	stack[top].type = number_m;
	stack[top].data.numVal = val;
	avm_dec_top();
}

void avm_callsaveenviroment(){
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc + 1);
	avm_push_envvalue(top + totalActuals + 2);
	avm_push_envvalue(topsp);
}

userFunc *avm_getfuncinfo(unsigned int address){
	int i;
	for(i=0 ; i < totalUserFuncs ; i++){
		if(userFuncs[i].address == address)
			return &userFuncs[i];
	}
	return 0;
}

void execute_funcenter(instruction *instr){
	avm_memcell *func = avm_translate_operand(instr->result,&ax);
	assert(func);
	assert(pc == func->data.funcVal); 

	//callee actions here
	totalActuals = 0;
	userFunc *funcInfo = avm_getfuncinfo(pc);
	topsp = top;
	top = top - funcInfo->localSize;
}


unsigned int avm_get_envvalue(unsigned int i){
	unsigned val = (unsigned) stack[i].data.numVal;
	return val;
}

void execute_funcexit(instruction *unused){
	/*avm_memcell * tmp;
	int k = avm_totalactuals();
	int i;
	for(i=0;i<k;++i){
		tmp = avm_getactuals(i);
		if(tmp->type == table_m) 
			avm_tabledecrefcounter(tmp->data.tableVal);
	}
	*/
	unsigned int oldTop = top;
	top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
	pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
	topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);	

	while(oldTop++ <= top)
		avm_memcellclear(&stack[oldTop]);
}
//epistrefei to sunolo twn arguments pou edwse o xristis stin klisi
unsigned int avm_totalactuals(){
	return avm_get_envvalue(topsp+AVM_NUMACTUALS_OFFSET);
}

//epistrefei to i-osto argument
avm_memcell* avm_getactuals(unsigned i){
	assert(i<avm_totalactuals());
	return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

char *avm_toString(avm_memcell *m){
	assert(m->type>=0 && m->type<=undef_m);
	char* ret= (*tostringFuncs[m->type])(m);
	return ret;
	
}

void libfunc_print(){
	unsigned n = avm_totalactuals();
	int i;
	for(i = 0; i < n; ++i){
		char *s = avm_toString(avm_getactuals(i));
		printf("%s",s);
	}
}

void libfunc_typeof(){
	unsigned n = avm_totalactuals();
	if(n != 1)
		avm_error("One argument expected in 'typeof()'\n");
	avm_memcellclear(&retval);
	retval.type = string_m;
	retval.data.strVal = strdup(typeStrings[avm_getactuals(0)->type]);
}

void libfunc_totalarguments(){
	avm_memcellclear(&retval);
	//an top == topsp den exoume args
	if(avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET) == avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET)){
		retval.type = nil_m;
		//avm_error("Can't call 'totalarguments()' in global scope\n"); //warning
	}else{
		retval.type = number_m;
		retval.data.numVal = avm_get_envvalue(avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET) + AVM_NUMACTUALS_OFFSET);
		//epistrefei ton topsp pou deixnei stin arxi tou called stack, 
		//an prosthesoume 4 pairnoume to n = numofargs
	}		
}

void libfunc_argument(){
	avm_memcellclear(&retval);
	if(avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET) == avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET)){
		retval.type = nil_m;
		//avm_error("Can't call 'arguments()' in global scope\n");
	}else{
		//retval.type = number_m;
		unsigned n = avm_totalactuals();
		if(n != 1)
			avm_error("One argument expected in 'argument()'\n");
		else{
			if(avm_getactuals(0)->type != number_m)
				avm_error("Argument of 'argument()' must be a number\n");
			else{
				unsigned int index = avm_getactuals(0)->data.numVal;
				if(index >= avm_get_envvalue(avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET) + AVM_NUMACTUALS_OFFSET)){
					avm_error("Function calling 'argument()' doesn't have that many arguments\n");
				}else{
					avm_memcellclear(&retval);
					if(stack[topsp + AVM_NUMACTUALS_OFFSET + index].type == number_m){
						retval.type = number_m;
						retval.data.numVal = avm_get_envvalue(avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET) + AVM_NUMACTUALS_OFFSET + index);
					}else if(stack[topsp + AVM_NUMACTUALS_OFFSET + index].type == bool_m){
						retval.type = bool_m;
						retval.data.boolVal = avm_get_envvalue(avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET) + AVM_NUMACTUALS_OFFSET + index);
					}else if(stack[topsp + AVM_NUMACTUALS_OFFSET + index].type == string_m){
						retval.type = string_m;
						retval.data.strVal = strdup(stack[topsp + AVM_SAVEDTOPSP_OFFSET + AVM_NUMACTUALS_OFFSET + index].data.strVal);
					}else if(stack[topsp + AVM_NUMACTUALS_OFFSET + index].type == table_m){
						retval.type = string_m;
						retval.data.strVal = strdup(stack[topsp + AVM_SAVEDTOPSP_OFFSET + AVM_NUMACTUALS_OFFSET + index].data.strVal);;
					}else if(stack[topsp + AVM_NUMACTUALS_OFFSET + index].type == userfunc_m){
						retval.type = string_m;
						retval.data.strVal = strdup(stack[topsp + AVM_SAVEDTOPSP_OFFSET + AVM_NUMACTUALS_OFFSET + index].data.strVal);;
					}else{
						retval.type = nil_m;
					}
				}
			}
		}
	}
}

void libfunc_sqrt(){
	unsigned n = avm_totalactuals();
	if(n != 1)
		avm_error("One argument expected in 'sqrt()'\n");
	avm_memcell *m = avm_getactuals(0);
	if(m->type != number_m)
		avm_error("'sqrt()' expected a number\n");
	if(m->data.numVal < 0){
		avm_memcellclear(&retval);
		retval.type = nil_m;
		//avm_error("'sqrt()' expected a positive number\n");
	}
	else{
		avm_memcellclear(&retval);
		retval.type = number_m;
		retval.data.numVal = sqrt(m->data.numVal);
	}
}

void libfunc_cos(){
	unsigned n = avm_totalactuals();
	if(n != 1)
		avm_error("One argument expected in 'cos()'\n");
	avm_memcell *m = avm_getactuals(0);
	if(m->type != number_m)
		avm_error("'cos()' expected a number\n");
	else{
		avm_memcellclear(&retval);
		retval.type = number_m;
		unsigned degree = m->data.numVal;
		retval.data.numVal = cos(PI/180*degree);
	}
}

void libfunc_sin(){
	unsigned n = avm_totalactuals();
	if(n != 1)
		avm_error("One argument expected in 'sin()'\n");
	avm_memcell *m = avm_getactuals(0);
	if(m->type != number_m)
		avm_error("'sin()' expected a number\n");
	else{
		avm_memcellclear(&retval);
		retval.type = number_m;
		unsigned degree = m->data.numVal;
		retval.data.numVal = sin(PI/180*degree);
	}
}

void libfunc_strtonum(){
	unsigned n = avm_totalactuals();
	if(n != 1)
		avm_error("One argument expected in 'strtonum()'\n");
	avm_memcell *m = avm_getactuals(0);
	if(m->type != string_m)
		avm_error("'strtonum()' expected a string\n");
	else{
		char *str = m->data.strVal;
		float rez = 0,fact = 1;
		if(*str == '-'){
			str++;
			fact = -1;
		}
		int point_seen;
		for(point_seen = 0; *str; str++){
			if(*str == '.'){
				point_seen = 1;
				continue;
			}
			int d = *str - '0';
			if(d >= 0 && d <= 9){
				if(point_seen)
					fact /= 10.0f;
				rez = rez * 10.0f + (float)d;
			}
		}
		avm_memcellclear(&retval);
		retval.type = number_m;
		retval.data.numVal = rez * fact;
		
	}
}

void libfunc_input(){
	char str[300];
	char c;
	char * t = "true",*f = "false";
	printf("Enter a value:\n");
	fgets(str,300,stdin);
	str[strlen(str)-1] = '\0';
	int i,flag = 0,ischar = 0;
	avm_memcellclear(&retval);

	if(!(strcmp(str,t))){
		retval.type = bool_m;
		retval.data.boolVal = 1;
		return;
	}else if(!(strcmp(str,f))){
		retval.type = bool_m;
		retval.data.boolVal = 0;
		return;
	}else if(!(strcmp(str,"nil"))){
		retval.type = nil_m;
		return;
	}
	for(i = 0;i < strlen(str); i++){
		c = str[i];
		if(c < '0' || c > '9'){
			if(c == '.'){
				flag++;
			}else{
				ischar = 1;
			}
		}
		if(ischar)
			break;
	}

	if(flag <= 1 && ischar == 0){
		retval.type = number_m;
		retval.data.numVal = atof(str);
	}else if(ischar == 1){
		retval.type = string_m;
		retval.data.strVal = strdup(str);
	}
}

void libfunc_objecttotalmembers(){
	unsigned n = avm_totalactuals();
	if(n != 1)
		avm_error("One argument expected in 'objecttotalmembers'\n");

	avm_memcell *table = avm_getactuals(0);
	if(table->type != table_m)
		avm_error("'objecttotalmembers' expected table\n");

	int total = 0;
	avm_table_bucket *tmp;
	avm_table_bucket *tmp2;
	avm_table_bucket *tmp3;
	avm_table_bucket *tmp4;
	avm_table_bucket *tmp5;
	avm_table_bucket *tmp6;
	int i;
	for(i = 0; i < AVM_TABLE_HASHSIZE;i++){
		tmp = table->data.tableVal->numIndexed[i];
		tmp2 = table->data.tableVal->strIndexed[i];
		tmp3 = table->data.tableVal->libfuncIndexed[i];
		tmp4 = table->data.tableVal->userfuncIndexed[i];
		tmp5 = table->data.tableVal->boolIndexed[i];
		tmp6 = table->data.tableVal->tableIndexed[i];
		if(tmp)
			total++;
		if(tmp2)
			total++;
		if(tmp3)
			total++;
		if(tmp4)
			total++;
		if(tmp5)
			total++;
		if(tmp6)
			total++;
	}
	avm_memcellclear(&retval);
	retval.type = number_m;
	retval.data.numVal = total;
}

void libfunc_objectmemberkeys(){
	unsigned n = avm_totalactuals();
	if(n != 1)
		avm_error("One argument expected in 'totalmemberkeys'\n");

	avm_memcell *table = avm_getactuals(0);
	if(table->type != table_m)
		avm_error("'objectmemberkeys' expected table\n");

	int total = 0;
	avm_table_bucket *tmp;
	avm_table_bucket *tmp2;
	avm_memcell *index = malloc(sizeof(avm_memcell));
	int i,next = 0;
	avm_table *new = avm_tablenew();
	avm_memcellclear(&retval);
	retval.type = table_m;
	retval.data.tableVal = new;
	for(i = 0; i < AVM_TABLE_HASHSIZE;i++){
		tmp = table->data.tableVal->numIndexed[i];
		tmp2 = table->data.tableVal->strIndexed[i];
		if(tmp){
			index = malloc(sizeof(avm_memcell));
			index->type = number_m;
			index->data.numVal = next;
			avm_tablesetelem(new,index,tmp->key);
			next++;
		}
		if(tmp2){
			index = malloc(sizeof(avm_memcell));
			index->type = number_m;
			index->data.numVal = next;
			avm_tablesetelem(new,index,tmp2->key);
			next++;
		}//pws tha paroume to onoma twn tables apo to tableIndexed?
	}
}

void libfunc_objectcopy(){
	unsigned n = avm_totalactuals(); //ta total acrtuals ths objectcopy
	if(n != 1)
		avm_error("One argument expected in 'totalmemberkeys'\n");

	avm_memcell *table = avm_getactuals(0);
	if(table->type != table_m)
		avm_error("'totalmemberkeys' expected table\n");

	avm_table_bucket *tmp;
	avm_table_bucket *tmp2;
	avm_table_bucket *tmp3;
	avm_table_bucket *tmp4;
	avm_table_bucket *tmp5;
	avm_table_bucket *tmp6;
	avm_memcell *index = malloc(sizeof(avm_memcell));

	avm_table *new = avm_tablenew();
	avm_memcellclear(&retval);
	retval.type = table_m;
	retval.data.tableVal = new;

	int i;
	for(i = 0; i < AVM_TABLE_HASHSIZE;i++){
		tmp = table->data.tableVal->numIndexed[i];
		tmp2 = table->data.tableVal->strIndexed[i];
		tmp3 = table->data.tableVal->tableIndexed[i];
		tmp4 = table->data.tableVal->libfuncIndexed[i];
		tmp5 = table->data.tableVal->userfuncIndexed[i];
		tmp6 = table->data.tableVal->boolIndexed[i];
		if(tmp){
			index = malloc(sizeof(avm_memcell));
			index->type = number_m;
			index->data.numVal = tmp->key->data.numVal;
			avm_tablesetelem(new,index,tmp->value);
		}
		if(tmp2){
			index = malloc(sizeof(avm_memcell));
			index->type = string_m;
			index->data.strVal = strdup(tmp2->key->data.strVal);
			avm_tablesetelem(new,index,tmp2->value);
		}
		if(tmp3){
			index = malloc(sizeof(avm_memcell));
			index->type = table_m;
			index->data.tableVal = tmp3->key->data.tableVal;
			avm_tablesetelem(new,index,tmp3->value);
		}
		if(tmp4){
			index = malloc(sizeof(avm_memcell));
			index->type = libfunc_m;
			index->data.libfuncVal = strdup(tmp4->key->data.libfuncVal);
			avm_tablesetelem(new,index,tmp4->value);
		}
		if(tmp5){
			index = malloc(sizeof(avm_memcell));
			index->type = userfunc_m;
			index->data.funcVal = tmp5->key->data.funcVal;
			avm_tablesetelem(new,index,tmp5->value);
		}
		if(tmp6){
			index = malloc(sizeof(avm_memcell));
			index->type = bool_m;
			index->data.boolVal = tmp6->key->data.boolVal;
			avm_tablesetelem(new,index,tmp6->value);
		}
	}
}

void avm_calllibfunc(char *id){
	totalActuals = 0;
    topsp = top;
     
    if(!strcmp(id,"print")){
            libfunc_print();
    }
    else if(!strcmp(id,"typeof")){
            libfunc_typeof();
    }
    else if(!strcmp(id,"totalarguments")){
        libfunc_totalarguments();
    }
    else if(!strcmp(id,"input")){
            libfunc_input();
    }
    else if(!strcmp(id,"objectmemberkeys")){
        libfunc_objectmemberkeys();
    }
    else if(!strcmp(id,"objecttotalmembers")){
        libfunc_objecttotalmembers();
    }
    else if(!strcmp(id,"objectcopy")){
        libfunc_objectcopy();
    }
    else if(!strcmp(id,"argument")){
        libfunc_argument();
    }
    else if(!strcmp(id,"strtonum")){
        libfunc_strtonum();
    }
    else if(!strcmp(id,"sqrt")){
        libfunc_sqrt();
    }
    else if(!strcmp(id,"cos")){
        libfunc_cos();
    }
    else if(!strcmp(id,"sin")){
        libfunc_sin();
    }
    else {
    	char *s = malloc(1000*(sizeof(char)));
    	strcat(s,"Unsupported lib func called!: ");
    	strcat(s,id);
        avm_error(s);
    }
 
    if(!executionFinished){
        execute_funcexit((instruction*)0);
    }
}

void execute_pusharg(instruction *instr){
	avm_memcell *arg = avm_translate_operand(instr->arg1,&ax);
	assert(arg);
	avm_assign(&stack[top], arg);
	++totalActuals;
	avm_dec_top();
}

void execute_ret(instruction* i){
	assert(0);
}

void execute_getretval(instruction* i){
	assert(0);
}