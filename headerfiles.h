#include<stdio.h>
#include<string.h>
#include<math.h>
#include"mystructures.h"
#include"conversion.h"
#include"checking_functions.h"

int search_opcode(char opcode[15])
{
    int i;
    for(i=0;i<9;i++)
    {
        if(strcmp(opcode,optab[i].mnemonics)==0)
        {
            return(optab[i].opcode);
            break;
        }

    }
    return(0);
}
int search_operand(char operand[15],int symtab_size)
{
        int i;
        for(i=0;i<symtab_size;i++)
        {
        if(strcmp(operand,symtab[i].label_name)==0)
        {
            return(symtab[i].opcode);
            break;
        }

    }
    return(0);
}


