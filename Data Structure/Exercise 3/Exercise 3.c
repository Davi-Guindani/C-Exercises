#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree
{
	int info;
	struct tree *left, *right;
} tree;

tree *readTree (FILE *arq)
{
	int n;
	char c;
	
	fscanf (arq, "%c", &c); // lendo o '('
	fscanf (arq, "%d", &n);
	if (n == -1) // arvore nula
	{	
		fscanf (arq, "%c", &c); // lendo o ')'
		return NULL;
	}
	else // nao nula
	{
		tree *a;
		a = (tree*) malloc (sizeof (tree));
		a->info = n;
		a->left = readTree (arq);
		a->right = readTree (arq);
		fscanf (arq, "%c", &c); // lendo o ')'
		return a;
	}
}

void ImprimirPreOrdem (tree *a)
{
	if (a != NULL)
	{
		printf ("%d ", a->info);
		ImprimirPreOrdem (a->left);
		ImprimirPreOrdem (a->right);
	}
}

void ImprimirEmOrdem (tree *a)
{
	if (a != NULL)
	{
		ImprimirEmOrdem (a->left);
		printf ("%d ", a->info);
		ImprimirEmOrdem (a->right);
	}
}

void ImprimirPosOrdem (tree *a)
{
	if (a != NULL)
	{
		ImprimirPosOrdem (a->left);
		ImprimirPosOrdem (a->right);
		printf ("%d ", a->info);
	}
}

void ImprimirNivel (tree *a, int cont, int nivel)
{
	if (a != NULL)
	{
		if (cont == nivel) printf ("%d ", a->info);
		else 
		{
			ImprimirNivel (a->left, cont + 1, nivel);
			ImprimirNivel (a->right, cont + 1, nivel);
		}
	}
}

int Altura (tree *a)
{
	if (a == NULL) return 0;
	else
	{
		int hd, he;
		he = Altura (a->left);
		hd = Altura (a->right);
		if (he > hd) return he + 1;
		else return hd + 1;
	}
}

void ImprimirEmLargura (tree *a, int n)
{
	if (a != NULL && n < Altura (a))
	{
		ImprimirNivel (a, 0, n);
		printf ("\n");
		ImprimirEmLargura (a, ++n);
	} 
}

int Existe (tree * a, int n)
{
	if (a == NULL) return 0;
	else if (n == a->info) return 1;
	else if (n < a->info) return Existe (a->left, n);
	else return Existe (a->right, n);
}

int NivelNo (tree *a, int cont, int n)
{
	if (a != NULL)
	{
		if (a->info != n) 
		{
			if (n < a->info) return (NivelNo (a->left, cont + 1, n));
			else return NivelNo (a->right, cont + 1, n);
		}
		else return cont;
	}
	else return 0;
}

void ImprimirMaioresIguais (tree *a, int n)
{
	if (a!= NULL)
	{
		if (a->info >= n)
		{
			printf ("%d ", a->info);
			ImprimirMaioresIguais (a->left, n);
			ImprimirMaioresIguais (a->right, n);
		}	
		else ImprimirMaioresIguais (a->right, n);
	}
}

void ImprimirFolhasMenores (tree *a, int n)
{
	if (a != NULL)
	{
		if ((a->left == NULL) && (a->right == NULL) && (a->info < n)) printf ("%d ", a->info);
		else
		{
			if ((a->info + 2) <= n)
			{
				ImprimirFolhasMenores (a->left, n);
				ImprimirFolhasMenores (a->right, n);
			}
			else ImprimirFolhasMenores (a->left, n);
		}
	}
}

tree *Inserir (tree *a, int n)
{
	if (a == NULL)
	{
		a = (tree*)malloc(sizeof(tree));
		a->info = n;
		a->left = NULL;
		a->right = NULL;
	}
	else if (n <= a->info) a->left = Inserir (a->left, n);
	else a->right = Inserir (a->right, n);
	return a;
}

