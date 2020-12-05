# Compiler-and-VM-for-Alpha-programming-language
This is a compiler for compiling programs written in the Alpha programming language. The compiled files can then be executed within the virtual machine included in this project.
# Compilation stages
1. Lexical Analysis -- Created the Lexical Analyzer "al", using lex, who takes as input a text file written with lexical elements from language Alpha
2. Syntax Analysis -- Created a Syntax Analyzer using YACC in C++, who takes as input a text file written in the Alpha programming language and validates its syntax.
3. Semantic Analysis And Intermediate Code Generation -- Integrated in the syntactic analyzer of the 2nd phase (for alpha language) semantic rules for syntactically guided intermediate code translation. Also implemented short-circuit boolean evaluation.
5. Code Generation -- Generated the target code with input the intermediate code procuded in phase 3.
6. VM -- Created a Virtual Machine, which takes as input the generated target code and executes it.
