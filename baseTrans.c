#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

char oldData[MAX], newData[MAX];
int olde[MAX], newe[MAX];
int oldb, newb;

void trans()
{
	int i, j = 0;
	int len;

	len = strlen(oldData);
	for(i = len-1; i >= 0; i--)
		olde[len-1-i] = oldData[i] - (oldData[i] <= '9' ? '0' : oldData[i] <= 'Z' ? ('A'-36) : ('a'-10));

	while(len)
	{
		for(i = len-1; i >= 1; i--)
		{
			olde[i-1] += olde[i]%newb*oldb;
			olde[i] /= newb;
		}

		newe[j++] = olde[0] % newb;
		olde[0] /= newb;

		while(len>0 && !olde[len-1])
			len--;
	}

	newe[j] = 0;
	for(i = 0; i < j; i++)
		newData[j-1-i] = newe[i] + (newe[i] <= 9 ? '0' : newe[i] <= 35 ? ('a'-10) : ('A'-36));
	newData[j] = 0;
}

int main() 
{	
	int N;

	scanf("%d", &N);
	while(N--)
	{
		scanf("%d%d%s", &oldb, &newb, oldData);
		trans();
		printf("%s\n", newData);
	}

    return 0;
}
