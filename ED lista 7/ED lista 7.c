#include <stdio.h>
#include <stdlib.h>


typedef struct lista
{
	int destino;
	int custo;
	struct lista *prox;
}lista;

void inicializarLista(lista **g, int n)
{
	int i;
	for(i = 1; i <= n; i++)
		g[i] = NULL;
}

lista *inserirLista(lista *g, int destino, int custo)
{
	lista *no = (lista*) malloc(sizeof(lista));
	no->destino = destino;
	no->custo = custo;
	no->prox = g;
	return no;
}

void inserirAresta(lista **g, int origem, int destino, int custo)
{
	g[origem] = inserirLista(g[origem], destino, custo);
}

void removerAresta(lista **g, int origem, int destino)
{
	lista *ant = NULL;
	lista *i;
	for(i = g[origem]; i != NULL; i = i->prox)
	{
		if(i->destino == destino)
		{
			if(ant == NULL)
			{
				g[origem] = g[origem]->prox;
				free(i);
				break;
			}
			else
			{
				ant->prox = i->prox;
				free(i);
				break;
			}
		}
		ant = i;
	}
}

int grauSaida(lista **g, int vertice)
{
	int count = 0;
	lista *i;
	for(i = g[vertice]; i != NULL; i = i->prox)
		count++;
	return count;
}

int grauEntrada(lista **g, int n, int vertice)
{
	int count = 0;
	int i;
	for(i = 1; i <= n; i++)
	{
		lista *j;
		for(j = g[i]; j != NULL; j = j->prox)
		{
			if(j->destino == vertice)
				count++;
		}
	}
	return count;
}

int grafoCompleto(lista **g, int n)
{
	int count = 0;
	int i;
	for(i = 1; i <= n; i++)
	{
		lista *j;
		for(j = g[i]; j != NULL; j = j->prox)
		{
			count++;
		}
	}
	if(count == (n * (n - 1)))
		return 1;
	else
		return 0;
}
void imprimirGrafo(lista **g, int n)
{
	int i;
	for(i = 1; i <= n; i++)
	{
		printf("Grafo %d: ", i);
		lista *j;
		for(j = g[i]; j != NULL; j = j->prox)
		{
			printf("(%d %d) ", j->destino, j->custo);
		}
	}
	printf("\n");
}

