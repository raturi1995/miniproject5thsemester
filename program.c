#include<stdio.h>
#include<string.h>
/*struct node
{
    int addr;
    struct node next_refer;
};*/
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
    //struct symbol_table next;
    //struct node refer;
}symtab[100];

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
    strcpy(symtab[temp].label_name,label);
    symtab[temp].opcode=locctr;
}
chk_opcode()
{

}
int main()
{
    FILE *input,*inter;
    char label[15],opcode[15],operand[15];
    int startaddr=0,locctr=0,program_length,symtab_size=0;
    input=fopen("input.txt","r");
    inter=fopen("inter.txt","w");
    fscanf(input,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        startaddr=atoi(operand);
        locctr=startaddr;
        printf("*\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(input,"%s%s%s",label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
    {
        if(label!="*")
        {
            chk_label(label,&symtab_size,locctr);
        }
        if(opcode!="*")
        {
            chk_opcode(opcode);
        }
        //checkpoint
        printf("%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
         fscanf(input,"%s%s%s",label,opcode,operand);
    }
    printf("*\t%s\t%s\t%s\n",label,opcode,operand);
    program_length=locctr-startaddr;




        /*i=0;
    do
    {
        fscanf(fp,"%s%x",temp_mnemonics,temp_opcode);
        mnemonics[0][i]=temp_mnemonics;
        opcode[i]=temp_opcode;
        i++;
    }while(temp_mnemonics!=EOF);
    no_of_mnemonics=i;
    //fscanf(fp,"%s",temp_mnemonics);
  while(temp_mnemonics!=EOF)
  {
   printf("%s\t",temp_mnemonics);
   fscanf(fp,"%s",temp_mnemonics);
  }
   /* for(i=0;i<no_of_mnemonics;i++)
    {
        printf("%s\t%x\n",mnemonics[i],opcode[i]);
    }*/
    return(0);
}
