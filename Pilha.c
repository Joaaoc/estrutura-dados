#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 5
#define TAMANHO_PLACA 8  // 7 caracteres + '\0'

// Estrutura para representar a pilha do estacionamento
typedef struct {
    char carros[MAX_CARROS][TAMANHO_PLACA];
    int topo;
} PilhaEstacionamento;

void inicializarPilha(PilhaEstacionamento* p) {
    p->topo = -1;
}

int estaVazia(PilhaEstacionamento* p) {
    return p->topo == -1;
}

int estaCheia(PilhaEstacionamento* p) {
    return p->topo == MAX_CARROS - 1;
}

int empilhar(PilhaEstacionamento* p, char placa[]) {
    if (estaCheia(p)) {
        printf("Estacionamento cheio! Carro com placa %s não pode entrar.\n", placa);
        return 0; // Não foi possível empilhar, estacionamento cheio
    }
    strcpy_s(p->carros[++(p->topo)], strlen(placa) + 1, placa);
    printf("Carro com placa %s entrou no estacionamento.\n", placa);
    return 1; // Sucesso
}

int desempilhar(PilhaEstacionamento* p, char placa[]) {
    if (estaVazia(p)) {
        return 0; // Não foi possível desempilhar, estacionamento vazio
    }
    strcpy_s(placa, strlen(p->carros[(p->topo)--]) + 1, p->carros[(p->topo)--]);
    return 1; // Sucesso
}

int removerCarro(PilhaEstacionamento* p, char placa[]) {
    int movimentos = 0;
    char temporario[MAX_CARROS][TAMANHO_PLACA];
    int topoTemp = -1;
    int encontrado = 0;

    // Retirar carros até encontrar o carro desejado ou a pilha ficar vazia
    while (!estaVazia(p)) {
        char placaTopo[TAMANHO_PLACA];
        desempilhar(p, placaTopo);
        if (strcmp(placaTopo, placa) == 0) {
            encontrado = 1;
            break;
        }
        strcpy_s(temporario[++topoTemp], strlen(placaTopo) +1, placaTopo);
        movimentos++;
    }

    // Recolocar os carros removidos na pilha original
    while (topoTemp >= 0) {
        empilhar(p, temporario[topoTemp--]);
    }

    if (encontrado) {
        printf("Carro com placa %s saiu do estacionamento, manobrado %d vezes.\n", placa, movimentos);
    }
    else {
        printf("Carro com placa %s não encontrado no estacionamento.\n", placa);
    }

    if (encontrado == 0)
    {
        printf("Carro com placa %s não está no estacionamento.\n", placa);
    }

    return encontrado;
}

int main2() {
    PilhaEstacionamento estacionamento;
    inicializarPilha(&estacionamento);
    
    char comando;
    char placa[TAMANHO_PLACA];

    char carro1[TAMANHO_PLACA] = "AAA0001";
    char carro2[TAMANHO_PLACA] = "AAA0002";
    char carro3[TAMANHO_PLACA] = "AAA0003";
    char carro4[TAMANHO_PLACA] = "AAA0004";
    char carro5[TAMANHO_PLACA] = "AAA0005";
    char carro6[TAMANHO_PLACA] = "AAA0006";
    char carro7[TAMANHO_PLACA] = "AAA0007";

    empilhar(&estacionamento, carro1);
    empilhar(&estacionamento, carro2);
    removerCarro(&estacionamento, carro1);
    empilhar(&estacionamento, carro3);
    empilhar(&estacionamento, carro4);
    empilhar(&estacionamento, carro5);
    removerCarro(&estacionamento, carro2);
    empilhar(&estacionamento, carro6);

    return 0;
}