int existe(int *vet, int valor, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		if(vet[i] == valor)
			return 1;
	}
	return 0;
}
int calcCusto(lista **g, int origem, int dest)
{
	lista *t;
	for(t = g[origem]; t != NULL; t = t->prox)
		if(t->destino == dest)
			return t->custo;
}
void caminhos(lista **g, int b, int *vet, int pos, int *menorCusto, int *vetMenorCusto, int *menorCaminho, int opcao, int *posAnt)
{
	if(vet[pos - 1] == b)
	{
		if(opcao == 1)
		{
		printf("\n");
		int i;
		for(i = 0; i < pos;i++)
			printf("%d", vet[i]);
		}
		else
			if(opcao == 2)
				if(pos < *posAnt)
				{
					int i;
					for(i = 0; i < pos; i++)
						menorCaminho[i] = vet[i];
					*posAnt = pos;
				}
			else
			{
				int aux = 0, soma = 0;
				int i;
				for(i = 1; i < pos; i++)
				{
					soma = soma + calcCusto(g, vet[aux], vet[i]);
					aux++;
				}
				if(soma < *menorCusto)
				{
					*menorCusto = soma;
					*posAnt = pos;
					int i;
					for(i = 0; i < pos; i++)
						vetMenorCusto[i] = vet[i];
				}
			}
	}
	else
	{
		lista *p = g[vet[pos - 1]];
		while(p != NULL)
		{
			if(!existe(vet, p->destino, pos))
			{
				vet[pos] = p->destino;
				caminhos(g, b, vet, pos + 1, menorCusto, vetMenorCusto, menorCaminho, opcao, posAnt);
			}
		}
		p = p->prox;
	}
}
int main()
{
	int menu = 0;
	int origem, destino, custo, vertices, gs, ge, aux, menorCusto = 1000000, posAnt = 6;
	printf("Qual eh a quantidade de vertices?\n");
	scanf("%d", &vertices);
	lista **g = (lista**) malloc((vertices+1)*sizeof(lista*));
	int *vet = (int*) malloc(vertices*sizeof(lista));
	int *menorCaminho = (int*) malloc(vertices*sizeof(lista));
	int *vetMenorCusto = (int*) malloc(vertices*sizeof(lista));
	printf("----------------------------MENU----------------------------\n1- Inserir uma aresta no grafo\n2- Remover uma aresta do grafo\n3- Imprimir grafo\n4- Imprimir os graus de entrada e saida de um vertice\n5- Verificar se um grafo eh completo\n6- Imprimir todos os caminhos entre uma origem e um destino\n7- Imprimir o caminho mais curto(com menor numero de arestas)\n8- Imprimir o caminho de menor custo(menor soma dos custos das arestas)\n9- Sair \n");
	scanf("%d", &menu);
	inicializarLista(g, vertices);
	while(menu >= 0 && menu < 9)
	{
		int i;
		switch(menu)
		{
			case 1: printf("Qual eh a origem?\n");
					scanf("%d", &origem);
					printf("Qual eh o destino?\n");
					scanf("%d", &destino);
					printf("Qual eh o custo?\n");
					scanf("%d", &custo);
					inserirAresta(g, origem, destino, custo);
					break;
			case 2: printf("Qual eh a origem?\n");
					scanf("%d", &origem);
					printf("Qual eh o destino?\n");
					scanf("%d", &destino);
					removerAresta(g, origem, destino);
					break;
			case 3:	imprimirGrafo(g, vertices);
					break;
			case 4:	printf("Qual eh o vertice?\n");
					scanf("%d", &origem);
					gs = grauSaida(g, origem);
					ge = grauEntrada(g, vertices, origem);
					printf("O grau de entrada eh %d e o de saida eh %d\n", ge, gs);
					break;
			case 5: aux = grafoCompleto(g, vertices);
					if(aux == 1)
						printf("O grafo eh completo!\n");
					else
						printf("O grafo nao eh completo!\n");		
			case 6: printf("Qual eh a origem?\n");
					scanf("%d", &origem);
					printf("Qual eh o destino?\n");
					scanf("%d", &destino);
					vet[0] = origem;
					caminhos(g, destino, vet, 1, &menorCusto, vetMenorCusto, menorCaminho, 1, &posAnt);
					break;
			case 7: printf("Qual eh a origem?\n");
					scanf("%d", &origem);
					printf("Qual eh o destino?\n");
					scanf("%d", &destino);
					vet[0] = origem;
					caminhos(g, destino, vet, 1, &menorCusto, vetMenorCusto, menorCaminho, 2, &posAnt);
					for(i = 0; i < posAnt; i++)
						printf("%d ", menorCaminho[i]);
					break;
			case 8: printf("Qual eh a origem?\n");
					scanf("%d", &origem);
					printf("Qual eh o destino?\n");
					scanf("%d", &destino);
					vet[0] = origem;
					caminhos(g, destino, vet, 1, &menorCusto, vetMenorCusto, menorCaminho, 3, &posAnt);
					printf("O caminho com menor custo é o: ");
					for(i = 0; i < posAnt; i++)
						printf("%d ", vetMenorCusto[i]);
					printf("com um custo de %d\n", menorCusto);
					break;
		}
		printf("----------------------------MENU----------------------------\n1- Inserir uma aresta no grafo\n2- Remover uma aresta do grafo\n3- Imprimir grafo\n4- Imprimir os graus de entrada e saida de um vertice\n5- Verificar se um grafo eh completo\n6- Imprimir todos os caminhos entre uma origem e um destino\n7- Imprimir o caminho mais curto(com menor numero de arestas)\n8- Imprimir o caminho de menor custo(menor soma dos custos das arestas)\n9- Sair \n");
		scanf("%d", &menu);
	}
	
	return 0;
}
