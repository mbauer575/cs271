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
void parse(FILE *file) {
    char line[MAX_LINE_LENGTH] = {0};
    char inst_type;
    char label[MAX_LABEL_LENGTH] = {0};

    while (fgets(line, sizeof(line), file)) {
        strip(line);
        if (line[0] != '\n' && line[0] != '\0') {
            if (is_Atype(line)) {
                inst_type = 'A';
            } else if (is_label(line)) {
                inst_type = 'L';
                extract_label(line, label);
                strcpy(line, label);
            } else if (is_Ctype(line)) {
                inst_type = 'C';
			}
            printf("%c  %s", inst_type, line);
        }
    }
}

/* Function: is_Atype
 * -------------
 * check if the line is an A-type instruction
 *
 * line: the char* string to check
 *
 * returns: true if the line is an A-type instruction, false otherwise
 */
bool is_Atype(const char *line) {
    return (line[0] == '@');
}
/*
 * Checks if a line is a label.
 *
 * line: the line to check
 *
 * returns: true if the line is a label, false otherwise
 */
bool is_label(const char *line) {
    return (line[0] == '(');
}
/*
 * Checks if a line is a C-type instruction.
 *
 * line: the line to check
 *
 * returns: true if the line is a C-type instruction, false otherwise
 */
bool is_Ctype(const char *line) {
    return (!is_label(line) && !is_Atype(line));
}

/* Function: extract_label
 * ----------------------
 * Extracts the label name from a label declaration line.
 *
 * line: the label declaration line
 * label: a buffer to store the extracted label name
 *
 * returns: the extracted label name
 */
char *extract_label(const char *line, char *label) {
    int len = strlen(line);
    strncpy(label, line + 1, len - 2);
    label[len - 2] = '\0';
    return label;
}