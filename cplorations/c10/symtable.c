/****************************************
 * C-ploration 7 CS 271
 *
 * [NAME] Maxwell Bauer
 * [TERM] FALL 2023
 *
 ****************************************/
#include "symtable.h"
#include "stdio.h"

Symbol *hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % SYMBOL_TABLE_SIZE;
}

void symtable_insert(char *key, hack_addr addr)
{
    struct Symbol *Symbol_insert = (struct Symbol *)malloc(sizeof(struct Symbol));
    Symbol_insert->addr = addr;
    Symbol_insert->name = strdup(key);

    int hashIndex = hash(key);

    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL)
    {
        ++hashIndex;
        hashIndex %= SYMBOL_TABLE_SIZE;
    }

    hashArray[hashIndex] = Symbol_insert;
}

struct Symbol *symtable_find(char *key)
{
    int hashIndex = hash(key);

    while (hashArray[hashIndex] != NULL)
    {
        if (strcmp(hashArray[hashIndex]->name, key) == 0)
            return hashArray[hashIndex];

        ++hashIndex;
        hashIndex %= SYMBOL_TABLE_SIZE;
    }

    return NULL;
}

void symtable_display_table()
{
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
    {
        if (hashArray[i] != NULL)
            printf(" (%s,%d)", hashArray[i]->name, hashArray[i]->addr);
        else
            printf(" ~~ ");
    }
    printf("\n");
}

void symtable_print_labels()
{
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
    {
        if (hashArray[i] != NULL)
        {
            printf("{%s,%d}\n", hashArray[i]->name, hashArray[i]->addr);
        }
    }
}