#include "tcode.h"

#define CURR_SIZE (totalInstr*sizeof(instruction))
#define NEW_SIZE (EXPAND_SIZE*sizeof(instruction)+CURR_SIZE)

unsigned int magic_number = 340200501;

instruction *instructions = (instruction*) 0;
unsigned totalInstr = 0;
unsigned currInstr = 0;

unsigned processedQuads = 0;

incomplete_jump* ij_head = (incomplete_jump*) 0;
unsigned ij_total = 0;

funcstack *fstack = (funcstack*) 0; //top

generator_func_t generators[] = {
	generate_ADD ,
   	generate_SUB ,
   	generate_MUL ,
   	generate_DIV ,
  	generate_MOD ,
    generate_NEWTABLE ,
    generate_TABLEGETELEM ,
    generate_TABLESETELEM ,
    generate_ASSIGN ,
    generate_NOP ,
	generate_UMINUS ,
	generate_AND,
	generate_OR ,
	generate_NOT ,
	generate_IF_EQ ,
	generate_IF_NOTEQ ,	
	generate_IF_LESSEQ ,
	generate_IF_GREATEREQ ,
	generate_IF_LESS ,
	generate_IF_GREATER ,
    generate_PARAM ,
	generate_CALL ,
	generate_RETURN ,
	generate_GETRETVAL ,
	generate_FUNCSTART ,
	generate_FUNCEND ,
	generate_JUMP
};

void InitFuncStack(){
    fstack = malloc(sizeof(funcstack));
    fstack->next = NULL;
}

void pushFuncStack(Node_T sym){

    funcstack *tmp = malloc(sizeof(funcstack));
    tmp->funcSym = sym;
    tmp->line = nextInstructionLabel()-1;
    tmp->rlist= NULL;
    tmp->next = NULL;
    if(fstack == NULL){
        fstack = tmp;
        fstack->next = NULL;
    }else{
        tmp->next = fstack;
        fstack = tmp;
    }
}

funcstack *popFuncStack(){
    funcstack *tmp = fstack;
    fstack = fstack->next;
    return tmp;
}

/* eisagoume to label tou (t-code) jump sth returnList ths synartisis
   pou vrisketai stin koryfi tis stoivas  */
void appendFuncStack(returnList *rlist, unsigned label){
    returnList *tmp = malloc(sizeof(returnList));
	tmp->label = label;
	if(rlist == NULL)
		tmp->next = NULL;
	else
		tmp->next = rlist;
	rlist = tmp;
}

/* patch ta target labels twn jump sti returnList */
void backpatch(funcstack *f, unsigned int label){
    returnList *tmp = f->rlist;
    while(tmp){
        instructions[tmp->label].result->value = label;
        tmp = tmp->next;
    }
}

int nextInstructionLabel(){
    return currInstr;
}

void expandInstructions(){
    assert(totalInstr == currInstr);
    instruction* newExpandedArray = (instruction*) malloc(NEW_SIZE);
    if (instructions){
        memcpy(newExpandedArray, instructions, CURR_SIZE);
        free(instructions);
    }
    instructions = newExpandedArray;
    totalInstr += EXPAND_SIZE;
}

instruction* newInstr(){ 
    instruction* new = (instruction*) malloc(sizeof(instruction));
    memset(new,0,sizeof(instruction));
    return new;
}

void emitInstruction(instruction *t){
    instruction* new = newInstr();

    if (currInstr == totalInstr){
        expandInstructions();
    }
    /* me arithmitiki deiktwn paw sto curr 
    instruction to opoio exei ginei malloced 
    kai menei na arxikopoihthei */
    new = instructions + currInstr++;

    new->opcode = t->opcode;
    new->arg1 = t->arg1;
    new->arg2 = t->arg2;
    new->result = t->result;
    new->srcLine = t->srcLine; 
    return;
}