void Remover (tree **a, int n)
{
	if (*a != NULL)
	{
		if ((*a)->info == n)
		{
			if (((*a)->left == NULL) && ((*a)->right == NULL))
			{
				free (*a);
				*a = NULL;
			}
			else if ((*a)->left == NULL)
			{
				tree *aux = (*a)->right;
				free (*a);
				*a = aux;
			}
			else if ((*a)->right == NULL)
			{
				tree *aux = (*a)->left;
				free (*a);
				*a = aux;
			}
			else
			{
				tree *aux = (*a)->left;
				while (aux->right != NULL) aux = aux->right;
				(*a)->info == aux->info;
				Remover (&((*a)->left), aux->info);
			}
		}
		else if (n < (*a)->info) Remover (&((*a)->left), n);
		else Remover (&((*a)->right), n);
	}
}

void Destruir (tree *a)
{
	if (a != NULL)
	{
		Destruir (a->left);	
		Destruir (a->right); 	
		free (a);
	}	
}

int main ()
{
	int cmd = 0;
	int dado = 0;
	char entrada [50];
	tree *a;
	FILE *f;
	
	printf ("Forneca o arquivo de uma arvore para ser trabalhada (nao esqueca do .txt):\n");
	scanf ("%s", &entrada);
	printf ("\n");
	f = fopen (entrada, "rt");
	while (cmd != 8)
	{
		printf ("Escolha uma das operacoes abaixo:\n");
		printf ("1: Ler uma arvore de um arquivo fornecido pelo usuario\n");
		printf ("2: Imprimir a arvore\n");
		printf ("3: Verificar se um elemento x existe na arvore\n");
		printf ("4: Imprimir o valor do nivel de um no x\n");
		printf ("5: Imprimir as folhas menores que um valor x\n");
		printf ("6: Inserir um no x na arvore\n");
		printf ("7: Remover um no x da arvore\n");
		printf ("8: Sair\n");
		printf ("Escolha: ");
		scanf ("%d", &cmd);
		switch (cmd)
		{
			case 1:
				a = readTree (f);
				printf ("Arvore lida.\n");
			break;
			case 2:
				printf ("Escolha a ordem de impressao:\n");
				printf ("1: pre-ordem\n");
				printf ("2: em ordem\n");
				printf ("3: pos-ordem\n");
				printf ("4: em largura\n");
				printf ("Escolha: ");
				scanf ("%d", &dado);
				switch (dado)
				{
					case 1: 
						ImprimirPreOrdem (a); 
						printf ("\n");
					break;
					case 2:
						ImprimirEmOrdem (a);
						printf ("\n");
					break;
					case 3:
						ImprimirPosOrdem (a);
						printf ("\n");
					break;
					case 4:
						ImprimirEmLargura (a, 0);
					break;
				}
			break;
			case 3:
				printf ("Digite o numero a ser verificado: ");
				scanf ("%d", &dado);
				if (Existe (a, dado)) printf ("O numero esta na arvore\n");
				else printf ("O numero nao esta na arvore\n");
			break;
			case 4:
				printf ("Digite o no a ter o valor de seu nivel impresso\n");
				scanf ("%d", &dado);
				if (Existe (a, dado)) printf ("O no esta no nivel %d\n", NivelNo (a, 0, dado));
				else printf ("O numero nao esta na arvore\n");
			break;
			case 5:
				printf ("Digite o valor x\n");
				scanf ("%d", &dado);
				ImprimirFolhasMenores (a, dado);
			break;
			case 6:
				printf ("Digite o numero a ser inserido\n");
				scanf ("%d", &dado);
				Inserir (a, dado);
				printf ("Numero inserido.\n");
			break;
			case 7:
				printf ("Digite o numero a ser removido\n");
				scanf ("%d", &dado);
				Remover (&a, dado);
				printf ("Numero removido.\n");
			break;
			case 8:
				Destruir (a);
			break;
		}
		printf ("\n");
	}
	
	fclose (f);	
	return 0;
}
