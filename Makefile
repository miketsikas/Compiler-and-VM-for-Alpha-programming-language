CFLAGS = -g

all: parser avm

avm: avm.h avm.c assigns.c arithms.c functions.c tables.c jumps.c
	gcc -g -o avm avm.c assigns.c arithms.c functions.c tables.c jumps.c -lm

parser: parser.c scanner.c tcode.h tcode.c constTables.h constTables.c
	gcc $(CFLAGS) parser.c scanner.c symtablehash.c quad.c tcode.c constTables.c -o parser

parser.c: parser.y symtable.h symtablehash.c quad.h quad.c
	bison -v --yacc --defines --output=parser.c parser.y

scanner.c: parser.c scanner.l
	flex --outfile=scanner.c scanner.l

clean:
	rm parser.h parser.c scanner.c parser parser.output avm

rmgen:
	rm scopes.txt icode.txt binary.bin binarytext.txt