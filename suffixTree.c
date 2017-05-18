#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR 256
#define MAX_LEN 1001
 
typedef struct SuffixTreeNode {

    struct SuffixTreeNode *children[MAX_CHAR];
    struct SuffixTreeNode *suffixLink;
 
    int start;
    int *end;
 
    int suffixIndex;
}Node;
 
char text[MAX_LEN]; 
Node *root = NULL; 

Node *lastNewNode = NULL;
Node *activeNode = NULL;
 
int activeEdge = -1;
int activeLength = 0;
 
int remainingSuffixCount = 0;
int leafEnd = -1;
int *rootEnd = NULL;
int *splitEnd = NULL;
int size = -1; 
 
Node *newNode(int start, int *end)
{
    Node *node =(Node*) malloc(sizeof(Node));
    int i;
    for(i = 0; i < MAX_CHAR; i++)
          node->children[i] = NULL;
 
    node->suffixLink = root;
    node->start = start;
    node->end = end;
 
    node->suffixIndex = -1;

    return node;
}
 
int edgeLength(Node *n) 
{
    return *(n->end) - (n->start) + 1;
}
 
int walkDown(Node *currNode)
{
    if(activeLength >= edgeLength(currNode))
    {
        activeEdge += edgeLength(currNode);
        activeLength -= edgeLength(currNode);
        activeNode = currNode;
        return 1;
    }
    return 0;
}
 
void extendSuffixTree(int pos)
{
    leafEnd = pos;
    remainingSuffixCount++;
    lastNewNode = NULL;
 
    while(remainingSuffixCount > 0) 
    {
        if(activeLength == 0)
            activeEdge = pos; 
       
        if(activeNode->children[text[activeEdge]] == NULL)
        {
            activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);
 
            if(lastNewNode != NULL)
            {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = NULL;
            }
        }
        else
        {
            Node *next = activeNode->children[text[activeEdge]];
            if(walkDown(next))
                continue;

            if(text[next->start + activeLength] == text[pos])
            {
                if(lastNewNode != NULL && activeNode != root)
                {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }
 
                activeLength++;
                break;
            }

            splitEnd = (int*) malloc(sizeof(int));
            *splitEnd = next->start + activeLength - 1;
 
            Node *split = newNode(next->start, splitEnd);
            activeNode->children[text[activeEdge]] = split;
 
            split->children[text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;
 
            if(lastNewNode != NULL)
                lastNewNode->suffixLink = split;

            lastNewNode = split;
        }
 
        remainingSuffixCount--;
        if(activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        }
        else if(activeNode != root) 
            activeNode = activeNode->suffixLink;
    }
}
 
void print(int i, int j)
{
    int k;
    for(k=i; k<=j; k++)
        printf("%c", text[k]);
}
 
void setSuffixIndexByDFS(Node *n, int labelHeight)
{
	int leaf = 1;
    int i;
    if(n == NULL)  
    	return;
 
    if(n->start != -1) 
        print(n->start, *(n->end));
    
    for(i = 0; i < MAX_CHAR; i++)
    {
        if(n->children[i] != NULL)
        {
            if(leaf == 1 && n->start != -1)
                printf(" [%d]\n", n->suffixIndex);
 
            leaf = 0;
            setSuffixIndexByDFS(n->children[i], labelHeight + edgeLength(n->children[i]));
        }
    }
    if(leaf == 1)
    {
        n->suffixIndex = size - labelHeight;
        printf(" [%d]\n", n->suffixIndex);
    }
}
 
void freeSuffixTreeByPostOrder(Node *n)
{
	int i;

    if(n == NULL)
        return;

    for(i = 0; i < MAX_CHAR; i++)
        if (n->children[i] != NULL)
            freeSuffixTreeByPostOrder(n->children[i]);

    if(n->suffixIndex == -1)
        free(n->end);
    free(n);
}
 
void buildSuffixTree()
{
	int i;

    size = strlen(text);
    rootEnd = (int*) malloc(sizeof(int));
    *rootEnd = - 1;
 
    root = newNode(-1, rootEnd);
 
    activeNode = root; 
    for(i = 0; i < size; i++)
        extendSuffixTree(i);

    setSuffixIndexByDFS(root, 0);
 
    freeSuffixTreeByPostOrder(root);
}
 
int main(int argc, char *argv[])
{
//  strcpy(text, "abc"); buildSuffixTree();
//  strcpy(text, "xabxac#");    buildSuffixTree();
//  strcpy(text, "xabxa");  buildSuffixTree();
//  strcpy(text, "xabxa$"); buildSuffixTree();
    strcpy(text, "abcabxabcd$"); buildSuffixTree();
//  strcpy(text, "geeksforgeeks$"); buildSuffixTree();
//  strcpy(text, "THIS IS A TEST TEXT$"); buildSuffixTree();
//  strcpy(text, "AABAACAADAABAAABAA$"); buildSuffixTree();
    return 0;
}