void make_operand(expr* e ,vmarg *arg){
	if(!e){
		arg = NULL;
		return;
	}
	switch(e->type) {
		case var_e :
		case tableitem_e :
		case arithexpr_e :
		case boolexpr_e :
		case assignexpr_e:
		case newtable_e : {

			assert(e->sym);
			arg->value = e->sym->offset;

			switch (e->sym->space) {
				case programvar: arg->type = global_a; break;
				case functionlocal: arg->type = local_a;	break;
				case formalarg: arg->type = formal_a;	break;
				default: assert(0);
			}
			break;
		}
        /* Constants */
		case constbool_e : {
			if(e->boolConst == '0')
				arg->value = 0;
			else if(e->boolConst == '1')
				arg->value = 1;
			arg->type = bool_a;
			break;
		}

		case conststring_e : {
			arg->value = consts_newstring(e->strConst);
			arg->type = string_a;
			break;
		}

		case constnum_e : {
            //make_numberoperand(arg, e->numConst);
			arg->value = consts_newnumber(e->numConst);
			arg->type = number_a;
			break;
		}

        case nil_e : {
            arg->type = nil_a;
            break;
        }

		case programfunc_e : {
			arg->type = userfunc_a;
            //arg->value = userfuncs_newfunc(e->sym);
			break;
		}
		case libraryfunc_e : {
			arg->type = libfunc_a;
			arg->value = libfuncs_newused(e->sym->name);
			break;
		}

		default : 
            assert(e);
            assert(e->sym);
            printf("UNKNOWN EXPRESSION TYPE : %d %s %d\n", e->sym->offset,e->sym->name,e->sym->taddress);
            assert(0);
	}
}

void make_numberoperand(vmarg* arg, double value){
	arg->value = consts_newnumber(value);
	arg->type = number_a;
}

void make_booloperand (vmarg* arg, unsigned value){
	arg->value = value;
	arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){
	arg->type = retval_a;
}

void reset_operand(vmarg *arg){ arg = NULL; }

void patch_incomplete_jump() {
    incomplete_jump* tmp;
    for(tmp = ij_head; tmp != NULL; tmp = tmp->next) {
        if (tmp->iaddress == currQuad) 
            instructions[tmp->instrNo].result->value = nextInstructionLabel(); /* 1-1 me t-code */
        else
            instructions[tmp->instrNo].result->value = quads[tmp->iaddress].taddress;
    }
}

/* jump label of i-code -> jump label of t-code */
void add_incomplete_jump(unsigned instructionlabel, unsigned quadlabel){
    incomplete_jump *ij = malloc(sizeof(incomplete_jump));
	ij->instrNo = instructionlabel;
	ij->iaddress = quadlabel;
	if(!ij_head)
		ij->next = NULL;
	else
		ij->next = ij_head;
	ij_head = ij;
}

void generate (vmopcode op, quad* quad) {
    instruction *t = newInstr();
    t->opcode = op;
    if(quad->arg1){
		t->arg1 = malloc(sizeof(vmarg));
		make_operand(quad->arg1 , t->arg1);
	}else reset_operand(t->arg1);

    if(quad->arg2){
		t->arg2 = malloc(sizeof(vmarg));
		make_operand(quad->arg2 , t->arg2);
	}else reset_operand(t->arg2);

    if(quad->result){
		t->result = malloc(sizeof(vmarg));
		make_operand(quad->result , t->result);
	}else reset_operand(t->result);

    t->srcLine = quad->line;
    quad->taddress = nextInstructionLabel();
    emitInstruction(t);
}
void generate_ADD (quad* quad){ generate(add_v, quad); }

void generate_SUB (quad* quad){ generate(sub_v, quad); }

void generate_MUL (quad* quad){ generate(mul_v, quad); }

void generate_DIV (quad* quad){ generate(div_v, quad); }

void generate_MOD (quad* quad){ generate(mod_v, quad); }

void generate_NEWTABLE (quad* quad){ 
    //generate(newtable_v, quad);   
    instruction *t = newInstr();
    t->opcode = newtable_v;
    t->result = malloc(sizeof(vmarg));
    make_operand(quad->arg1, t->result);
    quad->taddress = nextInstructionLabel();
    reset_operand(t->arg1);
    reset_operand(t->arg2);
    emitInstruction(t);
}

void generate_TABLEGETELEM (quad* quad){ generate(tablegetelem_v, quad); }

