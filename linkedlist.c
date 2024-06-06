#include <stdio.h>
#include <stdlib.h>

typedef struct Teste_
{
	int value;
	struct Teste_* node;
} Teste;

Teste* criarLista(Teste* node, int value)
{
	Teste* teste = (Teste*)malloc(sizeof(Teste));
	if (teste == NULL) { return NULL; }
	teste->value = value;
	teste->node = node;
	return teste;
}

//Aloca espaço na memória do tamanho de "Teste"

void mostra(Teste* node)
{
	printf("Mostrando a lista: ");
	if (node == NULL)
	{
		printf("Lista vazia.\n");
		return;
	}
	while (node != NULL)
	{
		printf("%d ", node->value);
		node = node->node;
	}
	printf("\n");
}
// Se o primeiro nó apontar para um valor nulo, retorna que a lista está vazia. Caso contrário, percorre toda lista (enquanto imprime na tela do usuário, até encontrar um nó que aponte para o valor nulo, o que indicará o fim da lista.


void mostraEspecifico(Teste* node, int index)
{
	printf("Mostrando elemento especifico: ");
	if (node == NULL)
	{
		printf("Lista vazia.\n");
		return;
	}
	if (index < 0)
	{
		printf("Index invalido\n");
		return;
	}
	int idx = 0;
	while (idx < index)
	{
		if (node->node == NULL)
		{
			printf("Index maior que a lista\n");
			return;
		}
		idx++;
		node = node->node;
	}
	printf("%d\n", node->value);
}
//Se o primeiro nó tiver um valor NULL, indicará que a lista está vazia. Se o index (posicao escolhida pelo usuario) for menor que 0, retornará que é uma posição inválida. Caso contrário, entrará na estrutura de repetição "while" para procurar a posição solicitada, se no meio da busca da posição solicitada encontrar um nó apontando para um nó com valor nulo, irá informar ao usuário que a posição escolhida é maior que a lista criada.

Teste* inserirNoInicio(Teste* startNode, int value)
{
	if (startNode == NULL)
	{
		printf("Lista vazia.\n");
		return NULL;
	}
	Teste* newNode = criarLista(startNode, value);
	printf("%d inserido no inicio da lista.\n", value);
	return newNode;
}
// Caso o primeiro nó seja nulo, informará ao usuário que a lista está vazia. Caso contrário, insere o valor "value" escolhido pelo usuário no início da lista. 

Teste* inserirNoFinal(Teste* startNode, int value)
{
	if (startNode == NULL)
	{
		printf("Lista vazia.\n");
		return startNode;
	}
	Teste* newNode = criarLista(NULL, value);
	Teste* node = startNode;
	while (node->node != NULL)
	{
		node = node->node;
	}
	node->node = newNode;
	printf("%d inserido no final da lista.\n", newNode->value);
	return startNode;
}

// Caso o primeiro nó seja nulo, informará ao usuário que a lista está vazia. Caso contrário, percorre toda a lista até que encontre um nó que aponte para um valor NULO (o que indicará o fim da lista e, consequentemente, o ultimo nó) e insere o nó solicitado pelo usuário após o nó encontrado.

Teste* inserirNoMeio(Teste* startNode, int value, int index)
{
	if (index < 0)
	{
		printf("Index invalido\n");
		return startNode;
	}
	if (index == 0)
	{
		return inserirNoInicio(startNode, value);
	}
	index -= 1;

	Teste* node = startNode;
	int idx = 0;
	while (idx < index)
	{
		if (node->node == NULL)
		{
			printf("Index maior que a lista\n");
			return startNode;
		}
		idx++;
		node = node->node;
	}
	Teste* nextNode = criarLista(node->node, value);
	node->node = nextNode;
	printf("%d inserido na posicao %d da lista.\n", node->node->value, index + 1);
	return startNode;
}
// Caso o index (posicao na lista) informado pelo usuário seja menor do que zero, retornará que é um valor inválido. Caso seja igual a zero, irá chamar a função inserirNoInicio, já que corresponderá à primeira posição. Caso contrário, percorre a lista até encontrar o nó da posição anterior ao solicitado pelo usuário , depois disso cria o nó com o valor inserido pelo usuário na posição solicitada (Ex: Usuário solicitou criação de um nó com valor 100 na posição 5. O programa irá procurar o nó na posição 4 e criará o nó solicitado após o nó na posição 4).
Teste* excluirNoInicio(Teste* startNode)
{
	Teste* node = startNode;
	if (startNode == NULL)
	{
		printf("Lista vazia.\n");
		return NULL;
	}
	printf("%d excluido no inicio da lista.\n", startNode->value);
	Teste* newNode = node->node;
	free(startNode);
	return newNode;
}
// Caso o primeiro nó seja nulo, informará ao usuário que a lista está vazia. Caso contrário, remove o primeiro nó encontrado.
Teste* excluirNoFinal(Teste* startNode)
{
	if (startNode == NULL)
	{
		printf("Lista vazia.\n");
		return startNode;
	}
	Teste* node = startNode;
	while (node->node != NULL && node->node->node != NULL)
	{
		node = node->node;
	}
	printf("%d excluido no final da lista.\n", node->node->value);
	free(node->node);
	node->node = NULL;
	return startNode;
}
// Caso o primeiro nó seja nulo, informará ao usuário que a lista está vazia. Caso contrário, percorre toda a lista até que encontre um nó que aponte para um valor NULO (o que indicará o fim da lista e, consequentemente, o ultimo nó) e exclui o nó encontrado.

