#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct arvore
{
	int info;
	struct arvore *esq, *dir;
} arvore;

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
	if (a == NULL) return 0;
	else if (n == a->info) return 1;
	else if (n < a->info) return Existe (a->esq, n);
	else return Existe (a->dir, n);
}

int NivelNo (arvore *a, int cont, int n)
{
	if (a != NULL)
	{
		if (a->info != n) 
		{
			if (n < a->info) return (NivelNo (a->esq, cont + 1, n));
			else return NivelNo (a->dir, cont + 1, n);
		}
		else return cont;
	}
	else return 0;
}

void ImprimirMaioresIguais (arvore *a, int n)
{
	if (a!= NULL)
	{
		if (a->info >= n)
		{
			printf ("%d ", a->info);
			ImprimirMaioresIguais (a->esq, n);
			ImprimirMaioresIguais (a->dir, n);
		}	
		else ImprimirMaioresIguais (a->dir, n);
	}
}

void ImprimirFolhasMenores (arvore *a, int n)
{
	if (a != NULL)
	{
		if ((a->esq == NULL) && (a->dir == NULL) && (a->info < n)) printf ("%d ", a->info);
		else
		{
			if ((a->info + 2) <= n)
			{
				ImprimirFolhasMenores (a->esq, n);
				ImprimirFolhasMenores (a->dir, n);
			}
			else ImprimirFolhasMenores (a->esq, n);
		}
	}
}

arvore *RotacaoEsqSimples(arvore *p)
{
	arvore *b = p->dir;
	p->dir = b->esq;
	b->esq = p;
	return b;
}

arvore *RotacaoDirSimples(arvore *p)
{
	arvore *b = p->esq;
	p->esq = b->dir;
	b->dir = p;
	return b;
}

arvore *RotacaoEsqDupla(arvore *p)
{
	p->dir = RotacaoDirSimples(p->dir);
	p = RotacaoEsqSimples(p);
	return p;
}

arvore *RotacaoDirDupla(arvore *p)
{
	p->esq = RotacaoEsqSimples(p->esq);
	p = RotacaoDirSimples(p);
	return p;
}

arvore *RotacaoEsq(arvore *p)
{
	int he = Altura(p->esq);
	int hd = Altura(p->dir);
	if (fabs(hd - he) > 1)
	{
		arvore *b = p->dir;
		he = Altura(b->esq);
		hd = Altura(b->dir);
		if (he > hd)
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
			//Verificar se é folha
			if(a->esq == NULL && a->dir == NULL)
			{
				free(a);
				return NULL;
			}
			//Verificar se um dos filhos é nulo
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
