proj: main.o pass1.o pass2.o
	gcc -o proj main.o pass1.o pass2.o -lm 

main.o: groupE.h main.c
	gcc -c -o main.o main.c -lm

pass1.o: groupE.h optab.h pass1.c
	gcc -c -o pass1.o pass1.c -lm

pass2.o: groupE.h pass2.c
	gcc -c -o pass2.o pass2.c -lm
