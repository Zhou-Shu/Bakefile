bake: bake.c variable.c openbakefile.c target.c bake.h
	gcc -o bake bake.c variable.c openbakefile.c target.c 
