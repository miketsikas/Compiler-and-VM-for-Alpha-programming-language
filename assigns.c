#include <unistd.h>
#include "avm.h"

void avm_assign(avm_memcell *lv, avm_memcell *rv){
	if(lv == rv)
		return;
	
	if( lv->type == table_m &&
		rv->type == table_m &&
		lv->data.tableVal == rv->data.tableVal)
		return;

	if(rv->type == undef_m) 
		avm_warning("assigning from 'undef' content!\n");

	avm_memcellclear(lv);
	memcpy(lv,rv,sizeof(avm_memcell));

	if(lv->type == string_m)
		lv->data.strVal = strdup(rv->data.strVal);
	else if(lv->type == table_m)
		avm_tableincrefcounter(lv->data.tableVal);
}

void execute_assign(instruction *instr){
	avm_memcell *lv = avm_translate_operand(instr->result,NULL);
	avm_memcell *rv = avm_translate_operand(instr->arg1,&ax);
	assert(lv && (&stack[0] <= lv || lv == &retval));
	avm_assign(lv,rv);
}