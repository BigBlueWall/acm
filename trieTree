#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE 256
#define MAXSIZE 1000

typedef struct Trie
{
    struct Trie *ch[CHAR_SIZE];
    int prefix;
    int end;

}TRIE;

TRIE *root;

void initTrie()
{
    int i;

    root = (TRIE *)malloc(sizeof(TRIE));
    root->prefix = 0;
    root->end = 0;
    for(i = 0; i < CHAR_SIZE; i++)
        root->ch[i] = NULL;
}

void delTrie(TRIE *tree)
{
    int i;
    if(tree == NULL)
        return;

    for(i = 0; i < CHAR_SIZE; i++)
        if(tree->ch[i] != NULL)
            delTrie(tree->ch[i]);

    free(tree);
}

void updateTrie(char *str)
{
    int i, j;
    int len;
    char c;
    TRIE *p, *q;

    len = strlen(str);
    p = root;

    for(i = 0; i < len; i++)
    {
        c = str[i];
        if(p->ch[c] == NULL)
        {
            q = (TRIE *)malloc(sizeof(TRIE));
            q->prefix = 1;
            q->end = 0;
            for(j = 0; j < CHAR_SIZE; j++)
                q->ch[j] = NULL;

            p->ch[c] = q;
            p = p->ch[c];
        }
        else
        {
            p->ch[c]->prefix++;
            p = p->ch[c];
        }
    }

    p->end = 1;
}

int findTrie(char *str)
{
    int i;
    char c;
    int len = strlen(str);
    TRIE *p = root;

    for(i = 0; i < len; i++)
    {   
        c = str[i];
        p = p->ch[c];
        if(p == NULL)
            return -1;
    }
    if(p->end == 1)
        return 0;
    return -1;
}

int cntPrefix(char *str)
{
    int i;
    char c;
    int len = strlen(str);
    TRIE *p = root;

    for(i = 0; i < len; i++)
    {
        c = str[i];
        p = p->ch[c];
        if(p == NULL)
            return 0;
    }

    return p->prefix;
}

int main(int argc, char const *argv[])
{
    int op;
    int res;
    char str[MAXSIZE];

    initTrie();
    while(~scanf("%d", &op))
    {
        if(op == -1)
            break;

        scanf("%s", str);
        switch(op)
        {
            case 1:
                updateTrie(str);
                break;
            case 2:
                res = findTrie(str);
                if(res == 0)
                    printf("Exists.\n");
                else
                    printf("Not Found.\n");
                break;
            case 3:
                res = cntPrefix(str);
                printf("prefix: %d\n", res);
                break;
            default:
                printf("Invalid op.\n");
                break;
        }
    }
    delTrie(root);

    return 0;
}







