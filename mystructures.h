#include<stdio.h>
#include<string.h>
#include<math.h>
struct operation_table
{
    char mnemonics[15];
    int opcode;
}optab[9]={   {"LDAS",59},
                {"JUMP",68},
                {"STAR",45},
                {"LDCHA",35},
                {"STCHA",98},
                {"ADDA",28},
                {"SUBT",56},
                {"TIXA",37},
                {"DIVD",85},
            };
struct symbol_table
{
    char label_name[15];
    int opcode;
}symtab[100];
