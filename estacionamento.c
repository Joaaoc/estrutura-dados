#include <stdio.h>
#include <stdlib.h>

#define LIMP "\e[0m" //Esses defines são responsáveis por colorir o "prinf()".
#define VERM "\e[38;5;196m"
#define VERD "\e[38;5;46m"
#define AZUL "\e[38;5;21m"

typedef struct lista{
    int dado;
    struct lista *proximo;
}Celula;

//Para checar se o ponteiro está vazio.
int checVazio(Celula *topo){
    return !topo;
}

//Função para empurrar elementos para a pilha.
void Push(Celula **topo, int valor, int *vaga_ocup, int *vaga_disp){

    *vaga_ocup = *vaga_ocup + 1;
    *vaga_disp = *vaga_disp - 1;

    //Cria um ponteiro com o espaço desta função.
    Celula *novo = malloc(sizeof(Celula));

    //Este ponteiro então recebe um valor.
    novo -> dado = valor;
    //E recebe um ponteiro anterior.
    novo -> proximo = *topo;

    //Apos isso o ponteiro topo recebe esses valores e assim por diante.
    *topo = novo;
}

//Função para retirar elemento da pilha.
int Pop(Celula **topo, int *vaga_ocup, int *vaga_disp){

    if (checVazio(*topo)){
        printf("A vaga esta vazia.\n\n--------------------");
        return 0;
    }
    else{
        *vaga_ocup = *vaga_ocup - 1;
        *vaga_disp = *vaga_disp + 1;

        //"temp" irá receber os valores de "topo".
        Celula *temp = *topo;
        //E "topo" irá receber o valor de "topo.proximo" ou seja, o ponteiro anterior.
        *topo = (*topo)->proximo;

        int valorTirado = temp->dado;
        free(temp);
        temp = NULL;
        return valorTirado;
    }
}

//Função para retirar elementos do meio da pilha realocando os acimas e os voltando depois.
void Desengarrafar(Celula **topo, int posicao, int *vaga_ocup, int *vaga_disp){

    if(checVazio(*topo)){
        printf("A vaga esta vazia.\n\n--------------------");
        return;
    }

    Celula *temp = NULL;
    int posicaoAtual = 0, manobra = 0;

    //Enquanto a posição atual for menor que a posição(vaga) escolhida - 1 e o ponteiro não estiver vazio.
    while(posicaoAtual < posicao - 1 && !checVazio(*topo))
    {
        //Os valores de topo serão retirados (pela função pop) e irão entrar em "temp" por meio da função push.
        //"vaga_ocup e "vaga_disp" servem para organização.
        Push(&temp, Pop(topo, vaga_ocup, vaga_disp), vaga_ocup, vaga_disp);
        posicaoAtual++;
        manobra++;
    }

    //Caso a posição atual seja diferente da posição e o ponteiro não estiver vazio.
    if(posicaoAtual != posicao && !checVazio(*topo)){
        //Irá imprimir a quantidade de manobras e o carro que foi removido acima.
        printf("Vezes que carros foram manobrados: %d\n", manobra);
        int elemRemovido = Pop(topo, vaga_ocup, vaga_disp);
        printf("Carro com a placa "AZUL"RJ"LIMP"-%05d da vaga %d foi retirado.\n\n--------------------", elemRemovido, posicao);
    }
    else{
        //Caso a vaga escolhida não tenha nenhum carro porem o ponteiro não esteja vazio.
        printf("Esta vaga esta vazia, tente outra posicao.\n\n--------------------");
    }
    
    //Enquanto o ponteiro temporário estiver cheio, irá acontecer o processo inverso,
    //colocando todos os elementos de volta em topo, exceto o retirado (aquele -1).
    while (!checVazio(temp))
    {
        Push(topo, Pop(&temp, vaga_ocup, vaga_disp), vaga_ocup, vaga_disp);
    }
}

//Função para imprimir as vagas ocupadas.
void Imprimir(Celula *topo){

    Celula *temp;
    temp = topo;
    int vaga = 1;

    if (checVazio(topo)){
        printf("\n\nA garagem esta vazia.\n\n--------------------");
        return;
    }
    else{
        printf("\n\nCarros estacionados:\n");
        //Enquanto a variável "temp" (que recebeu os valores de "topo") não for nula.
        while(temp){
            //Irá imprimir os valores dentro de si.
            printf("\nPlaca: "AZUL"RJ"LIMP"-%05d | Vaga: %d", temp->dado, vaga);
            //E irá voltar um ponteiro até que seja nulo, imprimindo assim todos os valores.
            temp = temp->proximo;
            ++vaga;
        }
        printf("\n\n--------------------");
    }
}

int main(){
    Celula *topo = NULL;

    char opcao;
    int valor, escolha;
    int vaga_ocup = 0; //Variável para verificar a quantidade de vagas ocupadas.
    int vaga_disp = 5; //Variável para verificar a quantidade de vagas disponíveis.

/*Caso queira carros sem ter que usar input, descomente a sessão a seguir.
Os carros possuem 7 numeros/letras em suas placas visto que "RJ" 
faz parte em seus prints, porém caso queira, pode inserir mais 2 numeros.*/

/* 
    Push(&topo, 20918, &vaga_ocup, &vaga_disp);
    Push(&topo, 13370, &vaga_ocup, &vaga_disp);
    Push(&topo, 78624, &vaga_ocup, &vaga_disp);
    Push(&topo, 11011, &vaga_ocup, &vaga_disp);   
    Push(&topo, 80085, &vaga_ocup, &vaga_disp);
*/

    printf("--------------------");
    do{
        if(vaga_disp > 0){
            printf("\n   "AZUL"ESTACIONAMENTO"LIMP"   \n--------------------\n\nE - Estacionar.\nS - Sair da vaga.\nV - Ver vagas.\n\nVagas disponiveis: "VERD"%d"LIMP"\nF - Fechar programa.\n\nDigite: ", vaga_disp);
            scanf("%c", &opcao);
            printf("--------------------");
        }
        else{
            printf("\n   "AZUL"ESTACIONAMENTO"LIMP"   \n--------------------\n\nE - "VERM"Garagem cheia."LIMP"\nS - Sair da vaga.\nV - Ver vagas.\n\nVagas disponiveis: "VERM"%d"LIMP"\nF - Fechar programa.\n\nDigite: ", vaga_disp);
            scanf("%c", &opcao);
            printf("--------------------");
        }

        switch (opcao){
        case 'F':
            printf("\nSaindo...");
            break;

        case 'E':
        case 'e':
        if(vaga_ocup < 5){
            printf("\n\nDigite os 5 numeros finais da placa: ");
            scanf("%d", &valor);

            printf("\nEstacionando...");
            Push(&topo, valor, &vaga_ocup, &vaga_disp);
            printf("\nCarro placa "AZUL"RJ"LIMP"-%05d estacionado.\n\n--------------------", *topo);
            break; 
        }
        else{
            printf(VERM"\n\nA garagem se encontra cheia."LIMP"\n\n--------------------"LIMP);
            break;
        }

        case 'S':
        case 's':
            printf("\n\nDigite a vaga do carro a ser tirado: ");
            scanf("%d", &escolha);
            printf("\n");
            Desengarrafar(&topo, escolha, &vaga_ocup, &vaga_disp);
            break;

        case 'V':
        case 'v':
            Imprimir(topo);
            break;

        default:
            printf("\n\nInsira uma opcao valida.\n\n--------------------");
            break;
        }

        getchar(); //Para tirar o buffer do teclado.
    } while (opcao != 'F');
}