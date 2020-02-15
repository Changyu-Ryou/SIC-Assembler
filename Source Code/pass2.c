#include "groupE.h"

void pass2(char* obj_filename, int i, int sa, int opp, int a) {

	FILE *print;
	int aa, aa1, aa2;

	char start[10], len[10];
	int opcode_length[10];
	int col = 0, ii = 0;
	print = fopen("./objectProg.txt", "wt");

	if (strcmp(sic[0].opcode, "START") == 0)
	{
		strcpy(start, sic[0].operand);
		strcpy(len, programlength);
	}
	printf("\n\nH^%s^00%s^00%s\nT^00%s", sic[0].label, start, len, start);
	fprintf(print, "H^%s^00%s^00%s\nT^00%s", sic[0].label, start, len, start);
	opcode_length[ii] = 0;
	for (aa = 1; aa < i; aa++) {
		for (aa1 = 0; aa1 < opp - 1; aa1++) {
			if (strcmp(sic[aa].opcode, optb[aa1].name) == 0) {
				for (aa2 = 0; aa2 < a; aa2++) {
					if (strcmp(sic[aa].operand, symtb[aa2].label) == 0)
					{
						if (col > 9)
						{
							col = 0;
							ii++;
							opcode_length[ii] = 0;
						}
						opcode_length[ii] += 3;
						col++;
						break;
					}
				}
				break;
			}
		}
		if ((strcmp(sic[aa].opcode, "BYTE") == 0) || (strcmp(sic[aa].opcode, "WORD") == 0))
		{
			if (strcmp(sic[aa].opcode, "WORD") == 0)
			{
				if (col > 9)
				{
					col = 0;
					ii++;
					opcode_length[ii] = 0;
				}
				opcode_length[ii] += 3;
				col++;
			}
			else
			{
				if (strcmp(sic[aa].label, "EOF") == 0) {
					if (col > 9)
					{
						col = 0;
						ii++;
						opcode_length[ii] = 0;
					}
					opcode_length[ii] += 3;
					col++;
				}
			}
		}
	}
	printf("^%x", opcode_length[0]);
	fprintf(print, "^%x", opcode_length[0]);
	col = 0;
	ii = 0;
	for (aa = 1; aa < i; aa++) {
		for (aa1 = 0; aa1 < opp - 1; aa1++) {
			if (strcmp(sic[aa].opcode, optb[aa1].name) == 0) {
				for (aa2 = 0; aa2 < a; aa2++) {
					if (strcmp(sic[aa].operand, symtb[aa2].label) == 0)
					{
						if (col > 9)
						{
							col = 0;
							ii++;
							printf("\nT^00%s^%02x", sic[aa].lineNo, opcode_length[ii]);
							fprintf(print, "\nT^00%s^%02x", sic[aa].lineNo, opcode_length[ii]);
						}
						printf("^%s%s", optb[aa1].op, symtb[aa2].adr);
						fprintf(print, "^%s%s", optb[aa1].op, symtb[aa2].adr);
						col++;
						break;
					}
				}
				break;
			}
		}
		if ((strcmp(sic[aa].opcode, "BYTE") == 0) || (strcmp(sic[aa].opcode, "WORD") == 0))
		{
			if (strcmp(sic[aa].opcode, "WORD") == 0)
			{
				if (col > 9)
				{
					col = 0;
					ii++;
					printf("\nT^00%s^%02x", sic[aa].lineNo, opcode_length[ii]);
					fprintf(print, "\nT^00%s^%02x", sic[aa].lineNo, opcode_length[ii]);
				}
				printf("^00000%s", sic[aa].operand);
				fprintf(print, "^00000%s", sic[aa].operand);
				col++;
			}
			else
			{
				if (strcmp(sic[aa].label, "EOF") == 0) {
					if (col > 9)
					{
						col = 0;
						ii++;
						printf("\nT^00%s^%02x", sic[aa].lineNo, opcode_length[ii]);
						fprintf(print, "\nT^00%s^%02x", sic[aa].lineNo, opcode_length[ii]);
					}
					printf("^000000");
					fprintf(print, "^000000");
					col++;
				}
				else {
					int length = strlen(sic[aa].operand);
					printf("length = %d \n", length);
					fprintf(print, "length = %d \n", length);
					for (ii = 2; ii < length; ii++)
					{
						printf("%c", sic[aa].operand[ii]);
						fprintf(print, "%c", sic[aa].operand[ii]);
					}
				}
			}
		}
	}
	printf("\nE^00%s\n", start);
	fprintf(print, "\nE^00%s\n", start);
}

