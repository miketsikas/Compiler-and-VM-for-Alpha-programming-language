#include <assert.h>
#include "avm.h"

avm_table *avm_tablenew(){
    avm_table *t = (avm_table*) malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);
    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);
    avm_tablebucketsinit(t->tableIndexed);
    avm_tablebucketsinit(t->libfuncIndexed);
    avm_tablebucketsinit(t->userfuncIndexed);
    avm_tablebucketsinit(t->boolIndexed);
    return t;
}

void avm_tableincrefcounter(avm_table* t)   { ++t->refCounter; }

/* automatic garbage collection for tables when refCounter gets 0 */
void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter >= 0);
    if(!--t->refCounter){
        avm_tabledestroy(t);
    }
}

void avm_tablebucketsinit(avm_table_bucket **p){
    for(unsigned i=0; i< AVM_TABLE_HASHSIZE; ++i){
        p[i] = (avm_table_bucket*) 0;
    }
}

void avm_tablebucketsdestroy(avm_table_bucket** p){

    for(unsigned i=0; i<AVM_TABLE_HASHSIZE; ++i,++p){
        for(avm_table_bucket* b = *p; b;){
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(del->key);
            avm_memcellclear(del->value);
            free(del);
        }
        p[i] = (avm_table_bucket*) 0;
    }
}

void avm_tabledestroy(avm_table *t){
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
    free(t);
}


void execute_newtable(instruction *instr){
    avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell*) 0);
    //assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && lv > &stack[top] || lv == &retval));

    avm_memcellclear(lv);

    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}

unsigned long hashfunc(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%AVM_TABLE_HASHSIZE;
}

avm_memcell *getIndexed(avm_table_bucket* array[],avm_memcell *index){
	int i;
	avm_memcell *toret = NULL;
	for(i = 0;i < AVM_TABLE_HASHSIZE; i++){
		if(array[i] && array[i]->value->type == table_m){
			toret = avm_tablegetelem(array[i]->value->data.tableVal,index);
			if(toret) break;
		}
	}
	return toret;
}
avm_memcell *whichIndex(avm_table *table,avm_memcell *index){
	avm_memcell *toret = NULL;
	toret = getIndexed(table->numIndexed,index);
	if(toret) return toret;
	toret = getIndexed(table->strIndexed,index);
	if(toret) return toret;
	toret = getIndexed(table->libfuncIndexed,index);
	if(toret) return toret;
	toret = getIndexed(table->userfuncIndexed,index);
	if(toret) return toret;
	toret = getIndexed(table->boolIndexed,index);
	if(toret) return toret;
	toret = getIndexed(table->tableIndexed,index);
	if(toret) return toret;
}

avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* index){
    if(index->type == number_m){
        avm_table_bucket *tmp = table->numIndexed[(int)index->data.numVal%AVM_TABLE_HASHSIZE];
        if(tmp)
            return tmp->value;
        else{
            return whichIndex(table,index);
        }
    }else if(index->type == string_m){
        unsigned int i = hashfunc(index->data.strVal);
        avm_table_bucket *tmp = table->strIndexed[i];
        if(tmp)
            return tmp->value;
        else
        	return whichIndex(table,index);
    }else if(index->type == table_m){
        unsigned int i = ((unsigned int)index->data.tableVal)%AVM_TABLE_HASHSIZE;
        avm_table_bucket *tmp = table->tableIndexed[i];
        if(tmp){ 
            //tmp->value = avm_tablegetelem(tmp->value->data.tableVal,index);
            return tmp->value;
        }else{
        	return whichIndex(table,index);
        }    
    }else if(index->type == libfunc_m){
        unsigned int i = hashfunc(index->data.libfuncVal);
        avm_table_bucket *tmp = table->libfuncIndexed[i];

        if(tmp) 
            return tmp->value;
        else
            return whichIndex(table,index);
    }else if(index->type == userfunc_m){
        avm_table_bucket *tmp = table->userfuncIndexed[(int)index->data.funcVal%AVM_TABLE_HASHSIZE];
        if(tmp)
            return tmp->value;
        else{
        	return whichIndex(table,index);
        }
    }else if(index->type == bool_m){
        avm_table_bucket *tmp = table->boolIndexed[(int)index->data.boolVal%AVM_TABLE_HASHSIZE];
        if(tmp)
            return tmp->value;
        else{
        	return whichIndex(table,index);
        }
    }
    return NULL;
}

void setContext(avm_memcell *index, avm_memcell *content, avm_table_bucket *new){
    
    switch(index->type){
        case(number_m):{
            new->key->type = number_m;
            new->key->data.numVal = index->data.numVal;
            break;
        }case(string_m):{
            new->key->type = string_m;
            new->key->data.strVal = strdup(index->data.strVal);
            break;
        }case(table_m):{
            new->key->type = table_m;
            new->key->data.tableVal = index->data.tableVal;
            break;
        }case(libfunc_m):{
            new->key->type = libfunc_m;
            new->key->data.libfuncVal = strdup(index->data.libfuncVal);
            break;
        }case(userfunc_m):{
            new->key->type = userfunc_m;
            new->key->data.funcVal = index->data.funcVal;
            break;
        }case(bool_m):{
            new->key->type = bool_m;
            new->key->data.boolVal = index->data.boolVal;
            break;
        }default:{
            avm_error("None of the known types for tablesetelem\n");
            break;
        }
    }

    switch(content->type){
        case(number_m):{
            new->value->type = number_m;
            new->value->data.numVal = content->data.numVal;
            break;
        }case(string_m):{
            new->value->type = string_m;
            new->value->data.strVal = strdup(content->data.strVal);
            break;
        }case(bool_m):{
            new->value->type = bool_m;
            new->value->data.boolVal = content->data.boolVal;
            break;
        }case(table_m):{
            new->value->type = table_m;
            new->value->data.tableVal = content->data.tableVal;
            break;
        }case(userfunc_m):{
            new->value->type = userfunc_m;
            new->value->data.funcVal = content->data.funcVal;
            break;
        }case(libfunc_m):{
            new->value->type = libfunc_m;
             new->value->data.libfuncVal = strdup(content->data.libfuncVal);
            break;
        }case(nil_m):{
            new->value->type = nil_m;
            break;
        }
        case(undef_m):{
            new->value->type = undef_m;
            break;
        }
        default:{
            avm_error("None of the known types for tablesetelem\n");
            break;
        }
    }
}

