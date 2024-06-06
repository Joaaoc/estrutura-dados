#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definição da estrutura do no da árvore
typedef struct Arvore{
    char palavra[15];
    int contagem;
    struct Arvore *lado_esq;
    struct Arvore *lado_dir;
} Arvore;

//Função para criar um novo no
Arvore* novoNo(char *palavra){
    Arvore *no = (Arvore *)malloc(sizeof(Arvore));
    strcpy(no->palavra, palavra);
    no->contagem = 1;
    no->lado_esq = NULL;
    no->lado_dir = NULL;
    return no;
}

//Função para inserir uma palavra na árvore
Arvore* insert(Arvore *no, char *palavra){
    if (no == NULL) {
        return novoNo(palavra);
    }

    int cmp = strcmp(palavra, no->palavra);

    if (cmp == 0) {
        no->contagem++;
    } else if (cmp < 0) {
        no->lado_esq = insert(no->lado_esq, palavra);
    } else {
        no->lado_dir = insert(no->lado_dir, palavra);
    }

    return no;
}

//Função para imprimir as palavras e suas quantidades em ordem alfabética
void em_ordem(Arvore *no){
    if (no != NULL) {
        em_ordem(no->lado_esq);
        printf("%s (%d)\n", no->palavra, no->contagem);
        em_ordem(no->lado_dir);
    }
}

//Função para processar as palavras
void processaPalavras(char *str[], int n){
    Arvore *no = NULL;

    for (int i = 0; i < n; i++) {
        no = insert(no, str[i]);
    }

    em_ordem(no);
}

//Função principal
int main(){
    int capacidade = 10;
    int tamanho = 0;
    char **palavras = malloc(capacidade * sizeof(char *));
    if (palavras == NULL){
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    char palavra[15];
    printf("Digite algumas palavras (digite '/0' para encerrar):\n");
    while (1){
        scanf("%15s", palavra);

        if (strcmp(palavra, "/0") == 0){
            break;
        }

        if (tamanho == capacidade){
            capacidade *= 2;
            palavras = realloc(palavras, capacidade * sizeof(char *));
            if (palavras == NULL) {
                fprintf(stderr, "Erro de realocação de memória\n");
                exit(EXIT_FAILURE);
            }
        }

        palavras[tamanho] = malloc((strlen(palavra) + 1) * sizeof(char));
        if (palavras[tamanho] == NULL) {
            fprintf(stderr, "Erro de alocação de memória\n");
            exit(EXIT_FAILURE);
        }
        strcpy(palavras[tamanho], palavra);
        tamanho++;
    }
    
	printf("Segue abaixo a quantidade de vezes em que cada palavra foi digitada:\n");
    processaPalavras(palavras, tamanho);

    for (int i = 0; i < tamanho; i++){
        free(palavras[i]);
    }
    free(palavras);

    return 0;
}