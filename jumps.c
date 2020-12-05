#include "avm.h"

typedef unsigned int (*tobool_func_t) (avm_memcell*);
typedef int (*cmp_func) (double, double);

int jle_impl(double x, double y){ return x<=y; }
int jge_impl(double x, double y){ return x>=y; }
int jlt_impl(double x, double y){ return x<y; }
int jgt_impl(double x, double y){ return x>y; }

cmp_func cmpFuncs[] ={
	jle_impl,
	jge_impl,
	jlt_impl,
	jgt_impl
};

unsigned int number_tobool(avm_memcell* m){
	return m->data.numVal != 0;
}

unsigned int string_tobool(avm_memcell* m){
	return m->data.strVal[0] != 0;
}

unsigned int bool_tobool(avm_memcell* m){
	return m->data.boolVal;
}

unsigned int table_tobool(avm_memcell* m){
	return 1;
}

unsigned int userfunc_tobool(avm_memcell* m){
	return 1;
}

unsigned int libfunc_tobool(avm_memcell* m){
	return 1;
}

unsigned int nil_tobool(avm_memcell* m){
	return 0;
}
	
unsigned int undef_tobool(avm_memcell* m){
	assert(0);
	return 0;
}

tobool_func_t toboolFuncs[]={
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool
};

unsigned int avm_tobool(avm_memcell *m){
	assert(m->type>=0 && m->type <undef_m);
	return (*toboolFuncs[m->type])(m);
}

void execute_jump(instruction* i){
	pc = i->result->value;
}

void execute_jeq(instruction *i){

	assert(i->result->type == label_a);

	avm_memcell* rv1 = avm_translate_operand(i->arg1,&ax);
	avm_memcell* rv2 = avm_translate_operand(i->arg2,&bx);

	unsigned int result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		/*avm_error*/printf("'undef' involved in equality!\n");
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type==nil_m && rv2->type==nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		printf("%s == %s is illegal!",typeStrings[rv1->type],typeStrings[rv2->type]);
		avm_error("");
	}
	else{
		
		if(rv1->type == number_m){
			if(rv1->data.numVal == rv2->data.numVal)
				result = 1;
			else
				result = 0;	
		}
		else if(rv1->type == string_m){
			if(!(strcmp(rv1->data.strVal,rv2->data.strVal)))
				result = 1;
			else
				result = 0;	
		}
 		else if(rv1->type == table_m){
 			if(rv1->data.tableVal == rv2->data.tableVal)
				result = 1;
			else
				result = 0; 	
		}
 		else if(rv1->type == userfunc_m){
 			if(rv1->data.funcVal == rv2->data.funcVal)
				result = 1;
			else
				result = 0;			
		}
 		else if(rv1->type == libfunc_m){
 			if(!(strcmp(rv1->data.libfuncVal,rv2->data.libfuncVal)))
				result = 1;
			else
				result = 0;		
		}
		else
			assert(0);
	}

	if(!executionFinished && result){
		pc = i->result->value;
	}
}
void execute_jne(instruction* i){
	assert(i->result->type == label_a);

	avm_memcell* rv1 = avm_translate_operand(i->arg1,&ax);
	avm_memcell* rv2 = avm_translate_operand(i->arg2,&bx);

	unsigned int result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type==nil_m && rv2->type==nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		printf("%s == %s is illegal!",typeStrings[rv1->type],typeStrings[rv2->type]);
		avm_error("");
	}
	else{
		
		if(rv1->type == number_m){
			if(rv1->data.numVal == rv2->data.numVal)
				result = 1;
			else
				result = 0;	
		}
		else if(rv1->type == string_m){
			if(!(strcmp(rv1->data.strVal,rv2->data.strVal)))
				result = 1;
			else
				result = 0;	
		}
 		else if(rv1->type == table_m){
 			if(rv1->data.tableVal == rv2->data.tableVal)
				result = 1;
			else
				result = 0; 	
		}
 		else if(rv1->type == userfunc_m){
 			if(rv1->data.funcVal == rv2->data.funcVal)
				result = 1;
			else
				result = 0;			
		}
 		else if(rv1->type == libfunc_m){
 			if(!(strcmp(rv1->data.libfuncVal,rv2->data.libfuncVal)))
				result = 1;
			else
				result = 0;		
		}
		else
			assert(0);
	}

	if(!executionFinished && result){
		pc = i->result->value;
	}
}
void execute_lgjump(instruction* i){
	avm_memcell* rv1 = avm_translate_operand(i->arg1,&ax);
	avm_memcell* rv2 = avm_translate_operand(i->arg2,&bx);
	unsigned int result = 0;
	assert(rv1 && rv2);
	if (rv1->type !=number_m || rv2->type !=number_m ){
		avm_error("not an number on arithmetic statement!\n");
		//executionFinished = 1;
	}
	else{
		cmp_func op = cmpFuncs[i->opcode - jle_v];
		result = (*op)(rv1->data.numVal,rv2->data.numVal);
	}
	if(result && !executionFinished){
		assert(i->result->type == label_a);
		pc = i->result->value;
	}
}
void execute_jle(instruction* i){
   	execute_lgjump(i);
}

void execute_jge(instruction* i){
	execute_lgjump(i);
}

void execute_jlt(instruction* i){
	execute_lgjump(i);
}

void execute_jgt(instruction* i){
	execute_lgjump(i);
}