void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content){
    avm_table_bucket *new;
    if(index->type == number_m){
        table->numIndexed[(int)index->data.numVal%AVM_TABLE_HASHSIZE] = malloc(sizeof(avm_table_bucket));
        new = table->numIndexed[(int)index->data.numVal%AVM_TABLE_HASHSIZE];
        new->next = NULL;
        new->key = malloc(sizeof(avm_memcell));
        new->value = malloc(sizeof(avm_memcell));
        setContext(index,content,new);

    }else if(index->type == string_m){
        unsigned int i = hashfunc(index->data.strVal);
        table->strIndexed[i] = malloc(sizeof(avm_table_bucket));
        new = table->strIndexed[i];
        new->next = NULL;
        new->key = malloc(sizeof(avm_memcell));
        new->value = malloc(sizeof(avm_memcell));
        setContext(index,content,new);
    }else if(index->type == table_m){
        unsigned int i = (unsigned int)index->data.tableVal%AVM_TABLE_HASHSIZE;
        table->tableIndexed[i] = malloc(sizeof(avm_table_bucket));
        new = table->tableIndexed[i];
        new->next = NULL;
        new->key = malloc(sizeof(avm_memcell));
        new->value = malloc(sizeof(avm_memcell));
        setContext(index,content,new);
    }else if(index->type == libfunc_m){
        unsigned int i = hashfunc(index->data.libfuncVal);
        table->libfuncIndexed[i] = malloc(sizeof(avm_table_bucket));
        new = table->libfuncIndexed[i];
        new->next = NULL;
        new->key = malloc(sizeof(avm_memcell));
        new->value = malloc(sizeof(avm_memcell));
        setContext(index,content,new);
    }else if(index->type == userfunc_m){
        table->userfuncIndexed[(int)index->data.funcVal%AVM_TABLE_HASHSIZE] = malloc(sizeof(avm_table_bucket));
        new = table->userfuncIndexed[(int)index->data.funcVal%AVM_TABLE_HASHSIZE];
        new->next = NULL;
        new->key = malloc(sizeof(avm_memcell));
        new->value = malloc(sizeof(avm_memcell));
        setContext(index,content,new);
    }else if(index->type == bool_m){
        table->boolIndexed[(int)index->data.boolVal%AVM_TABLE_HASHSIZE] = malloc(sizeof(avm_table_bucket));
        new = table->boolIndexed[(int)index->data.boolVal%AVM_TABLE_HASHSIZE];
        new->next = NULL;
        new->key = malloc(sizeof(avm_memcell));
        new->value = malloc(sizeof(avm_memcell));
        setContext(index,content,new);
    }else{
         //printf("aaaa%s\n",typeStrings[index->type]);
        avm_error("Not a number,string or table for indexing\n");
    }
}

void execute_tablegetelem(instruction *instr){

    avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell *t = avm_translate_operand(instr->arg1, (avm_memcell*) 0);
    avm_memcell *i = avm_translate_operand(instr->arg2, &ax);

    //assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && lv > &stack[top] || lv == &retval));
    //assert(t && &stack[AVM_STACKSIZE-1] >= t && t > &stack[top]);
    //assert(i);

    avm_memcellclear(lv);
    lv->type = nil_m;

    if(t->type != table_m){
        char *error;
        sprintf(error, "illegal use of type %s as table\n", typeStrings[t->type]);
        avm_error(error);
    }else{
        avm_memcell *content = avm_tablegetelem(t->data.tableVal, i);
        if(content && content != 51)
            avm_assign(lv, content);
        else{
            char *ts = avm_toString(t);
            char *is = avm_toString(i);
            char *warning;
            sprintf(warning, "Did not find %s in %s\n", is,ts);
            avm_warning(warning);
            free(ts);
            free(is);
        }
    }
}

void execute_tablesetelem(instruction *instr){

    avm_memcell *t = avm_translate_operand(instr->arg1, (avm_memcell*) 0); // na ta allaksw meta
    avm_memcell *i = avm_translate_operand(instr->arg2, &ax);
    avm_memcell *c = avm_translate_operand(instr->result, &bx);

    assert(t && &stack[AVM_STACKSIZE-1] >= t && t > &stack[top]);
    assert(i && c);

    if(t->type != table_m){
        char *error;
        sprintf(error, "illegal use of type %s as table\n", typeStrings[t->type]);
        avm_error(error);
    }else{
        avm_tablesetelem(t->data.tableVal,i,c);
    }
}