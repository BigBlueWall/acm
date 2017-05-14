#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE 256
#define MAXSIZE 1000

int charStep[CHAR_SIZE];

void setStep(char *subStr)
{
    int i;
    int slen = strlen(subStr);
    
    for(i = 0; i < CHAR_SIZE; i++)
        charStep[i] = slen + 1;
    for(i = 0; i < slen; i++)
        charStep[subStr[i]] = slen - i;
}

int sundaySearch(char *mainStr, char *subStr)
{
    int mlen, slen;
    int i, j;
    int ti;
    
    mlen = strlen(mainStr);
    slen = strlen(subStr);
    i = 0;
    j = 0;
    
    while(i < mlen)
    {
        ti = i;
        while(j < slen)
        {
            if(mainStr[i] == subStr[j])
            {
                i++;
                j++;
            }
            else
            {
                if(ti+slen > mlen)
                    return -1;
                i = ti+ charStep[mainStr[ti+slen]];
                j = 0;
                break;
            }
        }
        if(j == slen)
            return i - slen;
    }
    
    return -1;
}

int main(int argc, char const *argv[])
{
    char subStr[MAXSIZE], mainStr[MAXSIZE];
    
    while(~scanf("%s", mainStr))
    {
        scanf("%s", subStr);
        setStep(subStr);
        printf("%d\n", sundaySearch(mainStr, subStr));
    }
    
    return 0;
}