void generate_TABLESETELEM (quad* quad){ generate(tablesetelem_v, quad); }

void generate_ASSIGN (quad* quad){ generate(assign_v, quad); }

void generate_NOP (){ 
    instruction *t = newInstr(); 
    t->opcode = nop_v; 
    emitInstruction(t); 
}

void generate_relational (vmopcode op, quad* quad){
    instruction *t = newInstr();

    t->opcode = op;
    if(quad->arg1){
        t->arg1 = malloc(sizeof(vmarg));
        make_operand(quad->arg1, t->arg1);
    }else reset_operand(t->arg1);
    
    if(quad->arg2){
        t->arg2 = malloc(sizeof(vmarg));
        make_operand(quad->arg2, t->arg2);
    }else reset_operand(t->arg2);

    t->result = malloc(sizeof(vmarg));
    t->result->type = label_a;
    if (quad->label < processedQuads){
        t->result->value = quads[quad->label].taddress;
    }else{
        add_incomplete_jump(nextInstructionLabel(), quad->label);
    }
    quad->taddress = nextInstructionLabel();
    emitInstruction(t);
}

void generate_JUMP (quad* quad){ generate_relational(jump_v, quad); }
void generate_IF_EQ (quad* quad){ generate_relational(jeq_v, quad); }
void generate_IF_NOTEQ(quad* quad){ generate_relational(jne_v, quad); }
void generate_IF_GREATER (quad* quad){ generate_relational(jgt_v, quad); }
void generate_IF_GREATEREQ(quad* quad){ generate_relational(jge_v, quad); }
void generate_IF_LESS (quad* quad){ generate_relational(jlt_v, quad); }
void generate_IF_LESSEQ (quad* quad){ generate_relational(jle_v, quad); }

void generate_UMINUS (quad* quad){

    instruction *t = newInstr();
    t->opcode = mul_v;
    t->arg1 = malloc(sizeof(vmarg));
    t->arg2 = malloc(sizeof(vmarg));
    t->result = malloc(sizeof(vmarg));

    make_operand(quad->arg1, t->arg1);
    make_operand(quad->result, t->result);

    /* to arg2 tha einai -1 */
    t->arg2->type = number_a;
    t->arg2->value = -1;

    t->srcLine = quad->line;
    quad->taddress = nextInstructionLabel();
    emitInstruction(t);
}

void generate_NOT (quad* quad){

    quad->taddress = nextInstructionLabel();
    instruction *t = newInstr();
    t->arg1 = malloc(sizeof(vmarg));
    t->arg2 = malloc(sizeof(vmarg));
    t->result = malloc(sizeof(vmarg));

    t->opcode = jeq_v;
    make_operand(quad->arg1, t->arg1);
    make_booloperand(t->arg2, 0); //false
    t->result->type = label_a;
    t->result->value = nextInstructionLabel()+3;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(t->arg1, 0);
    reset_operand(t->arg2);
    make_operand(quad->result, t->result);
    emitInstruction(t);

    t->opcode = jump_v;
    reset_operand (t->arg1);
    reset_operand(t->arg2);
    t->result->type = label_a;
    t->result->value = nextInstructionLabel()+2;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(t->arg1, 1); //true
    reset_operand(t->arg2);
    make_operand(quad->result, t->result);
    emitInstruction(t);
}

void generate_OR (quad* quad){

    quad->taddress = nextInstructionLabel();
    instruction *t = newInstr();
    t->arg1 = malloc(sizeof(vmarg));
    t->arg2 = malloc(sizeof(vmarg));
    t->result = malloc(sizeof(vmarg));

    t->opcode = jeq_v;
    make_operand(quad->arg1, t->arg1);
    make_booloperand(t->arg2, 1);
    t->result->type = label_a;
    t->result->value = nextInstructionLabel()+4;
    emitInstruction(t);

    make_operand(quad->arg2, t->arg1);
    t->result->value = nextInstructionLabel()+3;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(t->arg1, 0);
    reset_operand(t->arg2);
    make_operand(quad->result, t->result);
    emitInstruction(t);

    t->opcode = jump_v;
    reset_operand (t->arg1);
    reset_operand(t->arg2);
    t->result->type = label_a;
    t->result->value = nextInstructionLabel()+2;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(t->arg1, 1);
    reset_operand(t->arg2);
    make_operand(quad->result, t->result);
    emitInstruction(t);
}

