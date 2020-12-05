#include "avm.h"

typedef double (*arithmetic_func_t)(double x, double y);

double add_impl(double x, double y){ return x+y; }

double sub_impl(double x, double y){ return x-y; }

double mul_impl(double x, double y){ return x*y; }

double div_impl(double x, double y){ 
	if(y == 0)
		avm_error("Cannot divide with 0\n");
	return x/y; 
}

double mod_impl(double x, double y){ 
	if(y == 0)
		avm_error("Cannot divide with 0\n");
	return ((unsigned int)x % (unsigned int)y); 
}

arithmetic_func_t arithmeticFuncs[] = {
	add_impl,
	sub_impl,
	mul_impl,
	div_impl,
	mod_impl
};

void execute_arithmetic (instruction* instr){
	avm_memcell* lv  = avm_translate_operand(instr->result,NULL);
	avm_memcell* rv1 = avm_translate_operand(instr->arg1,&ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2,&bx);

	//assert(lv && (&stack[0]<=lv && &stack[top]>lv || lv==&retval));
	assert(rv1 && rv2);

	/*add string case*/
	if (rv1->type !=number_m || rv2->type !=number_m ){
		avm_error("not a number arithmetic!\n");
		executionFinished = 1;
	}
	else{
		arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
		avm_memcellclear(lv);
		lv->type = number_m;
		lv->data.numVal = (*op)(rv1->data.numVal,rv2->data.numVal);
	}
}

void execute_add(instruction *i){
	execute_arithmetic(i);
}
void execute_sub(instruction *i){
	execute_arithmetic(i);
}
void execute_mul(instruction *i){
	execute_arithmetic(i);
}
void execute_div(instruction *i){
	execute_arithmetic(i);
}
void execute_mod(instruction *i){
	execute_arithmetic(i);
}