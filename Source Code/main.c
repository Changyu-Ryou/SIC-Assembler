#include "groupE.h"

int main(int argc, char* argv[])
{
	int i = 0, sa = 0, opp = 0;
	int a = 0;      //symtb check

	char filename[30];
	char inputfile[30];
	char sym_filename[30];
	char obj_filename[30];

	strcpy(inputfile, argv[1]);
	strcpy(filename, strtok(argv[1], "."));
	//strcpy(sym_filename, filename);
	//strcpy(obj_filename, filename);

	//strcat(sym_filename, ".t");
	//strcat(obj_filename, ".obj");

	pass1(sic, inputfile, filename,i,sa, opp, a);
	//pass2(obj_filename);

	return 0;
}