#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree
{
	int info;
	struct tree *left, *right;
} tree;

tree *readTree (FILE *f)
{
	int n;
	char c;
	
	fscanf (f, "%c", &c); // reading the '('
	fscanf (f, "%d", &n);
	if (n == -1) // null tree
	{	
		fscanf (f, "%c", &c); // reading the ')'
		return NULL;
	}
	else // not null
	{
		tree *t;
		t = (tree*) malloc (sizeof (tree));
		t->info = n;
		t->left = readTree (f);
		t->right = readTree (f);
		fscanf (f, "%c", &c); // reading the ')'
		return t;
	}
}

void printPreOrder (tree *t)
{
	if (t != NULL)
	{
		printf ("%d ", t->info);
		printPreOrder (t->left);
		printPreOrder (t->right);
	}
}

void printInOrder (tree *t)
{
	if (t != NULL)
	{
		printInOrder (t->left);
		printf ("%d ", t->info);
		printInOrder (t->right);
	}
}

void printPostOrder (tree *t)
{
	if (t != NULL)
	{
		printPostOrder (t->left);
		printPostOrder (t->right);
		printf ("%d ", t->info);
	}
}

void printLevel (tree *t, int count, int level)
{
	if (t != NULL)
	{
		if (count == level) printf ("%d ", t->info);
		else 
		{
			printLevel (t->left, count + 1, level);
			printLevel (t->right, count + 1, level);
		}
	}
}

int height (tree *t)
{
	if (t == NULL) return 0;
	else
	{
		int hr, hl;
		hl = height (t->left);
		hr = height (t->right);
		if (hl > hr) return hl + 1;
		else return hr + 1;
	}
}

void printInWidth (tree *t, int n)
{
	if (t != NULL && n < height (t))
	{
		printLevel (t, 0, n);
		printf ("\n");
		printInWidth (t, ++n);
	} 
}

int exists (tree * t, int n)
{
	if (t != NULL) 
	{
		if (t->info != n) return (exists (t->left, n) || exists (t->right, n));
		else return 1;
	}
	else return 0;
}

int nodeLevel (tree *t, int count, int n)
{
	if (t != NULL)
	{
		if (t->info != n) return (nodeLevel (t->left, count + 1, n) + nodeLevel (t->right, count + 1, n));
		else return count;
	}
	else return 0;
}


void printGreaterOrEqual (tree *t, int n)
{
	if (t!= NULL)
	{
		if (t->info >= n)
		{
			printf ("%d ", t->info);
			printGreaterOrEqual (t->left, n);
			printGreaterOrEqual (t->right, n);
		}	
		else printGreaterOrEqual (t->right, n);
	}
}

void printSmallerLeafs (tree *t, int n)
{
	if (t != NULL)
	{
		if ((t->left == NULL) && (t->right == NULL) && (t->info < n)) printf ("%d ", t->info);
		else
		{
			if ((t->info + 2) <= n)
			{
				printSmallerLeafs (t->left, n);
				printSmallerLeafs (t->right, n);
			}
			else printSmallerLeafs (t->left, n);
		}
	}
}

tree *simpleLeftRotation(tree *a)
{
	tree *t = a->right;
	a->right = t->left;
	t->left = a;
	return t;
}

tree *simpleRightRotation(tree *a)
{
	tree *t = a->left;
	a->left = t->right;
	t->right = a;
	return t;
}

tree *doubleLeftRotation(tree *t)
{
	t->right = RotacaoDirSimples(t->right);
	t = RotacaoEsqSimples(t);
	return t;
}

tree *doubleRightRotation(tree *t)
{
	t->left = RotacaoEsqSimples(t->left);
	t = RotacaoDirSimples(t);
	return t;
}

tree *leftRotation(tree *p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	if (fabs(hr - hl) > 1)
	{
		tree *b = p->right;
		hl = Altura(b->left);
		hr = Altura(b->right);
		if (hl > hr)
		p = RotacaoEsqDupla(p);
		else
		p = RotacaoEsqSimples(p);
	}
	return p;
}

arvore *RotacaoDir(arvore *p)
{
	int he = Altura(p->esq);
	int hd = Altura(p->dir);
	if (fabs(hd - he) > 1)
	{
		arvore *b = p->esq;
		he = Altura(b->esq);
		hd = Altura(b->dir);
		if (hd > he)
		p = RotacaoDirDupla(p);
		else
		p = RotacaoDirSimples(p);
	}
	return p;
}

arvore *Inserir(arvore *a, int x)
{
	if(a == NULL) 
	{
		a = (arvore*)malloc(sizeof(arvore));
		a->info = x;
		a->esq = NULL;
		a->dir = NULL;
	}
	else
	{
		if (x <= a->info)
		{
			a->esq = Inserir(a->esq,x);
			a = RotacaoDir(a);
		}
		else
		{
			a->dir = Inserir(a->dir,x);
			a = RotacaoEsq(a);
		}
	}
	return a;
}

arvore *Remover(arvore *a, int x)
{
	if(a != NULL)
	{
		if(a->info == x)
		{
			//Verificar se � folha
			if(a->esq == NULL && a->dir == NULL)
			{
				free(a);
				return NULL;
			}
			//Verificar se um dos filhos � nulo
			else if (a->esq == NULL || a->dir == NULL)
			{
				arvore *aux;
				
				if(a->esq == NULL)
				aux = a->dir;
				else
				aux = a->esq;
				free(a);
				return aux;
			}
			//Nenhum filho nulo
			else
			{
				arvore *maiorEsq = a->esq;
				while (maiorEsq->dir != NULL)
				maiorEsq = maiorEsq->dir;
				a->info = maiorEsq->info;
				a->esq = Remover(a->esq,a->info);
				a = RotacaoEsq(a);
			}
		}
		else if (x < a->info)
		{
			a->esq = Remover(a->esq, x);
			a = RotacaoEsq(a);
		}
		else
		{
			a->dir = Remover(a->dir, x);
			a = RotacaoDir(a);
		}
	}
	return a;
}

void Destruir (arvore *a)
{
	if (a != NULL)
	{
		Destruir (a->esq);	
		Destruir (a->dir); 	
		free (a);
	}	
}

int main ()
{
	int cmd = 0;
	int dado = 0;
	char entrada [50];
	arvore *a;
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
				a = LerArvore (f);
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
				a = Inserir (a, dado);
				printf ("Numero inserido.\n");
			break;
			case 7:
				printf ("Digite o numero a ser removido\n");
				scanf ("%d", &dado);
				a = Remover (&a, dado);
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
