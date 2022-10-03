#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
	int destino;
	int custo;
	struct lista *prox;
}	lista;

void Inicializar (lista **g, int n)
{
	int i;
	for (i = 0; i <= n; i ++) g[i] = NULL;
}

lista *InserirLista (lista *l, int d, int c)
{
	lista *no = (lista *) malloc (sizeof (lista));
	no->destino = d;
	no->custo = c;
	no->prox = l;
	return no;
}

void InserirAresta (lista **g, int origem, int destino, int custo) 
{
	g[origem] = InserirLista (g[origem], destino, custo);
}

void ImprimirLista (lista *l)
{
	if (l != NULL)
	{
		printf ("-(%d, %d)", l->destino, l->custo);
		ImprimirLista (l->prox);
	}
}

void ImprimirGrafo (lista **g, int n)
{
	int i;
	printf ("Grafo: ");
	for (i = 0; i <= n; i ++)
	{
		printf ("\n\t%d", i);
		ImprimirLista (g[i]);
	}
}

lista *RemoverLista (lista *l, int d)
{
	lista *aux = l;
	if (l->destino == d)
	{
		l = l->prox;
		free (aux);
	}
	else l->prox = RemoverLista (l->prox, d);
	return l;
}

void RemoverAresta (lista **g, int origem, int destino)
{
	g[origem] = RemoverLista (g[origem], destino);
}

int ContS (lista *l)
{
    if (l == NULL) return 0;
    return 1 + ContS (l->prox);
}

int GS (lista **g, int origem)
{
    return ContS (g[origem]);
}

int ContE (lista *l, int destino)
{
    if (l == NULL) return 0;
    if (l->destino == destino) return 1 + ContE (l->prox, destino);
    return ContE (l->prox, destino);
}

int GE (lista **g, int origem, int n)
{
    int cont = 0, i;
    for (i = 1; i <= n; i++) cont += ContE (g[i], origem);
    return cont;
}

int ContaArestas (lista *l)
{
    if (l == NULL) return 0;
    return 1 + ContaArestas (l->prox);
}

int GrafoCompleto (lista **g, int n)
{
    int arestas = 0, i;
    for (i = 1; i <= n; i ++) arestas += ContaArestas (g[i]);
    if (arestas != (n* (n - 1))) return 0;
    return 1;
}

int main () 
{
	int cmd = 0, n, gs, ge, teste, dado, dado1, dado2;
  
  printf("Digite o tamanho do grafo: ");
	scanf("%d",&n);
  
  lista *g[n];
  Inicializar (g, n);
  
  while (cmd != 6)
  {
  	printf ("1: Inserir uma aresta no grafo\n");
		printf ("2: Remover uma aresta do grafo\n");
		printf ("3: Imprimir grafo\n");
		printf ("4: Imprimir os graus de entrada e sa[ida de um vertice\n");
		printf ("5: Verificar se um grafo e completo\n");
		printf ("6: Sair\n");
		printf ("Escolha: ");
		scanf ("%d", &cmd);
		printf ("\n");
	
		switch (cmd)
		{
			case 1:
				printf ("Digite a origem dessa aresta, o destino e o custo\n");
				scanf ("%d %d %d", &dado, &dado1, &dado2);
				printf ("\n");
				InserirAresta (g, dado, dado1, dado2);
			break;
			case 2:
				printf("Escolha a origem e o destino:\n");
				scanf ("%d %d", &dado, &dado1);
				RemoverAresta(g, dado, dado1);
			break;
			case 3:
				ImprimirGrafo(g, n);
				printf ("\n\n");
			break;
			case 4:
				printf ("Digite o vertice\n");
				scanf ("%d", &dado);
				printf("Gs do vertice %d e: %d entradas\n", dado, GE (g, dado, n));
				printf("Grau de saidas do vertice %d e: %d saidas", dado, GS (g, dado));
				printf ("\n");
			break;
			case 5:
                if (GrafoCompleto (g, n)) printf ("O grafo esta completo\n");
                else printf("O grafo nao esta completo\n");
                printf ("\n");
			break;
			case 6:
				
			break;
		}
	}
	
	return 0;
}
