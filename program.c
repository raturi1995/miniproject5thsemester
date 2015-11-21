#include<stdio.h>
#include<string.h>
#include<math.h>
#include"headerfiles.h"

/*struct operation_table
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
            //printf(".........................555555.1.................................\n");
            //printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@%x",optab[i].opcode);
            return(optab[i].opcode);
            break;
        }

    }
   // printf(".........................55555.2.................................\n");
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
}*/
int main()
{
    FILE *input,*inter,*output;
    char label[15],opcode[15],operand[15],current_address[15],addr[15],record[100],byte_hex_value[50],text_value[50],opcode_value[50],byte_char_value[50];
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
        printf("H^% 6s^%06s^%06x\n",label,operand,program_length);
        fprintf(output,"H^% 6s^%06s^%06x\n",label,operand,program_length);
        fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
        {
            strcpy(addr,current_address);
            text_length=0;
            record[0]=0;
           // printf("........................1.............................\n");
            while((text_length<30)&&(strcmp(opcode,"END")!=0))
            {
                //printf("................................2.............................\n");
                if(search_opcode(opcode)!=0)
                {
                    //printf(".........................3.................................\n");
                    text_length+=3;
                    //printf(".........................3.1.................................\n");
                    strcat(record,"^");
                    //printf(".........................3.2.................................\n");
                   // printf("######################################%d",search_opcode(opcode));
                   itoa(search_opcode(opcode),opcode_value,10);
                    strcat(record,opcode_value);
                    //printf(".........................3.3................................\n");
                    if(strcmp(operand,"*")!=0)
                    {
                        //printf(".........................3.4................................\n");
                        value=search_operand(operand,symtab_size);
                        itoa(value,text_value,16);
                        //printf(".........................3.5................................\n");
                        strcat(record,text_value);//.............................................contohex(value)
                        //printf(".........................3.6................................\n");
                    }
                    else
                    {
                        //printf(".........................3.7................................\n");
                        strcat(record,"0000");
                        //printf(".........................3.8................................\n");
                    }
                    //printf(".........................3.9................................\n");
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                    //printf(".........................3.10................................\n");
                }
                //printf("...........................aaaaaaaaaaa...............\n");
                /*else*/ if(strcmp(opcode,"WORD")==0)
                {
                   // printf(".....................4...............................\n");
                    text_length+=3;
                    strcat(record,"^");
                    strcat(record,"00000");
                    strcat(record,operand);
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                }
                //printf("...........................bbbbbbbbbb...............\n");
               /*else*/ if(strcmp(opcode,"BYTE")==0)
                {
                    //printf(".........................5................\n");
                    byte_length=strlen(operand);
                    //printf(".........................5.1...............\n");
                    byte_hex_value[0]=0;
                    byte_char_value[0]=0;
                    //printf(".........................5.2...............\n");
                    if(operand[0]=='c')
                    {
                        //printf(".........................5.3...............\n");
                        for(i=2,j=0;i<byte_length-1;i++,j++)
                        {
                           //printf(".........................5.4...............\n");
                            byte_char_value[j]=operand[i];
                            //printf(".........................5.5...............\n");
                        }
                        //printf(".........................5.6...............\n");
                        text_length+=(j);
                        //printf(".........................5.7...............\n");
                        strcat(record,"^");
                        for(i=0;i<j;i++)
                        {
                            changetohexascii(record,byte_char_value[i]);
                        }
                        //printf(".........................5.8...............\n");
                       // strcat(record,byte_char_value);
                        //printf(".........................5.9...............\n");
                    }
                    //printf(".........................5.10...............\n");
                    if(operand[0]=='x')
                    {
                        //printf(".........................5.11...............\n");
                        for(i=2,j=0;i<byte_length-1;i++,j++)
                        {
                            //printf(".........................5.12...............\n");
                            byte_hex_value[j]=operand[i];
                            //printf(".........................5.13...............\n");
                        }
                        //printf(".........................5.14...............\n");
                        text_length+=(j/2);
                        //printf(".........................5.15...............\n");
                        strcat(record,"^");
                        //printf(".........................5.16...............\n");
                        strcat(record,byte_hex_value);
                        //printf(".........................5.17...............\n");
                    }
                    //printf(".........................5.18...............\n");
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                    //printf(".........................5.19...............\n");
                }
                //printf("...........................cccccccccccc...............\n");
               /*else*/ if(strcmp(opcode,"RESW")==0||strcmp(opcode,"RESB")==0)
                {
                    //printf("......................6.....................\n");
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                    break;
                }
                //printf(".......................7777777777.........................\n");
            }
            printf("T^%06s^%02x%s\n",addr,text_length,record);
            fprintf(output,"T^%06s^%02x%s\n",addr,text_length,record);
        }
        printf("E^%06x\n",startaddr);
        fprintf(output,"E^%06x\n",startaddr);
        fclose(inter);
        fclose(output);
    return(0);
}
