#include<stdio.h>
#include<string.h>
#include<math.h>
struct operation_table
{
    char mnemonics[15];
    int opcode;
}optab[5]={   {"LDA",50},
                {"JMP",10},
                {"STA",20},
                {"LDCH",30},
                {"STCH",40},
            };
struct symbol_table
{
    char label_name[15];
    int opcode;
}symtab[100];
int search_opcode(char opcode[15])
{
    int i;
    for(i=0;i<5;i++)
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
changetohexascii(char record[50],char ch)
{
    char text[5];
    int char_as_int=(int)ch;
    itoa(char_as_int,text,16);
    strcat(record,text);
}
unsigned long convtodecnum(char hex[])
{
    char *hexstr;
    int length = 0;
    const int base = 16;
    unsigned long decnum = 0;
    int i;
    for (hexstr = hex; *hexstr != '\0'; hexstr++)
    {
        length++;
    }
    hexstr = hex;
    for (i = 0; *hexstr != '\0' && i < length; i++, hexstr++)
    {
        if (*hexstr >= 48 && *hexstr <= 57)
        {
            decnum += (((int)(*hexstr)) - 48) * pow(base, length - i - 1);
        }
        else if ((*hexstr >= 65 && *hexstr <= 70))
        {
            decnum += (((int)(*hexstr)) - 55) * pow(base, length - i - 1);
        }
        else if (*hexstr >= 97 && *hexstr <= 102)
        {
            decnum += (((int)(*hexstr)) - 87) * pow(base, length - i - 1);
        }
        else
        {
            printf(" Invalid Hexadecimal Number \n");

        }
    }
    return decnum;
}

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
    for(i=0;i<5;i++)
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