Teste* excluirNoMeio(Teste* startNode, int index)
{
	if (startNode == NULL)
	{
		printf("Lista vazia.\n");
		return startNode;
	}
	if (index < 0)
	{
		printf("Index invalido\n");
		return startNode;
	}
	if (index == 0)
	{
		return excluirNoInicio(startNode);
	}
	index -= 1;
	Teste* nextNode = NULL;
	Teste* node = startNode;
	int idx = 0;
	while (idx < index)
	{
		if (node->node == NULL)
		{
			printf("Index maior que a lista\n");
			return startNode;
		}
		idx++;
		node = node->node;
	}
	if (node->node != NULL && node->node->node != NULL)
	{
		nextNode = node->node->node;
	}
	printf("%d excluido na posicao %d da lista.\n", node->node->value, index + 1);
	free(node->node);
	node->node = nextNode;
	return startNode;
}
// Caso o index (posicao na lista) informado pelo usuário seja menor do que zero, retornará que é um valor inválido. Caso seja igual a zero, irá chamar a função excluirNoInicio, já que corresponderá à primeira posição. Caso contrário, percorre a lista até encontrar o nó da posição anterior ao solicitado pelo usuário, depois disso cria o nó com o valor inserido pelo usuário na posição solicitada (Ex: Usuário solicitou exclusão de um nó com valor 100 na posição 5. O programa irá procurar o nó na posição 4 e deletará o nó posterior.)
Teste* esvaziar(Teste* startNode)
{
	Teste* node = startNode;
	while (startNode->node != NULL)
	{
		node = excluirNoFinal(startNode);
	}
	free(node);
	return NULL;
}
//Enquanto o nó estiver apontando para um outro nó com valor válido, este nó será excluído. Ao encontrar o ultimo nó, que estará apontando para um valor NULL, sairá da estrutura de repetição e será excluído com free(node);
int main()
{
	Teste* lista = criarLista(NULL, 0); // 0

	int value, index;
	int command;
	while (1)
	{
		printf("-------------------------------------\n");
		printf("Menu De Opcoes\n");
		printf("-------------------------------------\n");
		printf("[1] Adicionar no inicio da lista\n");
		printf("[2] Adicionar no final da lista\n");
		printf("[3] Adicionar em um ponto especifico\n");
		printf("[4] Listar todos os elementos da lista\n");
		printf("[5] Listar um elemento especifico da lista\n");
		printf("[6] Excluir do inicio da lista\n");
		printf("[7] Excluir do final da lista\n");
		printf("[8] Excluir de um ponto especifico da lista\n");
		printf("[9] Liberar os elementos e mostrar a lista vazia\n");
		printf("[0] Terminar\n");
		printf("-------------------------------------\n");
		printf("Qual a sua opcao?\n");
		scanf_s("%d", &command);
		system("cls");
		if (command == 0)
		{
			printf("Terminado\n");
			break;
		}
		else if (command == 1)
		{
			printf("Digite o valor: ");
			scanf_s("%d", &value);
			printf("\n");
			lista = inserirNoInicio(lista, value);
		}
		else if (command == 2)
		{
			printf("Digite o valor: ");
			scanf_s("%d", &value);
			printf("\n");
			lista = inserirNoFinal(lista, value);
		}
		else if (command == 3)
		{
			printf("Digite o valor e a posicao [valor posicao]: ");
			scanf_s("%d %d", &value, &index);
			printf("\n");
			lista = inserirNoMeio(lista, value, index);
		}
		else if (command == 4)
		{
			mostra(lista);
		}
		else if (command == 5)
		{
			printf("Digite a posicao: ");
			scanf_s("%d", &index);
			printf("\n");
			mostraEspecifico(lista, 2);
		}
		else if (command == 6)
		{
			excluirNoInicio(lista, value);
		}
		else if (command == 7)
		{
			lista = excluirNoFinal(lista, value);
		}
		else if (command == 8)
		{
			printf("Digite a posicao: ");
			scanf_s("%d %d", &value, &index);
			printf("\n");
			lista = excluirNoMeio(lista, index);
		}
		else if (command == 9)
		{
			lista = esvaziar(lista);
		}
	}

	return 0;

	/*lista = inserirNoFinal(lista, 1); // 0 1
	lista = inserirNoFinal(lista, 2); // 0 1 2
	lista = inserirNoFinal(lista, 3); // 0 1 2 3

	lista = inserirNoInicio(lista, 11); // 11 0 1 2 3
	lista = inserirNoFinal(lista, 22); // 11 0 1 2 3 22
	lista = inserirNoMeio(lista, 33, 4); // 11 0 1 2 33 3 22

	lista = excluirNoInicio(lista); // 0 1 2 33 3 22
	lista = excluirNoFinal(lista); // 0 1 2 33 3
	lista = excluirNoMeio(lista, 3); // 0 1 2 3

	mostraEspecifico(lista, 2); // 2
	mostra(lista); // 0 1 2 3

	lista = esvaziar(lista); // vazia*/
}
