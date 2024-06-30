/*

Componentes do grupo:

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

#define TAM_HASH 100
#define MAX_NOME 20

// Enum para tipos de token
typedef enum { Reservada, Variavel, Constante, Fim } TipoToken;
char* str_TipoToken[] = { "Reservada", "Variavel", "Constante", "Fim" };

// Enum para tipos de identificadores
typedef enum { Inteiro, Real, Caractere, String } TipoIdentificador;
char* str_TipoIdentificador[] = { "Inteiro", "Real", "Caractere", "String" };

// Função para puxar o próximo token da entrada
void pegaToken(TipoToken* token, TipoIdentificador* id, char* nome, int* linha);

// Estrutura que irá representar a linha
typedef struct Line
{
    int num;
    struct Line* next;
} Line;

// Estrutura para representar uma entrada na tabela de símbolos
typedef struct Input
{
    char nome[MAX_NOME + 1];
    TipoIdentificador id;
    Line* lines;
    struct Input* next;
} Input;

Input* table[TAM_HASH];

// Função de hashing simples
unsigned int hash(char* nome)
{
    unsigned int hash = 0;
    while (1)
    {
        if (!*nome)
            break;
        hash = (hash << 5) + *nome++;
    }
    return hash % TAM_HASH;
}

// Função que adiciona uma linha à uma entrada na tabela de símbolos
void addLine(Input* input, int linha)
{
    Line* newLine = (Line*)malloc(sizeof(Line));
    newLine->num = linha;
    newLine->next = NULL;

    Line* current = input->lines;
    if (current != NULL)
    {
        while (1)
        {
            if (current->next == NULL)
                break;
            current = current->next;
        }
        current->next = newLine;
        return;
    }
    input->lines = newLine;
    return;
}

// Função que cria uma nova entrada na tabela de símbolos
Input* newEntry(char* nome, TipoIdentificador id, int linha)
{
    Input* input = (Input*)malloc(sizeof(Input));
    strcpy_s(input->nome, strlen(nome) + 1, nome);
    input->id = id;
    input->lines = NULL;
    input->next = NULL;
    addLine(input, linha);
    return input;
}

// função para inserir uma entrada na tabela de símbolos
void insertTable(TipoToken token, TipoIdentificador id, char* nome, int linha)
{
    if (token != Variavel && token != Constante)
    {
        return;
    }

    unsigned int indice = hash(nome);
    Input* current = table[indice];

    while (1)
    {
        if (current == NULL)
            break;
        if (strcmp(current->nome, nome) != 0)
        {
            current = current->next;
        }
        else
        {
            addLine(current, linha);
            return;
        }
    }

    Input* nova = newEntry(nome, id, linha);
    nova->next = table[indice];
    table[indice] = nova;
}

// Função que imprime a tabela de símbolos
void showTable()
{
    for (int i = 0; i < TAM_HASH; i++)
    {
        Input* current = table[i];
        while (1)
        {
            if (current == NULL)
                break;
            printf("%s -> ", current->nome);
            Line* currentLine = current->lines;
            while (1)
            {
                if (currentLine == NULL)
                    break;
                printf("%d", currentLine->num);
                if (currentLine->next != NULL)
                    printf(" | ");
                currentLine = currentLine->next;
            }
            printf("\n");
            current = current->next;
        }
    }
}

int main(void)
{
    TipoToken token;
    TipoIdentificador id;
    char nome[MAX_NOME + 1];
    int line;

    for (int i = 0; i < TAM_HASH; i++)
    {
        table[i] = NULL;
    }

    pegaToken(&token, &id, nome, &line);
    while (1)
    {
        if (token == Fim)
            break;
        insertTable(token, id, nome, line);
        pegaToken(&token, &id, nome, &line);
    }

    showTable();
    return 0;
}

// Função que obtem o próximo token da entrada
void pegaToken(TipoToken* token, TipoIdentificador* id, char* nome, int* linha)
{
    static int pos = 1;
    switch (pos)
    {
    case 1:
        *token = Reservada;
        *id = String;
        strcpy(nome, "program");
        *linha = 1;
        break;
    case 2:
        *token = Variavel;
        *id = String;
        strcpy(nome, "calcula");
        *linha = 1;
        break;
    case 3:
        *token = Reservada;
        *id = String;
        strcpy(nome, ";");
        *linha = 1;
        break;
    case 4:
        *token = Reservada;
        *id = String;
        strcpy(nome, "var");
        *linha = 2;
        break;
    case 5:
        *token = Variavel;
        *id = Inteiro;
        strcpy(nome, "i");
        *linha = 3;
        break;
    case 6:
        *token = Reservada;
        *id = String;
        strcpy(nome, ",");
        *linha = 3;
        break;
    case 7:
        *token = Variavel;
        *id = Inteiro;
        strcpy(nome, "n");
        *linha = 3;
        break;
    case 8:
        *token = Reservada;
        *id = String;
        strcpy(nome, ":");
        *linha = 3;
        break;
    case 9:
        *token = Reservada;
        *id = String;
        strcpy(nome, "integer");
        *linha = 3;
        break;
    case 10:
        *token = Reservada;
        *id = String;
        strcpy(nome, ";");
        *linha = 3;
        break;
    case 11:
        *token = Reservada;
        *id = String;
        strcpy(nome, "begin");
        *linha = 4;
        break;
    case 12:
        *token = Variavel;
        *id = Inteiro;
        strcpy(nome, "n");
        *linha = 5;
        break;
    case 13:
        *token = Reservada;
        *id = String;
        strcpy(nome, ":=");
        *linha = 5;
        break;
    case 14:
        *token = Constante;
        *id = Inteiro;
        strcpy(nome, "0");
        *linha = 5;
        break;
    case 15:
        *token = Reservada;
        *id = String;
        strcpy(nome, ";");
        *linha = 5;
        break;
    case 16:
        *token = Reservada;
        *id = String;
        strcpy(nome, "for");
        *linha = 6;
        break;
    case 17:
        *token = Variavel;
        *id = Inteiro;
        strcpy(nome, "i");
        *linha = 6;
        break;
    case 18:
        *token = Reservada;
        *id = String;
        strcpy(nome, ":=");
        *linha = 6;
        break;
    case 19:
        *token = Constante;
        *id = Inteiro;
        strcpy(nome, "1");
        *linha = 6;
        break;
    case 20:
        *token = Reservada;
        *id = String;
        strcpy(nome, "to");
        *linha = 6;
        break;
    case 21:
        *token = Constante;
        *id = Inteiro;
        strcpy(nome, "10");
        *linha = 6;
        break;
    case 22:
        *token = Reservada;
        *id = String;
        strcpy(nome, "do");
        *linha = 6;
        break;
    case 23:
        *token = Variavel;
        *id = Inteiro;
        strcpy(nome, "n");
        *linha = 7;
        break;
    case 24:
        *token = Reservada;
        *id = String;
        strcpy(nome, ":=");
        *linha = 7;
        break;
    case 25:
        *token = Variavel;
        *id = Inteiro;
        strcpy(nome, "n");
        *linha = 7;
        break;
    case 26:
        *token = Reservada;
        *id = String;
        strcpy(nome, "+");
        *linha = 7;
        break;
    case 27:
        *token = Variavel;
        *id = Inteiro;
        strcpy(nome, "i");
        *linha = 7;
        break;
    case 28:
        *token = Reservada;
        *id = String;
        strcpy(nome, "*");
        *linha = 7;
        break;
    case 29:
        *token = Constante;
        *id = Inteiro;
        strcpy(nome, "10");
        *linha = 7;
        break;
    case 30:
        *token = Reservada;
        *id = String;
        strcpy(nome, ";");
        *linha = 7;
        break;
    case 31:
        *token = Reservada;
        *id = String;
        strcpy(nome, "end");
        *linha = 8;
        break;
    case 32:
        *token = Reservada;
        *id = String;
        strcpy(nome, ".");
        *linha = 8;
        break;
    default:
        *token = Fim;
    }
    pos++;
}
