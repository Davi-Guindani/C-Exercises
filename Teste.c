#include <stdio.h>

int N = 0;
int heap [100];

int indiceFilhoEsq (int x) 
{
	int indice = (2 * x) + 1;
	if (x >= N || indice >= N) return -1;
	else return indice;
}

int indiceFilhoDir (int x)
{
	int indice = (2 * x) + 2;
	if  (x >= N || indice >= N) return -1;
	else return indice;
}

int indicePai (int x) 
{
	int indice = (int) floor ((x - 1) / 2);
	if  (x <= 0 || x >= N) return -1;
	else return indice;
}

void AjustarSubindo (int *heap, int pos)
{
	if (pos != -1)
	{
		int pai = indicePai (pos);
		if (pai != -1)
		{
			if (heap[pos] < heap[pai])
			{
				int aux = heap[pos];
				heap[pos] = heap[pai];
				heap[pai] = aux;
				AjustarSubindo (heap, pai);
			}
		}
	}
}

void Inserir (int *heap, int x) 
{
	heap[N] = x;
	N ++;
	
	AjustarSubindo (heap, N - 1);
}

void AjustarDescendo (int *heap, int pos)
{
	if (pos != -1 && indiceFilhoEsq (pos) != -1)
	{
		int indiceMenorFilho = indiceFilhoEsq (pos);
		if (indiceFilhoDir (pos) != -1 && heap[indiceFilhoDir(pos)] < heap[indiceMenorFilho]) indiceMenorFilho = indiceFilhoDir (pos);
		if (heap[indiceMenorFilho] > heap[pos])
		{
			int aux = heap[pos];
			heap[pos] = heap[indiceMenorFilho];
			heap[indiceMenorFilho] = aux;
			AjustarDescendo (heap, indiceMenorFilho);
		}
	}
}

int Remover (int *heap)
{
	if (N == 0) return -1;
	else
	{
		int retorno = heap[0];
		heap[0] = heap[N - 1];
		N --;
		AjustarDescendo (heap, 0);
		return retorno;
	}
}

int main ()
{
	int cmd = 0;
	int dado = 0;
	int  i;
	
	while (cmd != 4)
	{
		printf ("1: Inserir um elemento x na heap\n");
		printf ("2: Remover um elemento\n");
		printf ("3: Imprimir a heap\n");
		printf ("4: Sair\n");
		printf ("Escolha: ");
		scanf ("%d", &cmd);
		switch (cmd)
		{
			case 1:
				scanf ("%d", &dado);
				Inserir (heap, dado);
			break;
			case 2:
				printf ("Numero removido: %d\n", Remover (heap));
			break;
			case 3:
				for (i = 0; i < N; i ++)
				{
					printf ("%d ", heap[i]);
				}
				printf ("\n");
			break;
			case 4:
				
			break;
		}
	}
	
	return 0;
}
