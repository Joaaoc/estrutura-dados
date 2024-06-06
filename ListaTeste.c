#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Fun��o que cria o n�
typedef struct no{
	int elemento;
	struct no *proximo;
}No;

//Fun��o para alocar a mem�ria
No *alocar(){
	No *novo = (No*) malloc(sizeof(No));
	if(!novo){
		printf("N�o h� mem�ria dispon�vel!");
		exit(1);
	}
	return novo;
}

//Declara��o de uma vari�vel para definir o tamanho da lista
int tamanhoDaLista;


void IniciarLista(No *lista){
	lista->proximo = NULL;
	tamanhoDaLista = 0;
}


/*------------------------------------------Fun��es para inserir dados na lista----------------------------------*/
//Fun��o que insere um elemento no in�cio da lista.
void InserirNoComeco(No *lista){
	No *novo = alocar();
	novo->proximo = lista->proximo;
	lista->proximo = novo;
	printf("Digite um valor, por favor: ");
	scanf("%d", &novo->elemento);
		
	tamanhoDaLista++;
}

//Fun��o que insere um novo elemento na posi��o escolhida pelo usu�rio.
void InserirOndeEscolher (No *lista){
	int posicao;
	
	printf("Em qual posi��o, de 1 � %d, deseja inserir o novo elemento? ", tamanhoDaLista);
	scanf("%d", &posicao);
	
	if(posicao > 0 && posicao <= tamanhoDaLista){
		if(posicao == 1){
			InserirNoComeco(lista);
		}
		else{
			No *atual = lista->proximo;
			No *anterior = lista;
			No *novo = alocar();
			for( int contagem = 1; contagem < posicao; contagem++){
				anterior = atual; atual = atual->proximo;
			}
			anterior->proximo = novo;
			novo->proximo = atual;
			printf("Qual o novo elemento? ");
			scanf("%d", &novo->elemento);
			
			tamanhoDaLista++;
		}
			
	}
	else{
		printf("Elemento inv�lido! Tente novamente.");	
	}
}

//Fun��o que insere um novo elemento no fim da lista.
void InserirNoFim (No *lista){
	No *novo = alocar();
	
	novo->proximo = NULL;
	if(lista->proximo == NULL)
		lista->proximo = novo;
	else{
		No *temporario = lista->proximo;
		while(temporario->proximo != NULL)
			temporario = temporario->proximo;
		temporario->proximo = novo;
	}
	printf("Digite o novo elemento: ");
	scanf("%d", &novo->elemento);
	
	tamanhoDaLista++;
}

/*-----------------------------Fun��es para remover itens da lista--------------------------------------*/

//Fun��o para remover um item do come�o da lista.
void ExcluirDoComeco(No *lista){
	if(lista->proximo == NULL)
		printf("N�o h� nada na lista! Lista vazia!");
	
	else{
		No *temporario = lista->proximo;
		lista->proximo = temporario->proximo;
		printf("Elemento %d foi removido com sucesso!", temporario->elemento);
		free(temporario);
		tamanhoDaLista--;
	}
	printf("\n\n");
	system("PAUSE");
}


//Fun��o para remover um elemento escolhido pelo usu�rio.
void RemoverOndeEscolher(No *lista){

    if(lista->proximo == NULL){
        printf("A lista est� vazia!\n");
        system("PAUSE");
        return;
    }
	int posicao;
	
	printf("Em qual posi��o, de 1 � %d, deseja retirar um elemento? ", tamanhoDaLista);
	scanf("%d", &posicao);
	
	if(posicao > 0 && posicao <= tamanhoDaLista){
		if(posicao == 1){
			return ExcluirDoComeco(lista);
		}
		else{
			No *atual = lista->proximo;
			No *anterior = lista;
			
			for(int contagem = 1; contagem < posicao; contagem++){
				anterior = atual;
				atual = atual->proximo;
			}
			anterior->proximo = atual->proximo;
			tamanhoDaLista--;
            free(lista);
			printf("Elemento %d foi removido com sucesso!", atual->elemento);
            printf("\n");
			system("PAUSE");
		}
	}
}


