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

// Estrutura que representa um nó do grafo
struct noGrafo
{
    int info;                 // Informação armazenada no nó
    struct noGrafo* proxNo;   // Ponteiro para o próximo nó na lista
    struct noArco* arcos;     // Ponteiro para a lista de arcos desse nó
};
typedef struct noGrafo* PtrNoGrafo;

// Estrutura que representa um arco do grafo
struct noArco
{
    int peso;                 // Peso do arco
    struct noGrafo* no;       // Ponteiro para o nó de destino do arco
    struct noArco* proxArco;  // Ponteiro para o próximo arco na lista
};
typedef struct noArco* PtrNoArco;

// Função para inserir um novo nó no início da lista de nós do grafo
void insertnode(PtrNoGrafo* g, PtrNoGrafo p)
{
    p->proxNo = *g; // O novo nó aponta para o atual primeiro nó
    *g = p;         // O ponteiro do grafo aponta para o novo nó
}

// Função para criar um arco entre dois nós do grafo com um peso específico
void joinwtInfo(PtrNoGrafo g, int x1, int x2, int p)
{
    PtrNoGrafo no1 = NULL, no2 = NULL;

    // Procura pelos nós com as informações x1 e x2
    while (1)
    {
        if (g == NULL)
            break;
        if (g->info == x1)
            no1 = g;
        if (g->info == x2)
            no2 = g;
        g = g->proxNo;
    }

    // Verifica se ambos os nós foram encontrados
    if (no1 == NULL)
    {
        printf("Error: no1 == NULL.\n");
        return;
    }
    if (no2 == NULL)
    {
        printf("Error: no2 == NULL.\n");
        return;
    }

    // Cria um novo arco e o insere na lista de arcos do nó no1
    PtrNoArco novoArco = (PtrNoArco)malloc(sizeof(struct noArco));
    novoArco->peso = p;
    novoArco->no = no2;
    novoArco->proxArco = no1->arcos;
    no1->arcos = novoArco;
}

// Função para verificar se dois nós são adjacentes
int adjacent(PtrNoGrafo g, int x1, int x2)
{
    PtrNoGrafo no = g;
    while (1)
    {
        if (no == NULL)
            break;
        if (no->info == x1)
        {
            PtrNoArco arco = no->arcos;
            while (1)
            {
                if (arco == NULL)
                    break;
                if (arco->no->info == x2) 
                    return 1;
                arco = arco->proxArco;
            }
        }
        no = no->proxNo;
    }
    return 0;
}

// Função para criar o grafo com alguns nós e arcos
void criaGrafo(PtrNoGrafo* g)
{
    // Cria 8 nós e os insere no grafo
    for (int i = 0; i < 8; i++)
    {
        PtrNoGrafo no = (PtrNoGrafo)malloc(sizeof(struct noGrafo));
        no->info = i;
        no->proxNo = NULL;
        no->arcos = NULL;
        insertnode(g, no);
    }

    // Cria alguns arcos entre os nós
    joinwtInfo(*g, 0, 3, 2);
    joinwtInfo(*g, 1, 0, 1);
    joinwtInfo(*g, 1, 2, 3);
    joinwtInfo(*g, 3, 0, 2);
    joinwtInfo(*g, 3, 4, 2);
    joinwtInfo(*g, 4, 4, 1);
    joinwtInfo(*g, 5, 6, 3);
}

// Função para mostrar o grafo
void mostraGrafo(PtrNoGrafo g)
{
    PtrNoGrafo p = g;

    while (1)
    {
        if (p == NULL)
            break;

        printf("----------\n");
        printf("* No: %d\n", p->info);

        printf("    Arcos: ");
        PtrNoArco a = p->arcos;
        if (a == NULL)
            printf("Vazio");
        else
        {
            while (1)
            {
                if (a == NULL)
                    break;
                printf("%d (%d)", a->no->info, a->peso);
                a = a->proxArco;
                if (a != NULL)
                    printf(" | ");
            }
        }
        printf("\n");

        printf("    Adjacentes: ");
        int firstTime = 1;
        PtrNoGrafo g2 = g;
        while (1)
        {
            if (g2 == NULL)
                break;
            if (g2 != p && adjacent(g, p->info, g2->info))
            {
                if (!firstTime)
                    printf(" | ");
                printf("%d", g2->info);
                firstTime = 0;
            }
            g2 = g2->proxNo;
        }
        if (firstTime)
            printf("Vazio");
        printf("\n");

        printf("----------\n");
        p = p->proxNo;
    }
}

// Função principal
int main(void)
{
    PtrNoGrafo g = NULL; // Inicializa o ponteiro para o grafo
    criaGrafo(&g);       // Cria o grafo
    mostraGrafo(g);      // Mostra o grafo
    return 0;
}
