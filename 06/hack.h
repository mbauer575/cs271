#ifndef HACK_H
#define HACK_H

#include <stdint.h>
#include <string.h>

#define NUM_PREDEFINED_SYMBOLS 23

typedef enum jump_id
{
    JMP_INVALID = -1,
    JMP_NULL = 0,
    JMP_JGT,
    JMP_JEQ,
    JMP_JGE,
    JMP_JLT,
    JMP_JNE,
    JMP_JLE,
    JMP_JMP
} jump_id;

typedef enum dest_id
{
    DEST_INVALID = -1,
    DEST_NULL = 0,
    DEST_M,
    DEST_D,
    DEST_MD,
    DEST_A,
    DEST_AM,
    DEST_AD,
    DEST_AMD
} dest_id;

typedef enum comp_id
{
    COMP_INVALID = -1,
    COMP_0 = 42,
    COMP_1 = 63,
    COMP_NEG1 = 58,
    COMP_D = 12,
    COMP_A = 48, // when a=0
    COMP_NOTD = 13,
    COMP_NOTA = 49, // when a=0
    COMP_NEGD = 15,
    COMP_NEGA = 51, // when a=0
    COMP_DPLUS1 = 31,
    COMP_APLUS1 = 55, // when a=0
    COMP_DMINUS1 = 14,
    COMP_AMINUS1 = 50, // when a=0
    COMP_DPLUSA = 2,   // when a=0
    COMP_DMINUSA = 19,
    COMP_AMINUSD = 7, // when a=0
    COMP_DANDA = 0,   // when a=0
    COMP_DORA = 21,   // when a=0
    COMP_M = 112,     // when a=1
    COMP_NOTM = 113,
    COMP_NEGM = 115,
    COMP_MPLUS1 = 119,
    COMP_MMINUS1 = 114,
    COMP_DPLUSM = 66, // when a=1
    COMP_DMINUSM = 83,
    COMP_MMINUSD = 71, // when a=1
    COMP_DANDM = 64,   // when a=1
    COMP_DORM = 85     // when a=1
} comp_id;

typedef enum symbol_id
{
    SYM_R0 = 0,
    SYM_R1 = 1,
    SYM_R2 = 2,
    SYM_R3 = 3,
    SYM_R4 = 4,
    SYM_R5 = 5,
    SYM_R6 = 6,
    SYM_R7 = 7,
    SYM_R8 = 8,
    SYM_R9 = 9,
    SYM_R10 = 10,
    SYM_R11 = 11,
    SYM_R12 = 12,
    SYM_R13 = 13,
    SYM_R14 = 14,
    SYM_R15 = 15,
    SYM_SCREEN = 16384,
    SYM_KBD = 24576,
    SYM_SP = 0,
    SYM_LCL = 1,
    SYM_ARG = 2,
    SYM_THIS = 3,
    SYM_THAT = 4
} symbol_id;

typedef struct predefined_symbol
{
    char name[10];
    int16_t value;
} predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
    {"R0", SYM_R0},
    {"R1", SYM_R1},
    {"R2", SYM_R2},
    {"R3", SYM_R3},
    {"R4", SYM_R4},
    {"R5", SYM_R5},
    {"R6", SYM_R6},
    {"R7", SYM_R7},
    {"R8", SYM_R8},
    {"R9", SYM_R9},
    {"R10", SYM_R10},
    {"R11", SYM_R11},
    {"R12", SYM_R12},
    {"R13", SYM_R13},
    {"R14", SYM_R14},
    {"R15", SYM_R15},
    {"SCREEN", SYM_SCREEN},
    {"KBD", SYM_KBD},
    {"SP", SYM_SP},
    {"LCL", SYM_LCL},
    {"ARG", SYM_ARG},
    {"THIS", SYM_THIS},
    {"THAT", SYM_THAT}};

static inline dest_id str_to_destid(const char *s)
{
    dest_id id = DEST_INVALID;

    if (s == NULL)
    {
        id = DEST_NULL;
    }
    else if (strcmp(s, "M") == 0)
    {
        id = DEST_M;
    }
    else if (strcmp(s, "D") == 0)
    {
        id = DEST_D;
    }
    else if (strcmp(s, "MD") == 0)
    {
        id = DEST_MD;
    }
    else if (strcmp(s, "A") == 0)
    {
        id = DEST_A;
    }
    else if (strcmp(s, "AM") == 0)
    {
        id = DEST_AM;
    }
    else if (strcmp(s, "AD") == 0)
    {
        id = DEST_AD;
    }
    else if (strcmp(s, "AMD") == 0)
    {
        id = DEST_AMD;
    }

    return id;
}