void generate_AND (quad* quad){

    quad->taddress = nextInstructionLabel();
    instruction *t = newInstr();
    t->arg1 = malloc(sizeof(vmarg));
    t->arg2 = malloc(sizeof(vmarg));
    t->result = malloc(sizeof(vmarg));

    t->opcode = jeq_v;
    make_operand(quad->arg1, t->arg1);
    make_booloperand(t->arg2, 0);
    t->result->type = label_a;
    t->result->value = nextInstructionLabel()+4;
    emitInstruction(t);

    make_operand(quad->arg2, t->arg1);
    t->result->value = nextInstructionLabel()+3;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(t->arg1, 1);
    reset_operand(t->arg2);
    make_operand(quad->result, t->result);
    emitInstruction(t);

    t->opcode = jump_v;
    reset_operand (t->arg1);
    reset_operand(t->arg2);
    t->result->type = label_a;
    t->result->value = nextInstructionLabel()+2;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(t->arg1, 0);
    reset_operand(t->arg2);
    make_operand(quad->result, t->result);
    emitInstruction(t);
}

void generate_PARAM(quad* quad) {
    quad->taddress = nextInstructionLabel();
    instruction *t = newInstr();
    t->arg1 = malloc(sizeof(vmarg));
    t->opcode = pusharg_v;
    make_operand(quad->arg1, t->arg1);
    emitInstruction(t);
}

void generate_CALL(quad* quad) {
    quad->taddress = nextInstructionLabel();
    instruction *t = newInstr();
    t->arg1 = malloc(sizeof(vmarg));
    t->opcode = call_v;
    make_operand(quad->arg1, t->arg1);
    emitInstruction(t);
}

void generate_GETRETVAL(quad* quad) {
    quad->taddress = nextInstructionLabel();
    instruction *t = newInstr();
    t->result = malloc(sizeof(vmarg));
    t->opcode = getretval_v; // assign_v ??
    make_operand(quad->arg1, t->result);
    t->arg1 = malloc(sizeof(vmarg));
    make_retvaloperand(t->arg1);
    emitInstruction(t);
}

void generate_FUNCSTART(quad* quad){

    Node_T sym = malloc(sizeof(struct node));
    sym = quad->arg1->sym; // arg1 oxi result !!!!!
    sym->taddress = nextInstructionLabel();
    quad->taddress = nextInstructionLabel();

    userfuncs_newfunc(sym);
    pushFuncStack(sym);

    instruction *t = newInstr();
    t->opcode = funcenter_v;
    t->result = malloc(sizeof(vmarg));
    make_operand(quad->arg1, t->result);
    t->srcLine = quad->line;
    emitInstruction(t);
}

void generate_RETURN(quad* quad){

    quad->taddress = nextInstructionLabel();
    instruction *t = newInstr();
    t->opcode = assign_v;
    t->arg1 = malloc(sizeof(vmarg));
    t->result = malloc(sizeof(vmarg));
    make_retvaloperand(t->result);
    make_operand(quad->arg1, t->arg1);
    emitInstruction(t);

    //fstack = top; -> to idio to fstack einai to top
    appendFuncStack(fstack->rlist, nextInstructionLabel());

    t->opcode = jump_v;
    reset_operand(t->arg1);
    reset_operand(t->arg2);
    t->result->type = label_a;
    t->srcLine = quad->line;
    emitInstruction(t);
}

void generate_FUNCEND(quad* quad) {

    funcstack *f = popFuncStack(fstack);
    backpatch(f,nextInstructionLabel());
    
    quad->taddress = nextInstructionLabel();
    
    instruction *t = newInstr();
    t->opcode = funcexit_v;
    t->result = malloc(sizeof(vmarg));
    make_operand(quad->arg1, t->result);
    t->srcLine = quad->line;
    emitInstruction(t);
}

