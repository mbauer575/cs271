/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Maxwell Bauer
 * [TERM] FALL 2023
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"
#include <string.h>

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
                s_new[i++] = '\0';
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
int parse(FILE *file, instruction *instructions)
{
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_number = 0;
    unsigned int instr_num = 0;
    instruction instr;

    add_predefined_symbols();
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        line_number++;
        char inst_type;
        if (instr_num > MAX_INSTRUCTIONS)
        {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }
        strip(line);
        if (line[0] != '\n' && line[0] != '\0' && line[0] != '/')
        {
            // line_number++;
            // instr_num++;
            if (is_Atype(line))
            {
                inst_type = 'A';
                if (!parse_A_instruction(line, &instr.a))
                {
                    exit_program(EXIT_INVALID_A_INSTR, line_number, line);
                }
                instr.type = a_type;
            }
            else if (is_label(line))
            {
                inst_type = 'L';
                char *extracted_line = extract_label(line);
                if (!isalpha(line[1]))
                {
                    exit_program(EXIT_INVALID_LABEL, line_number, extracted_line);
                }
                else if (symtable_find(extracted_line) != NULL)
                {
                    exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_number, line);
                }
                else
                {
                    symtable_insert(extracted_line, instr_num);
                    continue;
                    strcpy(line, extracted_line);
                    // line_number--;
                }
            }
            else if (is_Ctype(line))
            {
                inst_type = 'C';
                instr.type = c_type;
                char tmp_line[MAX_LINE_LENGTH];
                strcpy(tmp_line, line);
                parse_C_instruction(tmp_line, &(instr.c));

                if (instr.c.dest == -1)
                {
                    exit_program(EXIT_INVALID_C_DEST, line_number, line);
                }
                else if (instr.c.comp == -1)
                {
                    exit_program(EXIT_INVALID_C_COMP, line_number, line);
                }
                else if (instr.c.jump == -1)
                {
                    exit_program(EXIT_INVALID_C_JUMP, line_number, line);
                }
            }
            if (instr.type == a_type)
            {
                if (instr.a.is_addr)
                {
                    printf("A: %d\n", instr.a.instrs.address);
                }
                else
                {
                    printf("A: %s\n", instr.a.instrs.label);
                }
            }
            else
            {
                int newC;
                if (abs(instr.c.comp) < 16)
                {
                    newC = instr.c.comp & 0xF;
                }
                else if (abs(instr.c.comp) < 64)
                {
                    newC = instr.c.comp & 0x3F;
                }
                printf("C: d=%d, c=%d, j=%d\n", instr.c.dest, newC, instr.c.jump);
            }
            // printf("%c  %s", inst_type, line);
            instructions[instr_num++] = instr;
            // printf("%u: %c  %s\n", instr_num, inst_type, line);
        }
    }
    return instr_num;
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

/* Function: add_predefined_symbols
 * -------------
 *  add predefined symbols to the symbol table
 *
 *
 *
 * returns: nothing
 */
void add_predefined_symbols()
{
    for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++)
    {
        predefined_symbol symbol = predefined_symbols[i];
        symtable_insert(symbol.name, symbol.value);
    }
}
/*
 * Parses an A-type instruction.
 *
 * line: the line to parse
 * instr: the a_instruction structure to populate
 *
 * returns: true if the line is a valid A-type instruction, false otherwise
 */
bool parse_A_instruction(const char *line, a_instruction *instr)
{
    char *s = (char *)malloc(strlen(line));
    strcpy(s, line + 1);
    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);
    if (s == s_end)
    {
        instr->instrs.label = (char *)malloc(strlen(line));
        strcpy(instr->instrs.label, s);
        instr->is_addr = false;
    }
    else if (*s_end != 0)
    {
        return false;
    }
    else
    {
        instr->instrs.address = result;
        instr->is_addr = true;
    }
    return true;
}
/*
 * Parses a C-type instruction.
 *
 * line: the line to parse
 * instr: the c_instruction structure to populate
 *
 * returns: nothing
 */
void parse_C_instruction(char *line, c_instruction *instr)
{
    char *temp, *jump, *dest, *comp;
    int a = 0;

    // Tokenize the line by ";"
    temp = strtok(line, ";");
    jump = strtok(NULL, ";");

    // Tokenize the temp by "="
    dest = strtok(temp, "=");
    comp = strtok(NULL, "=");

    // If comp is NULL, then it's really the destination
    if (comp == NULL)
    {
        comp = dest;
        dest = NULL;
    }

    // Set the jump, comp, a, and dest fields of the instr structure
    instr->jump = str_to_jumpid(jump);
    instr->comp = str_to_compid(comp, &a);
    instr->a = a;
    instr->dest = str_to_destid(dest);
}