//Fun��o para remover um elemento do final da lista.
void ExcluirDoFim(No *lista){
	
	if(lista->proximo == NULL){

        printf("N�o h� elementos na lista! Lista vazia!\n");
        system("PAUSE");
    }
	else{
        No *ultimo = lista->proximo;
        No *penultimo = lista;
        
        while(ultimo->proximo != NULL){
            penultimo = ultimo;
            ultimo = ultimo->proximo;
        }
        penultimo->proximo = NULL;
        printf("Elemento %d foi removido com sucesso!", ultimo->elemento);
        free(ultimo);
        tamanhoDaLista--;
        printf("\n\n");
        system("PAUSE");
    }
        
}

/*--------------------------------------------Fun��es para imprimir e limpar a lista-------------------------------------*/

//Fun��o para imprimir a lista completa.
void MostrarLista(No *lista){
	No *atual = lista->proximo;
	if(atual == NULL){
		printf("Lista vazia!\n");
        system("PAUSE");
		return;
	}
	
    printf("Elementos existentes na lista: \n");
	while(atual != NULL){
		printf("%d ", atual->elemento);
		atual = atual->proximo;
	}
    printf("\nQuantidade total de elementos: %d", tamanhoDaLista);
    printf("\n");
    system("PAUSE");
}

//Fun��o para imprimir um elemento selecionado da lista.
void MostrarItemEspecifico(No *lista){

    if(lista->proximo == NULL){
        printf("A lista est� vazia!\n");
        system("PAUSE");
        return;
    }

	int posicao;
	
	printf("Em qual posi��o, de 1 � %d, deseja consultar um elemento espec�fico?\n", tamanhoDaLista);
	scanf("%d", &posicao);
	
	if(posicao > 0 && posicao <= tamanhoDaLista){
		No *atual = lista->proximo;
		No *anterior = lista;
		
		for(int contagem = 1; contagem < posicao; contagem++){
			anterior = atual;
			atual = atual->proximo;
		}
		system("CLS");
		printf("Valor do elemento na posi��o %d �: %d", posicao, atual->elemento);
		printf("\n\n");
		system("PAUSE");
	}
}


//Fun��o para limpar a lista e mostrar ela vazia.
void LimparLista(No *lista){
	No *atual = lista->proximo, *imediato;
	while(atual != NULL){
		imediato = atual->proximo;
		free(atual);
		atual = imediato;
	}
	
	IniciarLista(lista);
    printf("Liberando elementos da lista...\n");
    system("PAUSE");
}

/*---------------------------------------Fun��o principal--------------------------------------*/

int main(){
	
	No *lista = alocar();
	IniciarLista(lista);
	int opcao;
    setlocale(LC_ALL, "Portuguese_Brazil");
	
	do{
		system ("CLS");
		printf("\n-------------------------------------------------------------\n");
		printf("                       MENU DE OP��ES\n");
		printf("-------------------------------------------------------------\n");
		printf("[1] Adicionar no in�cio da lista\n");
		printf("[2] Adicionar no final da lista\n");
		printf("[3] Adicionar em um ponto espec�fico da lista\n");
		printf("[4] Listar todos os elementos da lista\n");
		printf("[5] Listar um elemento espec�fico da lista\n");
		printf("[6] Excluir do in�cio da lista\n");
		printf("[7] Excluir do final da lista\n");
		printf("[8] Excluir de um ponto espec�fico da lista\n");
		printf("[9] Liberar os elementos e mostrar a lista vazia\n");
		printf("[0] Terminar\n");
		printf("------------------------------------------------------------\n");
		printf("Qual a sua op��o? ");
		scanf("%d", &opcao);
		system("CLS");
		
		switch(opcao){
			case 1:
				InserirNoComeco(lista);
				break;
				
			case 2:
				InserirNoFim(lista);
				break;
				
			case 3:
				InserirOndeEscolher(lista);
				break;
				
			case 4:
				MostrarLista(lista);
				break;
				
			case 5:
                MostrarItemEspecifico(lista);
				break;
				
			case 6:
				ExcluirDoComeco(lista);
				break;
				
			case 7:
				ExcluirDoFim(lista);
				break;
				
			case 8:
				RemoverOndeEscolher(lista);
				break;
				
			case 9:
				LimparLista(lista);
				break;
				
			case 0:
				printf("Programa finalizado!");
				break;
				
			default:
				printf("Op��o inv�lida! Tente novamente.\n\n");
                system("PAUSE");
		}
	}while(opcao != 0);
	
	return 0;
}