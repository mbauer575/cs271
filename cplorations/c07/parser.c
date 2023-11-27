/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Maxwell Bauer
 * [TERM] FALL 2023
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s)
{
    char *s_new = (char *)malloc(strlen(s) + 1);
    int i = 0;

    for (char *s2 = s; *s2; s2++)
    {
        if (*s2 == '/' && *(s2 + 1) == '/')
        {
            if (*(s2 - 1))
            {
                s_new[i++] = '\n';
            }
            break;
        }
        if (*s2 == '\n' && *(s2 - 1))
        {
            // s_new[i++] = *s2;
        }
        else if (!isspace(*s2))
        {
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
void parse(FILE *file)
{
    char line[MAX_LINE_LENGTH] = {0};
    int line_number = 0;

    while (fgets(line, sizeof(line), file))
    {
        strip(line);
        if (line[0] != '\n' && line[0] != '\0')
        {
            if (is_Atype(line))
            {
                // inst_type = 'A';
            }
            else if (is_label(line))
            {
                // inst_type = 'L';
                char *extracted_line = extract_label(line);
                symtable_insert(extracted_line, line_number);
                strcpy(line, extracted_line);
                line_number--;
            }
            else if (is_Ctype(line))
            {
                // inst_type = 'C';
            }
            line_number++;
            // printf("%c  %s", inst_type, line); // commented out
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
bool is_Atype(const char *line)
{
    return (line[0] == '@');
}
/*
 * Checks if a line is a label.
 *
 * line: the line to check
 *
 * returns: true if the line is a label, false otherwise
 */
bool is_label(const char *line)
{
    return (line[0] == '(');
}
/*
 * Checks if a line is a C-type instruction.
 *
 * line: the line to check
 *
 * returns: true if the line is a C-type instruction, false otherwise
 */
bool is_Ctype(const char *line)
{
    return (!is_label(line) && !is_Atype(line));
}

char *extract_label(const char *line)
{
    char *new_line = malloc(strlen(line) + 1);
    int i = 0;
    int j = 0;
    for (i = 0; line[i] != '\0'; i++)
    {
        if (line[i] != '(' && line[i] != ')')
        {
            new_line[j++] = line[i];
        }
    }
    new_line[j] = '\0';

    return new_line;
}