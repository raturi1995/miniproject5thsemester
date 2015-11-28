#include<stdio.h>
#include<string.h>
#include<math.h>
chk_byte_length(char operand[15],int *locctr)
{
    int flag=0,i;
    int size_of_operand=strlen(operand);
    if(operand[0]=='c')
    {
        (*locctr)=(*locctr)+(size_of_operand-3);
    }
    if(operand[0]=='x')
    {
        for(i=2;operand[i]!='\0';i++)
        {
            flag++;
        }
        (*locctr)=(*locctr)+(flag/2);
    }
}

chk_label(char label[15],int *p,int locctr)
{
    int temp,i;
    temp=(*p);
    for(i=0;i<temp;i++)
    {
        if(strcmp(symtab[i].label_name,label)==0)
            {
                printf("symbol table..error.....label ambiguity generated");
                exit(0);
            }
    }
    (*p)=(*p)+1;
    strcpy(symtab[temp].label_name,label);
    symtab[temp].opcode=locctr;
}
chk_opcode(char opcode[15],int *locctr,char operand[15])
{
    int i,operand_value,flag;
    for(i=0;i<9;i++)
    {
        if(strcmp(opcode,optab[i].mnemonics)==0)
            flag=1;
    }
    if(flag!=1)
    {
        if(strcmp(opcode,"WORD")==0)
            (*locctr)=(*locctr)+3;
        else if(strcmp(opcode,"RESW")==0)
        {
            operand_value=atoi(operand);
            (*locctr)=(*locctr)+(3*operand_value);
        }
        else if(strcmp(opcode,"RESB")==0)
        {
            operand_value=atoi(operand);
            (*locctr)=(*locctr)+operand_value;
        }
        else if(strcmp(opcode,"BYTE")==0)
        {
            chk_byte_length(operand,locctr);
        }
        else
        {
            printf("ERROR:mnemonics not found in the operation table.\nInput the valid mnemonics\n");
            exit(0);
        }
    }
    else
    {
        (*locctr)=(*locctr)+3;
    }
}

