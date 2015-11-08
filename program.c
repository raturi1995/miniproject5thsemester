#include<stdio.h>
int main()
{
    FILE *fp;
    char mnemonics[15][100],temp_mnemonics[15];
    int opcode[100],temp_opcode,i,no_of_mnemonics;
    fp=fopen("instruction_set.txt","r");
    /*i=0;
    do
    {
        fscanf(fp,"%s%x",temp_mnemonics,temp_opcode);
        mnemonics[0][i]=temp_mnemonics;
        opcode[i]=temp_opcode;
        i++;
    }while(temp_mnemonics!=EOF);
    no_of_mnemonics=i;*/
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
