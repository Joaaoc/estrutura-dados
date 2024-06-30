/*
Bruno Iglesias Guagliardi
Caio Marques Egidio
João Vitor Canella Rodrigues
Luis Gustavo de Menezes Eggenstein
Matheus Vieira da Cunha e Silva
Pablo Gomide
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SZ 100  // Tamanho máximo das strings

// Definição da estrutura da árvore
typedef struct Tree_
{
    char str[STR_SZ];  // A string em si
    int count;         // Quantas vezes essa string apareceu
    struct Tree* left; // Ponteiro para a subárvore esquerda
    struct Tree* right;// Ponteiro para a subárvore direita
} Tree;

// Função para criar um novo nó
Tree* createNode(char* str)
{
    Tree* node = (Tree*)malloc(sizeof(Tree)); // Aloca memória para o novo nó
    strcpy_s(node->str, strlen(str) + 1, str); // Copia a string para o nó
    node->count = 1;       // Inicializa o contador com 1
    node->left = NULL;     // Sem filhos ainda
    node->right = NULL;    // Sem filhos ainda
    return node;           // Retorna o nó novo
}

// Função para inserir um nó na árvore
Tree* insertNode(Tree* node, char* str)
{
    if (node == NULL)  // Se a árvore está vazia, cria um novo nó
        return createNode(str);

    int cmp = strcmp(str, node->str); // Compara a nova string com a do nó atual
    if (cmp == 0)                     // Se forem iguais, incrementa o contador
        node->count++;
    else if (cmp < 0)                 // Se for menor, vai para a esquerda
        node->left = insertNode(node->left, str);
    else                              // Se for maior, vai para a direita
        node->right = insertNode(node->right, str);
    return node;                      // Retorna o nó (atualizado)
}

// Função para percorrer a árvore em ordem e imprimir as palavras
void sortNode(Tree* node)
{
    if (node == NULL)  // Se o nó é NULL, não faz nada
        return;

    sortNode(node->left);                 // Primeiro visita a subárvore esquerda
    printf("%s (%d)\n", node->str, node->count); // Imprime a string e a contagem
    sortNode(node->right);                // Depois visita a subárvore direita
}

// Função para inserir palavras na árvore e ordená-las
void sortWords(char* str[], int n)
{
    Tree* node = NULL;   // Começa com a árvore vazia
    for (int i = 0; i < n; i++)  // Insere todas as palavras na árvore
        node = insertNode(node, str[i]);
    sortNode(node);      // Imprime as palavras em ordem
}

// Função principal
int main() {
    int wordsCapacity = 10;  // Começa com espaço para 10 palavras
    int wordsLen = 0;        // Nenhuma palavra ainda

    printf("Insira as palavras que deseja adicionar (0 para sair):\n");
    char** words = malloc(wordsCapacity * sizeof(char*)); // Aloca memória para o array de palavras
    char word[STR_SZ];        // Buffer para ler as palavras
    while (1) 
    {
        scanf_s("%s", word, sizeof(word));  // Lê uma palavra

        if (strcmp(word, "0") == 0) // Se o usuário digitar "0", para
            break;

        if (wordsLen == wordsCapacity) // Se o array está cheio, dobra o tamanho
        {
            wordsCapacity *= 2;
            words = realloc(words, wordsCapacity * sizeof(char*)); // Realoca memória
        }

        words[wordsLen] = malloc((strlen(word) + 1) * sizeof(char)); // Aloca memória para a nova palavra
        strcpy_s(words[wordsLen], strlen(word) + 1, word); // Copia a palavra para o array
        wordsLen++; // Conta mais uma palavra
    }

    printf("\\/ Quantidade de palavras digitadas \\/\n");
    sortWords(words, wordsLen); // Insere na árvore e imprime em ordem

    for (int i = 0; i < wordsLen; i++) // Libera a memória de cada palavra
        free(words[i]);
    free(words); // Libera a memória do array

    printf("Aperte qualquer letra + enter para finalizar...\n");
    char key;
    scanf_s(" %c", &key); // Espera o usuário pressionar uma tecla

    return 0; // Termina o programa
}
