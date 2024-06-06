#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SZ 100

typedef struct Tree_
{
    char str[STR_SZ];
    int count;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* createNode(char* str)
{
    Tree* node = (Tree*)malloc(sizeof(Tree));
    strcpy_s(node->str, strlen(str) + 1, str);
    node->count = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Tree* insertNode(Tree* node, char* str)
{
    if (node == NULL)
        return createNode(str);

    int cmp = strcmp(str, node->str);
    if (cmp == 0)
        node->count++;
    else if (cmp < 0)
        node->left = insertNode(node->left, str);
    else
        node->right = insertNode(node->right, str);
    return node;
}

void sortNode(Tree* node)
{
    if (node == NULL)
        return;

    sortNode(node->left);
    printf("%s (%d)\n", node->str, node->count);
    sortNode(node->right);
}

void sortWords(char* str[], int n)
{
    Tree* node = NULL;
    for (int i = 0; i < n; i++)
        node = insertNode(node, str[i]);
    sortNode(node);
}

int main() {
    int wordsCapacity = 10;
    int wordsLen = 0;

    printf("Insira as palavras que deseja adicionar (0 para sair):\n");
    char** words = malloc(wordsCapacity * sizeof(char*));
    char word[STR_SZ];
    while (1) 
    {
        scanf_s("%s", word, sizeof(word));

        if (strcmp(word, "0") == 0) 
            break;

        if (wordsLen == wordsCapacity) 
        {
            wordsCapacity = wordsCapacity * 2;
            words = realloc(words, wordsCapacity * sizeof(char*));
        }

        words[wordsLen] = malloc((strlen(words) + 1) * sizeof(char));
        strcpy_s(words[wordsLen], strlen(word) + 1, word);
        wordsLen++;
    }

    printf("\\/ Quantidade de palavras digitadas \\/\n");
    sortWords(words, wordsLen);

    for (int i = 0; i < wordsLen; i++) 
        free(words[i]);
    free(words);

    printf("Aperte qualquer letra + enter para finalizar...\n");
    char key;
    scanf_s(" %c", &key);

    return 0;
}