/*
    for(i = 0; i<currQuad; i++){
        (*generators[quads[i].op])(quads+i);
    }
    patch_incomplete_jump();

    Gia afto htan h generators alla tin kaname me switch
    ....
*/
void produce_tcode(){
    int i;
    InitFuncStack();
    for(i=0; i<currQuad; i++){

        switch (quads[i].op){
            case assign: generate_ASSIGN(&quads[i]); break;
            case add: generate_ADD(&quads[i]); break;
            case sub: generate_SUB(&quads[i]); break;
            case mul: generate_MUL(&quads[i]); break;
            case divide: generate_DIV(&quads[i]); break;
            case mod: generate_MOD(&quads[i]); break;
            case uminus: generate_UMINUS(&quads[i]); break;
            case and: generate_AND(&quads[i]); break;
            case or: generate_OR(&quads[i]); break;
            case not: generate_NOT(&quads[i]); break;
            case if_eq: generate_IF_EQ(&quads[i]); break;
            case if_noteq: generate_IF_NOTEQ(&quads[i]); break;
            case if_lesseq: generate_IF_LESS(&quads[i]); break;
            case if_greatereq: generate_IF_GREATEREQ(&quads[i]); break;
            case if_less: generate_IF_LESS(&quads[i]); break;
            case if_greater: generate_IF_GREATER(&quads[i]); break;
            case call: generate_CALL(&quads[i]); break;
            case param: generate_PARAM(&quads[i]); break;
            case ret: generate_RETURN(&quads[i]); break;
            case getretval: generate_GETRETVAL(&quads[i]); break;
            case funcstart: generate_FUNCSTART(&quads[i]); break;
            case funcend: generate_FUNCEND(&quads[i]); break;
            case jump: generate_JUMP(&quads[i]); break;
            case tablecreate: generate_NEWTABLE(&quads[i]); break;
            case tablegetelem: generate_TABLEGETELEM(&quads[i]); break;
            case tablesetelem: generate_TABLESETELEM(&quads[i]); break;
            default:
                generate_NOP(&quads[i]);
                printf("QUAD HAS NO OPCODE\n");
        }
    }
    patch_incomplete_jump();
    return;
}

void generateText(){

    FILE *writefd;
    int i, strsize;

    writefd = fopen("binarytext.txt","w");
    if (!writefd){
        printf("Unable to open text file.\n");
        return;
    }
    fprintf(writefd,"%d\n",magic_number);
    /* constTables */
    fprintf(writefd,"Numbers:\n");
    fprintf(writefd,"[%u]",totalNumConsts);
    for (i=0; i<totalNumConsts; i++){
        fprintf(writefd,"   %f", numConsts[i]);
    }
    fprintf(writefd,"\nStrings:\n");
    fprintf(writefd,"[%u]",totalStringConsts);
    for (i=0; i<totalStringConsts; i++){
        strsize = strlen(stringConsts[i]);
        fprintf(writefd,"   %u", strsize);
        fprintf(writefd," %s", stringConsts[i]);
    }
    fprintf(writefd,"\nLibfuncs:\n");
    fprintf(writefd,"[%u]",totalNamedLibfuncs);
    for (i=0; i<totalNamedLibfuncs; i++){
        strsize = strlen(namedLibfuncs[i]);
        fprintf(writefd,"   %u %s", strsize, namedLibfuncs[i]);
    }
    fprintf(writefd,"\nUserfuncs:\n");
    fprintf(writefd,"[%u]",totalUserFuncs);
    for (i=0; i<totalUserFuncs; i++){
        fprintf(writefd,"   %s", userFuncs[i].id);
        fprintf(writefd," %u", userFuncs[i].address);
        fprintf(writefd," %u", userFuncs[i].localSize);
    }
    /* t-code */
    fprintf(writefd,"\n\nCode ");
    fprintf(writefd,"[%u]",nextInstructionLabel());
    for (i=0; i<nextInstructionLabel(); i++){
        /* opcode, type value, type value, type value */
        fprintf(writefd,"\n%d: %d, ", i+1, instructions[i].opcode);

        if(instructions[i].arg1){
            fprintf(writefd,"(type:%d) ", instructions[i].arg1->type);
            fprintf(writefd,"(value:%u) , ", instructions[i].arg1->value);
        }
        if(instructions[i].arg2){
            fprintf(writefd,"(type:%d) ", instructions[i].arg2->type);
            fprintf(writefd,"(value:%u) , ", instructions[i].arg2->value);
        }
        if(instructions[i].result){
            fprintf(writefd,"(type:%d) ", instructions[i].result->type);
            fprintf(writefd,"(value:%u)  ", instructions[i].result->value);
        }
    }
    fclose(writefd);
}

