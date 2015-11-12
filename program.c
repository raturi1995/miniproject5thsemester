#include<stdio.h>
#include<string.h>

struct operation_table
{
    char mnemonics[15];
    int opcode;
}optab[3]={   {"LDA","00"},
                {"JMP","01"},
                {"STA","02"}
            };
struct symbol_table
{
    char label_name[15];
    int opcode;
}symtab[100];
unsigned long convtodecnum(char hex[])
{
    char *hexstr;
    int length = 0;
    const int base = 16; // Base of Hexadecimal Number
    unsigned long decnum = 0;
    int i;
    // Find length of Hexadecimal Number
    for (hexstr = hex; *hexstr != '\0'; hexstr++)
    {
	length++;
    }
    // Find Hexadecimal Number
    hexstr = hex;
    for (i = 0; *hexstr != '\0' && i < length; i++, hexstr++)
    {
	// Compare *hexstr with ASCII values
	if (*hexstr >= 48 && *hexstr <= 57)   // is *hexstr Between 0-9
	{
	    decnum += (((int)(*hexstr)) - 48) * pow(base, length - i - 1);
	}
	else if ((*hexstr >= 65 && *hexstr <= 70))   // is *hexstr Between A-F
	{
	    decnum += (((int)(*hexstr)) - 55) * pow(base, length - i - 1);
	}
	else if (*hexstr >= 97 && *hexstr <= 102)   // is *hexstr Between a-f
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
    for(i=0;i<3;i++)
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
int main()
{
    FILE *input,*inter;
    char label[15],opcode[15],operand[15];
    int startaddr=0,locctr=0,program_length,symtab_size=0,i;
    input=fopen("input.txt","r");
    inter=fopen("inter.txt","w");
    fscanf(input,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        startaddr=convtodecnum(operand);
        locctr=startaddr;
        printf("*\t%s\t%s\t%s\n",label,opcode,operand);
        fprintf(inter,"*\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(input,"%s%s%s",label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
    {
        if(strcmp(label,"*")!=0)
        {
            chk_label(label,&symtab_size,locctr);
        }
        printf("%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        fprintf(inter,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if(strcmp(opcode,"*")!=0)
        {
            chk_opcode(opcode,&locctr,operand);
        }
        fscanf(input,"%s%s%s",label,opcode,operand);
    }
    printf("*\t%s\t%s\t%s\n",label,opcode,operand);
    fprintf(inter,"*\t%s\t%s\t%s\n",label,opcode,operand);
    program_length=locctr-startaddr;
    printf("\nprogram length is ==%x\n",program_length);
    return(0);
}
