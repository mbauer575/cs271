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

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH-2)

typedef int16_t hack_addr;
typedef int16_t opcode;

typedef union {
    hack_addr address;
    char *label;
} a_value;

typedef struct {
    a_value value;
    bool is_addr;
} a_instruction;

typedef struct {
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;
} c_instruction;

typedef enum {
    INVALID_INST = -1,
    A_INST,
    C_INST
} instr_type;

typedef union {
    a_instruction a_inst;
    c_instruction c_inst;
} instruction_value;

typedef struct {
    instruction_value value;
    instr_type type;
} instruction;


/** function prototypes **/
char *strip(char *s);
char *extract_label(const char *line, char* label);

void parse(FILE * file);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);


