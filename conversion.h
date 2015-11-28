#include<stdio.h>
#include<string.h>
#include<math.h>
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
