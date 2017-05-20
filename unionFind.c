#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

int father[N];

void init()
{
	int i;
	for(i = 0; i < N; i++)
		father[i] = i;
}

void unionxy(int x, int y)
{
	x = getfather(x);
	y = getfather(y);
	if(x > y)
		father[x] = y;
	father[y] = x;
}

int getfather(int x)
{
	if(x != father[x])
		father[x] = getfather(father[x]);
	return father[x];
}

int main(int argc, char const *argv[])
{
  	unionxy(0,1);
  	unionxy(2,1);
  	unionxy(3,4);
  	unionxy(5,6);
  	unionxy(7,8);
  	unionxy(7,6);
  	unionxy(4,1);

	return 0;
}




