#include <stdio.h>
#include <stdlib.h>

typedef struct Pilha_ 
{
    int dado;
    struct Pilha_* proximo;
} Pilha;

int pilhaVazia(Pilha* topo) 
{
    return !topo;
}

void Push(Pilha** topo, int valor, int* vaga_ocup, int* vaga_disp) 
{
    *vaga_ocup = *vaga_ocup + 1;
    *vaga_disp = *vaga_disp - 1;
    Pilha* novo = malloc(sizeof(Pilha));
    novo->dado = valor;
    novo->proximo = *topo;
    *topo = novo;
    printf("Carro placa RJ-%05d estacionado.\n", valor);
}

int Pop(Pilha** topo, int* vaga_ocup, int* vaga_disp) 
{
    if (pilhaVazia(*topo))
    {
        printf("A vaga ja esta vazia.\n");
        return 0;
    }
    else 
    {
        *vaga_ocup = *vaga_ocup - 1;
        *vaga_disp = *vaga_disp + 1;
        Pilha* temp = *topo;
        *topo = (*topo)->proximo;
        int valorTirado = temp->dado;
        free(temp);
        temp = NULL;
        return valorTirado;
    }
}

void Desengarrafar(Pilha** topo, int posicao, int* vaga_ocup, int* vaga_disp) 
{
    if (pilhaVazia(*topo))
    {
        printf("A vaga ja esta vazia.\n");
        return;
    }

    Pilha* temp = NULL;
    int posicaoAtual = 0, manobra = 0;
    while (posicaoAtual < posicao - 1 && !pilhaVazia(*topo))
    {
        Push(&temp, Pop(topo, vaga_ocup, vaga_disp), vaga_ocup, vaga_disp);
        posicaoAtual++;
        manobra++;
    }

    if (posicaoAtual != posicao && !pilhaVazia(*topo))
    {
        printf("Vezes que carros foram manobrados: %d\n", manobra);
        int elemRemovido = Pop(topo, vaga_ocup, vaga_disp);
        printf("Carro com a placa RJ-%05d da vaga %d foi retirado.\n", elemRemovido, posicao);
    }
    else 
    {
        printf("Esta vaga esta vazia, tente outra posicao.\n");
    }

    while (!pilhaVazia(temp))
    {
        Push(topo, Pop(&temp, vaga_ocup, vaga_disp), vaga_ocup, vaga_disp);
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
            printf("    > [%d] Placa: RJ-%05d\n", vaga, temp->dado);
            temp = temp->proximo;
            ++vaga;
        }
        printf("---------------\n\n");
    }
}

int main() 
{
    Pilha* topo = NULL;

    char command;
    int placa, escolha;
    int vaga_ocup = 0;
    int vaga_disp = 5;

    printf("--------------------");
    while (1)
    {
        system("cls");
        showGarage(topo);
        
        printf("O que deseja fazer?\n");
        printf("    > E - Estacionar\n");
        printf("    > S - Sair da vaga\n");
        printf("    > 0 - Sair do programa\n");
        printf("Selecione uma opcao: ");
        scanf_s(" %c", &command);
        printf("\n");
        if (command == '0')
        {
            break;
        }
        else if (command == 'E' || command == 'e')
        {
            if (vaga_ocup >= 5)
            {
                printf("Garagem cheia.\n");
                continue;
            }

            printf("Digite os 5 numeros finais da placa: ");
            scanf_s("%d", &placa);

            system("cls");
            printf("Estacionando...\n");
            Push(&topo, placa, &vaga_ocup, &vaga_disp);
        }
        else if (command == 'S' || command == 's')
        {
            printf("Digite a vaga do carro a ser tirado: ");
            scanf_s("%d", &escolha);

            system("cls");
            printf("Desestacionando...\n");
            Desengarrafar(&topo, escolha, &vaga_ocup, &vaga_disp);
        }

        printf("Aperte qualquer tecla para reiniciar...\n");
        scanf_s(" %c", &command);
    }


    return 0;
}
