/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Maxwell Bauer
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"

int main(int argc, const char *argv[])
{		
	if(argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char input_file[MAX_LINE_LENGTH];
	strcpy(input_file, "asm/");
	strcat(input_file, argv[1]);

	FILE *fin = fopen(argv[1], "r");
	if(fin == NULL)
	{
		perror("Unable to open file!");
		exit(EXIT_FAILURE);
	}
	else
	{
		parse(fin);
		fclose(fin);
	}
			
}


