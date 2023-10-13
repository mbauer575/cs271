/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] Maxwell Bauer
 * [TERM] FALL 2023
 * 
 ****************************************/
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>

#define MAX_LINE_LENGTH  200


int main(int argc, const char *argv[])
{	
	if(argc != 2)
	{
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}	

	char input_file[MAX_LINE_LENGTH];
	strcpy(input_file, "asm/");
	strcat(input_file, argv[1]);
	
	// for gradescope use argv[1] directly instead of input_file
	FILE *fin = fopen(argv[1], "r");

	if(fin == NULL)
	{
		perror("Unable to open file!");
		exit(EXIT_FAILURE);
	}
	
	char out_file[MAX_LINE_LENGTH];
	
	strcpy(out_file, argv[1]);
	strcat(out_file, ".echo");

	FILE *fout = fopen(out_file, "w+");


	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;

	while (fgets(line, sizeof(line), fin)) 
	{
		line_num++;
    	printf("[%04d] %s", line_num, line);
    	fprintf(fout, "[%04d] %s", line_num, line);
	}
	fclose(fin);
	fclose(fout);
	return 1;
}
