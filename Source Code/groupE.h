#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAXCOL 80
#define MAXLINE 100

char programlength[MAXLINE];
char lc[100];


struct OPT {
	char name[MAXLINE];     // Mnemonic
	char op[100];            // opcode
};

struct  Statement {
	char lineNo[100];
	char label[100];
	char opcode[100];
	char operand[100];
};

struct  optable {
	char name[MAXLINE];
	char  op[MAXLINE];
};
struct symtable {
	char label[MAXLINE];
	int value;
	char adr[MAXLINE];// int adr;
};
struct Statement sic[MAXLINE];
struct optable optb[MAXLINE];
struct symtable symtb[MAXLINE];


struct Statement readline(FILE *src, int path);
