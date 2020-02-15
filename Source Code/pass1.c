#include "groupE.h"
#include "optab.h"

int xtoi(char *hex)
{
	int i, j, cnt;
	double sum = 0;
	int num[10], integer = 0;

	for (cnt = 0; *(hex + cnt) != '\0'; cnt++);

	for (i = 0; i < cnt; i++)
	{
		if (*(hex + i) == 'A' || *(hex + i) == 'a') {
			sum = 10 * pow(16, cnt - i - 1);
		}
		else if (*(hex + i) == 'B' || *(hex + i) == 'b') {
			sum = 11 * pow(16, cnt - i - 1);
		}
		else if (*(hex + i) == 'C' || *(hex + i) == 'c') {
			sum = 12 * pow(16, cnt - i - 1);
		}
		else if (*(hex + i) == 'D' || *(hex + i) == 'd') {
			sum = 13 * pow(16, cnt - i - 1);
		}
		else if (*(hex + i) == 'E' || *(hex + i) == 'e') {
			sum = 14 * pow(16, cnt - i - 1);
		}
		else if (*(hex + i) == 'F' || *(hex + i) == 'f') {
			sum = 15 * pow(16, cnt - i - 1);
		}
		else if (*(hex + i) >= '0' && *(hex + i) <= '9') {
			sum = (*(hex + i) - 48) * pow(16, cnt - i - 1);
		}
		else perror("Error: Is not Number");

		num[i] = (int)sum;
	}

	for (j = 0; j < 4; j++)
		integer += num[j];
	return integer;
}

void lcproc(int x) {
	char buff[MAXLINE];
	int buf1 = 0;
	int xx = xtoi(lc);

	xx += x;
	sprintf(buff, "%x", xx);
	strcpy(lc, buff);
}

void pass1(struct Statement * sic, char* filename, char* filename2, int i, int sa, int opp, int a)
{
	FILE *in, *out;
	char str[MAXCOL];
	int op1 = 0;
	int sa10 = 0;
	   //sa=start address, lc=loc
	char *t, *t2;
	char buf[10];
	int k, aa, aa1, aa2;


	char sym_filename[30];
	char obj_filename[30];

	strcpy(sym_filename, filename2);
	strcpy(obj_filename, filename2);

	strcat(sym_filename, ".t");
	strcat(obj_filename, ".obj");


	in = fopen(filename, "r");
	out = fopen(sym_filename, "wt");
	if (in == NULL) {
		printf("can't open the file!\n");
		exit(1);
	}
	if (out == NULL) {
		printf("sym no file\n");
		exit(1);
	}

	printf("\n---file--- \n");
	while (fgets(str, MAXCOL, in) != '\x00') {
		int jj = 0;
		printf("%s", str);

		// Returns first token
		strcpy(sic[i].lineNo, strtok(str, " \t\n"));
		strcpy(sic[i].label, strtok(NULL, " \t\n"));
		while (jj < 62) {
			if (strcmp(OPTAB[jj].name, sic[i].label) == 0) {
				strcpy(sic[i].opcode, strtok(NULL, " \t\n"));
				strcpy(sic[i].operand, sic[i].opcode);
				strcpy(sic[i].opcode, sic[i].label);
				strcpy(sic[i].label, "");
				break;
			}
			jj++;
		}
		if (jj == 62) {
			strcpy(sic[i].opcode, strtok(NULL, " \t\n"));
			strcpy(sic[i].operand, strtok(NULL, " \t\n"));
		}

		i++;
	}

	if (strcmp(sic[0].opcode, "START") == 0)
	{
		sa = atoi(sic[0].operand);
		sprintf(sic[0].lineNo, "%d", sa);
		sprintf(buf, "%d", sa);
		strcpy(lc, buf);
	}
	else
		strcpy(lc, "0");

	printf("\n");

	for (k = 1; k < i; k++) {
		strcpy(sic[k].lineNo, lc);

		if (*sic[k].label != NULL)
		{
			strcpy(symtb[a].label, sic[k].label);
			strcpy(symtb[a].adr, lc);
			a++;
		}
		int j = 0;
		while (j < 62) {
			if (strcmp(OPTAB[j].name, sic[k].opcode) == 0) {

				lcproc(3);
				strcpy(optb[opp].name, sic[k].opcode);
				strcpy(optb[opp].op, OPTAB[j].op);
				opp++;
				break;
			}
			if (strcmp(sic[k].opcode, "WORD") == 0)
			{
				lcproc(3);
				break;
			}
			else if (strcmp(sic[k].opcode, "RESW") == 0)
			{
				op1 = atoi(sic[k].operand);
				op1 *= 3;
				lcproc(op1);
				break;
			}
			else if (strcmp(sic[k].opcode, "BYTE") == 0)
			{
				if (sic[k].operand[0] == 'X')
					lcproc(1);
				else
				{
					int len = strlen(sic[k].operand) - 2;

					lcproc(len);
				}
				break;
			}
			else if (strcmp(sic[k].opcode, "RESB") == 0)
			{
				op1 = atoi(sic[k].operand);
				lcproc(op1);
				break;
			}
			else if (strcmp(sic[k].opcode, "END") == 0)
			{
				int buff1 = xtoi(lc);
				int buff2 = xtoi(sic[0].lineNo);
				buff1 -= buff2;
				sprintf(programlength, "%x", buff1);

				printf("\n\nProgram length = %s \n", programlength);
				break;
			}
			j++;
		}
	}

	printf("\n");
	printf("\n");

	printf("----Symbol Table---- \n");
	for (aa = 0; aa < a; aa++) {
		fprintf(out, "%s\t%s\n", symtb[aa].adr, symtb[aa].label);
		printf("%s \t%s \n", symtb[aa].label, symtb[aa].adr);
	}
	printf("\n----OPTable---- \n");
	for (aa = 0; aa < opp; aa++) {
		printf("%s \t%s \n", optb[aa].name, optb[aa].op);
	}
	printf("\n----구조체 내용---- \n");
	for (aa = 0; aa < i; aa++) {
		printf("%s\t%s\t%s\t%s\n", sic[aa].lineNo, sic[aa].label, sic[aa].opcode, sic[aa].operand);
	}
	fclose(in);
	fclose(out);

	pass2(obj_filename, i, sa, opp, a);

}
