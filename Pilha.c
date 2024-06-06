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

typedef struct Pilha_
{
    int placa;
    int manobras;
    struct Pilha_ *next;
} Pilha;
//Struct que armazena a placa e quantidade de manobras feita por cada carro

int pilhaVazia(Pilha *stack)
{
    return !stack;
}

void stackPush(Pilha **pilha, int valor, int *vagaOcupada, int *vagaLivre, int usePrint)
{
    Pilha *node = *pilha;

    if (*vagaOcupada >= 5)
    {
        if (usePrint)
            printf("Garagem cheia.\n");
        return;
    }

    while (node != NULL)
    {
        if (node->placa == valor)
        {
            if (usePrint)
                printf("O carro com a placa AAA-%05d ja esta estacionado.\n", valor);
            return;
        }
        node = node->next;
    }
    *vagaOcupada = *vagaOcupada + 1;
    *vagaLivre = *vagaLivre - 1;
    Pilha *novo = malloc(sizeof(Pilha));
    novo->placa = valor;
    novo->manobras = 0;
    novo->next = *pilha;
    *pilha = novo;
    if (usePrint)
        printf("Carro placa AAA-%05d estacionado.\n", valor);
}
//Função para estacionar um carro, caso todas as vagas estejam preenchidas, retorna ao usuário que a garagem está cheia. Caso contrário, adicionará o carro à garagem e alocará na  memória suas informações.
int stackPop(Pilha **topo, int *vagaOcupada, int *vagaLivre, int *manobras)
{
    if (pilhaVazia(*topo))
    {
        printf("A vaga ja esta vazia.\n");
        return 0;
    }
    *vagaOcupada = *vagaOcupada - 1;
    *vagaLivre = *vagaLivre + 1;
    Pilha *temp = *topo;
    *topo = (*topo)->next;
    int valorTirado = temp->placa;
    *manobras = temp->manobras;
    free(temp);
    return valorTirado;
}
//Função para retirar um carro da vaga especificada pelo usuário
void stackRemove(Pilha **topo, int posicao, int *vagaOcupada, int *vagaLivre, int *manobras)
{
    if (pilhaVazia(*topo))
    {
        printf("A vaga ja esta vazia.\n");
        return;
    }

    Pilha *temp = NULL;
    int posicaoAtual = 1;

    // Remove carros temporariamente até chegar na posição desejada
    while (posicaoAtual < posicao && !pilhaVazia(*topo))
    {
        Pilha *carroRemovido = *topo;
        int manobrasTemp = 0; // Variável temporária para armazenar manobras
        stackPush(&temp, stackPop(topo, vagaOcupada, vagaLivre, &manobrasTemp), vagaOcupada, vagaLivre, 0);
        carroRemovido->manobras += 1; // Incrementar manobras do carro removido temporariamente
        posicaoAtual++;
    }

    // Verificar se a posição é válida e remover o carro desejado
    if (posicaoAtual == posicao && !pilhaVazia(*topo))
    {
        int elemRemovido = stackPop(topo, vagaOcupada, vagaLivre, manobras);
        printf("Carro com a placa AAA-%05d da vaga %d foi retirado apos %d manobras.\n", elemRemovido, posicao, *manobras);
    }
    else
    {
        printf("Esta vaga esta vazia, tente outra posicao.\n");
    }

    // Recolocar os carros removidos temporariamente de volta na pilha
    while (!pilhaVazia(temp))
    {
        int manobrasTemp = 0; // Variável temporária para armazenar manobras
        stackPush(topo, stackPop(&temp, vagaOcupada, vagaLivre, &manobrasTemp), vagaOcupada, vagaLivre, 0);
        (*topo)->manobras += 1; // Incrementar manobras do carro recolocado
    }
}

void showGarage(Pilha *topo)
{
    Pilha *temp;
    temp = topo;
    int vaga = 1;

    printf("Carros estacionados:\n");
    if (pilhaVazia(topo))
    {
        printf("    > A garagem esta vazia.\n");
        printf("---------------\n");
        return;
    }

    while (temp)
    {
        printf("    > Vaga: [%d] | Placa: AAA-%05d | Manobras: (%d)\n", vaga, temp->placa, temp->manobras);
        temp = temp->next;
        ++vaga;
    }
    printf("---------------\n\n");
}
//Mostra os carros que estão estacionados na garagem, mostrando a vaga em que estão, suas respectivas placas e quantas vezes foram manobrados.
int main()
{
    Pilha *topo = NULL;

    char command;
    int placa;
    int vagaOcupada = 0;
    int vagaLivre = 5;
    int manobras = 0;

    printf("--------------------");
    while (1)
    {
        system("cls");
        showGarage(topo);

        printf("O que deseja fazer?\n");
        printf("    > E <placa> - Estacionar\n");
        printf("    > S <vaga> - Sair da vaga\n");
        printf("    > 0 0 - Sair do programa\n");
        printf("Selecione uma opcao: ");
        scanf_s(" %c %d", &command, sizeof(command), &placa, sizeof(placa));
        printf("\n");
        if (command == '0')
        {
            printf("Programa finalizado.\n");
            break;
        }
        else if (command == 'E' || command == 'e')
        {
            system("cls");
            printf("Estacionando...\n");
            stackPush(&topo, placa, &vagaOcupada, &vagaLivre, 1);
        }
        else if (command == 'S' || command == 's')
        {
            system("cls");
            printf("Desestacionando...\n");
            stackRemove(&topo, placa, &vagaOcupada, &vagaLivre, &manobras);
        }

        system("pause");
    }

    system("pause");
    return 0;
}
