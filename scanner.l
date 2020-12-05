%{
	#include "parser.h"

	char* comment_lines(int start, int end);
	

	int tokencount = 0;
	int comCounter = 0;
%}

/* tmima orismwn */

%option yylineno
%option noyywrap

/*keyword 		if|else|while|for|function|return|break|continue|and|not|or|local|true|false|nil*/
operator 		\={1,2}|\+{1,2}|\-{1,2}|\*|\/|\%|\!=|>|<|>=|<=
punctuation 	\{|\}|\[|\]|\(|\)|\;|\,|\:{1,2}|\.{1,2}

id 	 			[a-zA-Z][a-zA-Z_0-9]*
integer 		(0[xX][0-9A-Fa-f]+)|([0-9]+)
real 			[0-9]*\.[0-9](e|E)?[0-9]*
delimiter 		[\r\n \t\v]+
string 			\"
line_comment 	"//".*
block_comment 	"/*"

/* tmima kanonwn */

%%
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"for" {return FOR;}
"function" {return FUNCTION;}
"return" {return RETURN;}
"break" {return BREAK;}
"continue" {return CONTINUE;}
"and" {return AND;}
"or" {return OR;}
"not" {return NOT;}
"local" {return LOCAL;}
"true" {return TRUE;}
"false" {return FALSE;}
"nil" {return NIL;}

"=" {return ASSERTION;}
"==" {return EQUALS;}
"+" {return PLUS;}
"++" {return PLUS1;}
"-" {return MINUS;}
"--" {return MINUS1;}
"*" {return MULT;}
"/" {return DIV;}
"%" {return MOD;}
"!=" {return DIFF;}
">" {return GREATER_THAN;}
">=" {return GREATER_OR_EQUAL;}
"<" {return LESS_THAN;}
"<=" {return LESS_OR_EQUAL;}
"{" {return LEFT_BRACKET;}
"}" {return RIGHT_BRACKET;}
"[" {return LEFT_SQUARE_BRACKET;}
"]" {return RIGHT_SQUARE_BRACKET;}
"(" {return LEFT_PARENTHESIS;}
")" {return RIGHT_PARENTHESIS;}
";" {return SEMICOLON;}
"," {return COMMA;}
":" {return COLON;}
"::" {return DOUBLE_COLON;}
"." {return DOT;}
".." {return DOUBLE_DOT;}


{id}			{	
	yylval.strVal = strdup(yytext);
	return ID;
}
{integer} 		{
	yylval.intVal = atoi(yytext);
	return INTEGER;
}
{real} 			{	
	yylval.doubleVal = atof(yytext);
	return REAL;
}
{delimiter} 	{}

{string} 			{	
						char c, *str = (char*)malloc(sizeof(char));
						int count = 0, exit = 0;

						while((c = input())!= EOF){

							if(c == '\\'){
								switch((c = input())){

									case '\"':
										str[count++]='"';
										str = realloc(str,count*sizeof(char));
										break;

									case 'n':
										str[count++]='\n';
										str = realloc(str,count*sizeof(char));
										break;

									case 't':
										str[count++]='\t';
										str = realloc(str,count*sizeof(char));
										break;

									case 'b':
										str[count++]='\b';
										str = realloc(str,count*sizeof(char));
										break;

									case 'r':
										str[count++]='\r';
										str = realloc(str,count*sizeof(char));
										break;

									case '\\':
										str[count++]='\\';
										str = realloc(str,count*sizeof(char));
										break;
									
									default:
										exit = 1;
										printf("Error: (line %d) unrecognized escape character '\%c'\n",yylineno,c);
										break;
								}								
							} else {

								if(c == 34){ // ascii representation of double quote
									str[count]='\0';
									break;
								}
								str[count++]=c;
								str = realloc(str,count*sizeof(char));

							}
						}

						if(c == EOF){
							printf("Error: (line %d) string not terminated\n", yylineno);
						}else{
							if(exit!=1){
								yylval.strVal = strdup(str);
								return STRING;
							}
						}
}

{line_comment} 		{}

{block_comment} 	{	
						int start = yylineno, end;
						char c, *cl;

						int** counters,i = 0,j = 0,nested = 0;
						counters = malloc(sizeof(int*));
						counters[i] = malloc(sizeof(int));
						counters[i][0] = yylineno;
						counters[i][1] = -1;
						
						comCounter++;
						
						while((c = input())!= EOF){
							if(c == '*'){
								if((c = input()) == '/'){
									if(counters[i][1] == -1){
										counters[i][1] = yylineno;
									}
									i--;
									comCounter--;
									if(comCounter == 0)
										break;
								}
								else{
									unput(c);
								}
							}else if(c == '/'){
								if(c = input() == '*'){
									nested++;
									i = nested;
									counters = realloc(counters,sizeof(int*)*(nested+1));
									counters[nested] = malloc(sizeof(int));
									counters[nested][0] = yylineno;
									counters[nested][1] = -1;
									comCounter++;
								}else
									unput(c);
							}
						}
						if(comCounter == 0){
							//cl = comment_lines(start, yylineno);
							//list_insert(yyval,yylineno,++tokencount,cl,"COMMENT",NULL,-1);
							for(j = nested;j >=0;j--){ // EDW ALLAGI
								cl = comment_lines(counters[j][0], counters[j][1]);
								//list_insert(yyval,yylineno,++tokencount,cl,"COMMENT",NULL,-1);
							}

						} else 	
							printf("Error: (line %d) comments not closed\n",yylineno);
}

. 					{
						printf("Undefined input %s in line %d\n", yytext, yylineno);
}

%%

/* Epistrefei to string "start - end" */
char* comment_lines(int start, int end) {

	char *result1, *result2, *final;

	result1 = (char*)malloc(sizeof(unsigned int));
	result2 = (char*)malloc(sizeof(unsigned int));

	/* integer to string */
	sprintf(result1, "%u", start);
	sprintf(result2, "%u", end);

	final = malloc(strlen(result1) + strlen(result2) + 3 + 1); // - and \0

	strcat(final, result1);
	strcat(final, " - ");
	strcat(final, result2);

	return final;
}
