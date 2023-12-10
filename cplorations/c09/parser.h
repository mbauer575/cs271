#ifndef __PARSER_H__
#define __PARSER_H__

/****************************************
 * C-ploration 5 for CS 271
 *
 * [NAME] Maxwell Bauer
 * [TERM] FALL 2023
 *
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "hack.h"

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

typedef union
{
    hack_addr address;
    char *label;
} a_value;

typedef struct a_instruction
{
    union instrs
    {
        hack_addr address;
        char *label;
    } instrs;
    bool is_addr;
} a_instruction;

typedef struct c_instruction
{
    opcode a : 1;
    opcode comp : 6;
    opcode dest : 3;
    opcode jump : 3;
} c_instruction;

enum instr_type
{
    invalid = -1,
    a_type,
    c_type
};

typedef union
{
    a_instruction a_inst;
    c_instruction c_inst;
} instruction_value;
bool parse_A_instruction(const char *line, a_instruction *instr);
typedef struct instruction
{
    union
    {
        a_instruction a;
        c_instruction c;
    };
    enum instr_type type;
} instruction;

/** function prototypes **/
char *strip(char *s);
char *extract_label(const char *);
void parse(FILE *file);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

void add_predefined_symbols();

#endif