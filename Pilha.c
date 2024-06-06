#include <stdio.h>
#include <stdlib.h>

typedef struct Pilha_ 
{
    int placa;
    int manobras;
    struct Pilha_* next;
} Pilha;

int pilhaVazia(Pilha* stack) 
{
    return !stack;
}

void stackPush(Pilha** pilha, int valor, int* vaga_ocup, int* vaga_disp, int usePrint)
{
    Pilha* node = *pilha;

    if (*vaga_ocup >= 5)
    {
        if (usePrint)
            printf("Garagem cheia.\n");
        return;
    }

    while (node != NULL && node->placa != NULL)
    {
        if (node->placa == valor)
        {
            if (usePrint)   
                printf("O carro com a placa RJ-%05d ja esta estacionado.\n", valor);
            return;
        }
        node = node->next;
    }
    *vaga_ocup = *vaga_ocup + 1;
    *vaga_disp = *vaga_disp - 1;
    Pilha* novo = malloc(sizeof(Pilha));
    novo->placa = valor;
    novo->manobras = 0;
    novo->next = *pilha;
    *pilha = novo;
    if (usePrint)
        printf("Carro placa AAA-%05d estacionado.\n", valor);
}

int stackPop(Pilha** topo, int* vaga_ocup, int* vaga_disp, int* manobras)
{
    if (pilhaVazia(*topo))
    {
        printf("A vaga ja esta vazia.\n");
        return 0;
    }
    *vaga_ocup = *vaga_ocup - 1;
    *vaga_disp = *vaga_disp + 1;
    Pilha* temp = *topo;
    *topo = (*topo)->next;
    int valorTirado = temp->placa;
    *manobras = temp->manobras;
    temp->placa = NULL;
    temp->manobras = NULL;
    free(temp);
    temp = NULL;
    return valorTirado;
}

void stackRemove(Pilha** topo, int posicao, int* vaga_ocup, int* vaga_disp, int* manobras) 
{
    if (pilhaVazia(*topo))
    {
        printf("A vaga ja esta vazia.\n");
        return;
    }

    Pilha* temp = NULL;
    int posicaoAtual = 0;
    while (posicaoAtual < posicao - 1 && !pilhaVazia(*topo))
    {
        stackPush(&temp, stackPop(topo, vaga_ocup, vaga_disp, manobras), vaga_ocup, vaga_disp, 0);
        posicaoAtual++;
        (*topo)->manobras += 1;
    }

    if (posicaoAtual != posicao && !pilhaVazia(*topo))
    {
        int elemRemovido = stackPop(topo, vaga_ocup, vaga_disp, manobras);
        printf("Carro com a placa AAA-%05d da vaga %d foi retirado apos %d manobras.\n", elemRemovido, posicao, *manobras);
    }
    else 
    {
        printf("Esta vaga esta vazia, tente outra posicao.\n");
    }

    while (!pilhaVazia(temp))
    {
        stackPush(topo, stackPop(&temp, vaga_ocup, vaga_disp, manobras), vaga_ocup, vaga_disp, 0);
    }
}

void showGarage(Pilha* topo) 
{
    Pilha* temp;
    temp = topo;
    int vaga = 1;

    printf("Carros estacionados:\n");
    if (pilhaVazia(topo))
    {
        printf("    > A garagem esta vazia.\n");
        printf("---------------\n");
        return;
    }
    else 
    {
        while (temp) 
        {
            printf("    > Vaga: [%d] | Placa: AAA-%05d | Manobras: (%d)\n", vaga, temp->placa, temp->manobras);
            temp = temp->next;
            ++vaga;
        }
        printf("---------------\n\n");
    }
}

int main() 
{
    Pilha* topo = NULL;

    char command;
    int placa;
    int vaga_ocup = 0;
    int vaga_disp = 5;
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
            stackPush(&topo, placa, &vaga_ocup, &vaga_disp, 1);
        }
        else if (command == 'S' || command == 's')
        {
            system("cls");
            printf("Desestacionando...\n");
            stackRemove(&topo, placa, &vaga_ocup, &vaga_disp, &manobras);
        }

        system("pause");
    }

    system("pause");
    return 0;
}