static inline jump_id str_to_jumpid(const char *s)
{
    jump_id id = JMP_INVALID;

    if (s == NULL)
    {
        id = JMP_NULL;
    }
    else if (strcmp(s, "JGT") == 0)
    {
        id = JMP_JGT;
    }
    else if (strcmp(s, "JEQ") == 0)
    {
        id = JMP_JEQ;
    }
    else if (strcmp(s, "JGE") == 0)
    {
        id = JMP_JGE;
    }
    else if (strcmp(s, "JLT") == 0)
    {
        id = JMP_JLT;
    }
    else if (strcmp(s, "JNE") == 0)
    {
        id = JMP_JNE;
    }
    else if (strcmp(s, "JLE") == 0)
    {
        id = JMP_JLE;
    }
    else if (strcmp(s, "JMP") == 0)
    {
        id = JMP_JMP;
    }

    return id;
}
static inline comp_id str_to_compid(const char *s, int *a)
{
    comp_id id = COMP_INVALID;
    *a = 0;
    if (s == NULL)
    {
        id = COMP_INVALID;
    }
    else if (strcmp(s, "0") == 0)
    {
        id = COMP_0;
    }
    else if (strcmp(s, "1") == 0)
    {
        id = COMP_1;
    }
    else if (strcmp(s, "-1") == 0)
    {
        id = COMP_NEG1;
    }
    else if (strcmp(s, "D") == 0)
    {
        id = COMP_D;
    }
    else if (strcmp(s, "A") == 0)
    {
        id = COMP_A;
    }
    else if (strcmp(s, "!D") == 0)
    {
        id = COMP_NOTD;
    }
    else if (strcmp(s, "!A") == 0)
    {
        id = COMP_NOTA;
    }
    else if (strcmp(s, "-D") == 0)
    {
        id = COMP_NEGD;
    }
    else if (strcmp(s, "-A") == 0)
    {
        id = COMP_NEGA;
    }
    else if (strcmp(s, "D+1") == 0)
    {
        id = COMP_DPLUS1;
    }
    else if (strcmp(s, "A+1") == 0)
    {
        id = COMP_APLUS1;
    }
    else if (strcmp(s, "D-1") == 0)
    {
        id = COMP_DMINUS1;
    }
    else if (strcmp(s, "A-1") == 0)
    {
        id = COMP_AMINUS1;
    }
    else if (strcmp(s, "D+A") == 0)
    {
        id = COMP_DPLUSA;
    }
    else if (strcmp(s, "D-A") == 0)
    {
        id = COMP_DMINUSA;
    }
    else if (strcmp(s, "A-D") == 0)
    {
        id = COMP_AMINUSD;
    }
    else if (strcmp(s, "D&A") == 0)
    {
        id = COMP_DANDA;
    }
    else if (strcmp(s, "D|A") == 0)
    {
        id = COMP_DORA;
    }
    else if (strcmp(s, "M") == 0)
    {
        id = COMP_M;
        id = COMP_A;
        *a = 1;
    }
    else if (strcmp(s, "!M") == 0)
    {
        id = COMP_NOTM;
        id = COMP_NOTA;
        *a = 1;
    }
    else if (strcmp(s, "-M") == 0)
    {
        id = COMP_NEGM;
        id = COMP_NEGA;
        *a = 1;
    }
    else if (strcmp(s, "M+1") == 0)
    {
        id = COMP_MPLUS1;
        id = COMP_APLUS1;
        *a = 1;
    }
    else if (strcmp(s, "M-1") == 0)
    {
        id = COMP_MMINUS1;
        id = COMP_AMINUS1;
        *a = 1;
    }
    else if (strcmp(s, "D+M") == 0)
    {
        id = COMP_DPLUSM;
        id = COMP_DPLUSA;
        *a = 1;
    }
    else if (strcmp(s, "D-M") == 0)
    {
        id = COMP_DMINUSM;
        id = COMP_DMINUSA;
        *a = 1;
    }
    else if (strcmp(s, "M-D") == 0)
    {
        id = COMP_MMINUSD;
        id = COMP_AMINUSD;
        *a = 1;
    }
    else if (strcmp(s, "D&M") == 0)
    {
        id = COMP_DANDM;
        id = COMP_DANDA;
        *a = 1;
    }
    else if (strcmp(s, "D|M") == 0)
    {
        id = COMP_DORM;
        id = COMP_DORA;
        *a = 1;
    };
    return id;
}

#endif