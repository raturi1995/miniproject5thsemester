#include"headerfiles.h"
int main()
{
    FILE *input,*inter,*output;
    char label[15],opcode[15],operand[15],current_address[15],addr[15],oper_value[20],operand_value[20],record[100],byte_hex_value[50],text_value[50],opcode_value[50],byte_char_value[50];
    int startaddr=0,locctr=0,program_length,symtab_size=0,i,j,text_length,byte_length,value;
    printf("\t\t\t\tMINI PROJECT\n\n\t\t\t SUBMITTED BY:  SHUBHAM RATURI\n");
    printf("_______________________________________________________________________________\n");
    printf("\nTHE INTERMEDIATE FILE OF THE  GIVEN PROGRAM IS:\n\n\nADDRESS\tLABEL\tOPCODE\tOPERAND\n\n");
    input=fopen("input.txt","r");
    inter=fopen("inter.txt","w");
    fscanf(input,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        startaddr=convtodecnum(operand);          //starting address is stored in startaddr.
        locctr=startaddr;
        printf("*\t%s\t%s\t%s\n",label,opcode,operand);
        fprintf(inter,"*\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(input,"%s%s%s",label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
    {
        if(strcmp(label,"*")!=0)
        {
            chk_label(label,&symtab_size,locctr);                //label is send to the function to search in symtab.
        }
        printf("%04x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        fprintf(inter,"%06x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        /*

        */
        if(strcmp(opcode,"*")!=0)
        {
            chk_opcode(opcode,&locctr,operand);
        }
        fscanf(input,"%s%s%s",label,opcode,operand);
    }
    printf("*\t%s\t%s\t%s\n",label,opcode,operand);
    fprintf(inter,"*\t%s\t%s\t%s\n",label,opcode,operand);
    program_length=locctr-startaddr;                           //proggram length is calculated.
    printf("\nPROGRAM LENGTH OF THE PROGRAM IS ==%x\n",program_length);
    fclose(input);
    fclose(inter);
    //........................pass 2...........................
    printf("\nOBJECT FILE OF THE ABOVE PROGRAM IS  :\n\n");
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
            while((text_length<30)&&(strcmp(opcode,"END")!=0))
            {
                if(search_opcode(opcode)!=0)
                {
                    text_length+=3;
                    strcat(record,"^");
                    itoa(search_opcode(opcode),opcode_value,10);
                    strcat(record,opcode_value);
                    if(strcmp(operand,"*")!=0)
                    {
                        value=search_operand(operand,symtab_size);
                        itoa(value,text_value,16);
                        strcat(record,text_value);
                    }
                    else
                    {
                        strcat(record,"0000");
                    }
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                }
                if(strcmp(opcode,"WORD")==0)
                {
                    text_length+=3;
                    strcat(record,"^");
                    int operand_value=atoi(operand);
                    itoa(operand_value,oper_value,16);
                    int len=strlen(oper_value);
                    for(i=0;i<6-len;i++)
                    {
                        strcat(record,"0");
                    }
                    strcat(record,oper_value);
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                }
                 if(strcmp(opcode,"BYTE")==0)
                {
                    byte_length=strlen(operand);
                    byte_hex_value[0]=0;
                    byte_char_value[0]=0;
                    if(operand[0]=='c')
                    {
                        for(i=2,j=0;i<byte_length-1;i++,j++)
                        {
                            byte_char_value[j]=operand[i];
                        }
                        text_length+=(j);
                        strcat(record,"^");
                        for(i=0;i<j;i++)
                        {
                            changetohexascii(record,byte_char_value[i]);
                        }
                    }
                    if(operand[0]=='x')
                    {
                        for(i=2,j=0;i<byte_length-1;i++,j++)
                        {
                            byte_hex_value[j]=operand[i];
                        }
                        text_length+=(j/2);
                        strcat(record,"^");
                        strcat(record,byte_hex_value);
                    }
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                }
                if(strcmp(opcode,"RESW")==0||strcmp(opcode,"RESB")==0)
                {
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                    break;
                }
            }
            printf("T^%06s^%02x%s\n",addr,text_length,record);
            fprintf(output,"T^%06s^%02x%s\n",addr,text_length,record);
        }
    printf("E^%06x\n",startaddr);
    fprintf(output,"E^%06x\n",startaddr);
    fclose(inter);
    fclose(output);
    printf("\nTHE CONTENT IN SYMBOL TABLE IS :\n\n");
    for(i=0;i<symtab_size;i++)
    {
        printf("%s\t%x\n",symtab[i].label_name,symtab[i].opcode);
    }
    return(0);
}
