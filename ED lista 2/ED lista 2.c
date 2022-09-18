#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct arvore
{
	int info;
	struct arvore *esq, *dir;
} arvore;

void ImprimirPreOrdem (arvore *a)
{
	if (a != NULL)
	{
		printf ("%d ", a->info);
		ImprimirPreOrdem (a->esq);
		ImprimirPreOrdem (a->dir);
	}
}

void ImprimirEmOrdem (arvore *a)
{
	if (a != NULL)
	{
		ImprimirEmOrdem (a->esq);
		printf ("%d ", a->info);
		ImprimirEmOrdem (a->dir);
	}
}

void ImprimirPosOrdem (arvore *a)
{
	if (a != NULL)
	{
		ImprimirPosOrdem (a->esq);
		ImprimirPosOrdem (a->dir);
		printf ("%d ", a->info);
	}
}

arvore *LerArvore (FILE *arq)
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
		arvore *a;
		a = (arvore*) malloc (sizeof (arvore));
		a->info = n;
		a->esq = LerArvore (arq);
		a->dir = LerArvore (arq);
		fscanf (arq, "%c", &c); // lendo o ')'
		return a;
	}
}

int Altura (arvore *a)
{
	if (a == NULL) return 0;
	else
	{
		int hd, he;
		he = Altura (a->esq);
		hd = Altura (a->dir);
		if (he > hd) return he + 1;
		else return hd + 1;
	}
}

int ContaNivel (arvore *a, int cont, int nivel)
{
	if (a == NULL) return 0;
	else 
	{
		if (cont == nivel) return 1;
		else return ContaNivel (a->esq, cont + 1, nivel) + ContaNivel (a->dir, cont + 1, nivel);
	}
}

void ImprimirNivel (arvore *a, int cont, int nivel)
{
	if (a != NULL)
	{
		if (cont == nivel) printf ("%d ", a->info);
		else 
		{
			ImprimirNivel (a->esq, cont + 1, nivel);
			ImprimirNivel (a->dir, cont + 1, nivel);
		}
	}
}

void ImprimirEmLargura (arvore *a, int n)
{
	if (a != NULL && n < Altura (a))
	{
		ImprimirNivel (a, 0, n);
		printf ("\n");
		ImprimirEmLargura (a, ++n);
	} 
}

int Existe (arvore * a, int n)
{
	if (a != NULL) 
	{
		if (a->info != n) return (Existe (a->esq, n) || Existe (a->dir, n));
		else return 1;
	}
	else return 0;
}

int NivelNo (arvore *a, int cont, int n)
{
	if (a != NULL)
	{
		if (a->info != n) return (NivelNo (a->esq, cont + 1, n) + NivelNo (a->dir, cont + 1, n));
		else return cont;
	}
	else return 0;
}

int ContArvore (arvore *a) 
{
	if (a != NULL) return 1 + ContArvore (a->esq) + ContArvore (a->dir);
	else return 0;
}

void ImprimirFolhas (arvore *a, int cont, int h)
{
	if (a != NULL)
	{
		if (cont == h - 1) printf ("%d ", a->info);
		else 
		{
			ImprimirFolhas (a->esq, cont + 1, h);
			ImprimirFolhas (a->dir, cont + 1, h);
		}
	}
}

int Balanceada (arvore *a)
{
	if (a != NULL)
	{
		int hd, he;
		he = Altura (a->esq);
		hd = Altura (a->dir);
		if (abs (he - hd) <= 1) return (Balanceada (a->esq) && Balanceada (a->dir));
		else return 0;
	}
	else return 1;
}

void DestruirNo (arvore *a)
{
	if (a != NULL)
	{
		DestruirNo (a->esq);	
		DestruirNo (a->dir);
		free (a);
	}
}

void DestruirArvore (arvore *a)
{
	if (a != NULL)
	{
		DestruirNo (a);
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
	while (cmd != 9)
	{
		printf ("Escolha uma das operacoes abaixo:\n");
		printf ("1: Ler uma arvore de um arquivo fornecido pelo usuario\n");
		printf ("2: Imprimir a arvore\n");
		printf ("3: Verificar se um elemento x existe na arvore\n");
		printf ("4: Contar o numero de elementos da arvore\n");
		printf ("5: Imprimir os nos folhas da arvore\n");
		printf ("6: Verificar se uma arvore esta balanceada\n");
		printf ("7: Verificar se uma arvore e cheia\n");
		printf ("8: Imprimir o valor do nivel de um no x\n");
		printf ("9: Sair\n");
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
				printf ("A arvore tem %d elementos\n", ContArvore (a));
			break;
			case 5:
				ImprimirFolhas (a, 0, Altura (a));
			break;
			case 6:
				if (Balanceada (a)) printf ("A arvore esta balanceada\n");
				else printf ("A arvore nao esta balanceada\n");
			break;
			case 7:
				if (ContArvore (a) == (pow (2, Altura (a)) - 1)) printf ("A arvore e cheia\n");
				else printf ("A arvore nao e cheia\n");
			break;
			case 8:
				printf ("Digite o no a ter o valor de seu nivel impresso\n");
				scanf ("%d", &dado);
				if (Existe (a, dado)) printf ("O no esta no nivel %d\n", NivelNo (a, 0, dado));
				else printf ("O numero nao esta na arvore\n");
			break;
			case 9:
				DestruirArvore (a);
			break;
		}
		printf ("\n");
	}
	fclose (f);
	return 0;
}
