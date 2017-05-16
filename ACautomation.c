#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE 26
#define MAXSIZE 1000

typedef struct Trie
{
    struct Trie *ch[CHAR_SIZE];
    struct Trie *fail;
    int end;

}TRIE;

TRIE *root;
TRIE *queue[MAXSIZE];

void initTrie()
{
    int i;

    root = (TRIE *)malloc(sizeof(TRIE));
    root->end = 0;
    root->fail = NULL;
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
    tree = NULL;
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
        c = str[i]-'a';
        if(p->ch[c] == NULL)
        {
            q = (TRIE *)malloc(sizeof(TRIE));
            q->end = 0;
            q->fail = NULL;
            for(j = 0; j < CHAR_SIZE; j++)
                q->ch[j] = NULL;

            p->ch[c] = q;
            p = p->ch[c];
        }
        else
            p = p->ch[c];
    }

    p->end = 1;
}

void updateFail()
{
    int i;
    int front, tail;
    TRIE *tcur, *tp;

    front = 0;
    tail = 0;
    queue[tail++] = root;
    while(tail != front)
    {
        tcur = queue[front];
        front = (front+1)%MAXSIZE;
        for(i = 0; i < CHAR_SIZE; i++)
        {
            if(tcur->ch[i] != NULL)
            {
                if(tcur == root)
                    tcur->ch[i]->fail = root;
                else
                {
                    tp = tcur->fail;
                    while(tp != NULL)
                    {
                        if(tp->ch[i] != NULL)
                        {
                            tcur->ch[i]->fail = tp->ch[i];
                            break;
                        }
                        tp = tp->fail;
                    }
                    if(tp == NULL)
                        tcur->ch[i]->fail = root;
                }
                queue[tail] = tcur->ch[i];
                tail = (tail+1)%MAXSIZE;
            }
        }
    }   
}

int query(char *str)
{
    int i;
    char c;
    int cnt = 0;
    int len = strlen(str);
    TRIE *cur = root;
    TRIE *temp = NULL;

    for(i = 0; i < len; i++)
    {
        c = str[i]-'a';
        while(cur->ch[c] == NULL && cur->fail != NULL)
            cur = cur->fail;
        if(cur->ch[c] != NULL)
        {
            cur = cur->ch[c];
            temp = cur;
            while(temp->end == 1)
            {
                cnt++;
                temp->end = -1;
                temp = temp->fail;
            }
        }
    }

    return cnt;
}

int main(int argc, char const *argv[])
{
    int i;
    int n;
    char str[MAXSIZE];

    initTrie();

    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        scanf("%s", str);
        updateTrie(str);
    }
    updateFail();
    scanf("%s", str);
    printf("%d\n", query(str));

    delTrie(root);

    return 0;
}







