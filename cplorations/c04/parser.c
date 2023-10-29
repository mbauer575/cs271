/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Maxwell Bauer
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	
	char *s_new = (char*)malloc(strlen(s) + 1);
    int i = 0;

    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') {
			if (*(s2 - 1)){
				s_new[i++] = '\n';
			}
            break;
		
        } 
		if (*s2 == '\n' && *(s2 - 1)) {
			s_new[i++] = *s2;
		}
		else if (!isspace(*s2)) {
            s_new[i++] = *s2;
        }
    }

    s_new[i] = '\0';
    strcpy(s, s_new);

    return s;
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	
	char line[MAX_LINE_LENGTH] = {0};

	while(fgets(line, sizeof(line), file))
	{
		strip(line);
		if (line[0] != '\0'){
			printf("%s", line);
		}
	}
}