void generateBinary(){

    FILE *writefd;
    unsigned i, unknown = 11;
    unsigned strsize;
    char *id;

    writefd = fopen("binary.bin","wb");
    if (!writefd){
        printf("Unable to open binary file for writing.\n");
        return;
    }
    fwrite(&magic_number, sizeof(unsigned int), 1, writefd);

    /* constTables: Numbers */
    fwrite(&totalNumConsts, sizeof(unsigned), 1, writefd);
    for(i=0; i<totalNumConsts; i++){
        fwrite(&numConsts[i], sizeof(numConsts), 1, writefd);
    }
    /* constTables: Strings */
    fwrite(&totalStringConsts, sizeof(unsigned), 1, writefd);
    for(i=0; i<totalStringConsts; i++){
        strsize = strlen(stringConsts[i]);
        fwrite(&strsize, sizeof(unsigned), 1, writefd);
        fwrite(stringConsts[i], strsize, 1, writefd);
    }  
    /* constTables: Libfuncs */
    fwrite(&totalNamedLibfuncs, sizeof(unsigned), 1, writefd);
    for(i=0; i<totalNamedLibfuncs; i++){
        strsize = strlen(namedLibfuncs[i]);
        fwrite(&strsize, sizeof(unsigned), 1, writefd);
        fwrite(namedLibfuncs[i], strsize, 1, writefd);
    }
    /* constTables: Userfuncs */
    fwrite(&totalUserFuncs, sizeof(unsigned), 1, writefd);
    for(i=0; i<totalUserFuncs; i++){
        fwrite(&userFuncs[i].address, sizeof(unsigned), 1, writefd);
        fwrite(&userFuncs[i].localSize, sizeof(unsigned), 1, writefd);
        strsize = strlen(userFuncs[i].id);
        fwrite(&strsize, sizeof(unsigned), 1, writefd);
        fwrite(userFuncs[i].id, strlen(userFuncs[i].id), 1, writefd);
    }

    /* t-code */
    fwrite(&currInstr, sizeof(currInstr), 1, writefd); //codeSize

    for (i=0; i<nextInstructionLabel(); i++){
        /* opcode, type value, type value, type value */
        fwrite(&instructions[i].opcode, sizeof(vmopcode), 1, writefd);

        if(instructions[i].arg1){
            fwrite(&instructions[i].arg1->type, sizeof(vmarg_t), 1, writefd);
            fwrite(&instructions[i].arg1->value, sizeof(unsigned), 1, writefd);
        }else{
            fwrite(&unknown, sizeof(vmarg_t), 1, writefd);
            fwrite(&unknown, sizeof(unsigned), 1, writefd);
        }
        if(instructions[i].arg2){
            fwrite(&instructions[i].arg2->type, sizeof(vmarg_t), 1, writefd);
            fwrite(&instructions[i].arg2->value, sizeof(unsigned), 1, writefd);
        }else{
            fwrite(&unknown, sizeof(vmarg_t), 1, writefd);
            fwrite(&unknown, sizeof(unsigned), 1, writefd);
        }
        if(instructions[i].result){
            fwrite(&instructions[i].result->type, sizeof(vmarg_t), 1, writefd);
            fwrite(&instructions[i].result->value, sizeof(unsigned), 1, writefd);
        }else{
            fwrite(&unknown, sizeof(vmarg_t), 1, writefd);
            fwrite(&unknown, sizeof(unsigned), 1, writefd);
        }
    }
    fclose(writefd);
}