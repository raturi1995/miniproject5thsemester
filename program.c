#include<stdio.h>
#include<string.h>
#include<math.h>

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
int search_opcode(char opcode[15])
{
    int i;
    for(i=0;i<3;i++)
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
contohex()
{
    return(12);
}
changetohexascii()
{
    return(32);
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
    FILE *input,*inter,*output;
    char label[15],opcode[15],operand[15],current_address[15],addr[15],record[100],byte_value[50];
    int startaddr=0,locctr=0,program_length,symtab_size=0,i,j,text_length,byte_length,value;
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
    fclose(input);
    fclose(inter);
    printf("........................pass 2.................................................\n");
    //.........................................................pass 2...........................
    output=fopen("output.txt","w");
    inter=fopen("inter.txt","r");
    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        printf("H^%s^00%s^0000%x",label,operand,program_length);
        //fprintf(inter,"*\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
        {
            strcpy(addr,current_address);
            text_length=0;
            record[0]=0;
            printf("........................1.............................\n");
            while((text_length<30))
            {
                printf("................................2.............................\n");
                if(search_opcode(opcode)!=0)
                {
                    printf(".........................3.................................\n");
                    text_length+=3;
                    strcat(record,"^");
                    strcat(record,search_opcode(opcode));
                    if(strcmp(operand,"*")!=0)
                    {
                        value=search_operand(operand,symtab_size);
                        strcat(record,value);//.............................................contohex(value)
                    }
                    else
                    {
                        strcat(record,"0000");
                    }
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                }
                else if(strcmp(opcode,"WORD")==0)
                {
                    printf(".....................4...............................\n");
                    text_length+=3;
                    strcat(record,"^");
                    strcat(record,"00000");
                    strcat(record,operand);
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                }
               else if(strcmp(opcode,"BYTE")==0)
                {
                    printf(".........................5555555555555555555555555................\n");
                    byte_length=strlen(operand);
                    byte_value[0]='\0';
                    if(operand[0]=="c")
                    {
                        for(i=2,j=0;i<byte_length;i++,j++)
                        {
                            byte_value[j]=operand[i];
                        }
                        text_length+=j;
                        strcat(record,"^");
                        strcat(record,changetohexascii(byte_value));
                    }
                    if(operand[0]=="x")
                    {
                        for(i=2,j=0;i<byte_length;i++,j++)
                        {
                            byte_value[j]=operand[i];
                        }
                        text_length+=j/2;
                        strcat(record,"^");
                        strcat(record,byte_value);
                    }
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                }
               else if(strcmp(opcode,"RESW")==0||strcmp(opcode,"RESB")==0)
                {
                    printf("......................6.....................\n");
                    break;
                }
                printf(".......................7777777777.........................\n");
            }
            printf("T^00%s^%x%s\n",addr,text_length,record);
        }
        fclose(inter);
        fclose(output);
    return(0);
}
