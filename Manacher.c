#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE 26
#define MAXSIZE 1001

char str[MAXSIZE];
char temp[MAXSIZE*2+4];
int Len[MAXSIZE*2+4];

int po;
int ans;
int mx;
int center;

int min(int a, int b)
{
    return a > b ? b : a;
}

int init()
{
    int i;
    int len = strlen(str);
    temp[0] = '@';
    for(i = 1; i < len*2; i+=2)
    {
        temp[i] = '#';
        temp[i+1] = str[i/2];
    }
    temp[i++] = '#';
    temp[i++] = '$';
    temp[i] = 0;

    return 2*len+1;
}

void manacher(int len)
{
    int i;
    for(i = 1; i < len; i++)
    {
        if(mx > i)
            Len[i] = min(mx-i, Len[2*po-i]);
        else
            Len[i] = 1;
        while(temp[i-Len[i]] == temp[i+Len[i]])
            Len[i]++;
        if(Len[i]+i > mx)
        {
            mx = Len[i]+i;
            po = i;
        }
        if(ans < Len[i])
        {
            ans = Len[i];
            center = i;
        }
    }
    mx = center - ans + 1;
    ans = ans * 2 - 1;
}

int main(int argc, char const *argv[])
{
    int i;

    scanf("%s", str);
    manacher(init());

    for(i = mx; i < mx+ans; i++)
        if(temp[i] != '#')
            putchar(temp[i]);
    putchar('\n');

    return 0;
}







