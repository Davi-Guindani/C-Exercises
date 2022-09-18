#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

#define N 100

struct fila 
{
	int vet[N];
	int fim;
};

Fila Inicializar ()
{
	Fila f = (Fila) malloc (sizeof (struct fila));
	int i;
	for (i = 0; i < N; i ++) f->vet[i] = 0;
	f->fim = 0;
}

Fila Destruir (Fila f)
{
	free (f);
	return NULL;
}

int cheia (Fila f)
{
	if (f->fim == N) return 1;
	return 0;
}

int Enfileira (Fila f, int x)
{
	if (cheia (f)) return 0;
	f->vet[f->fim] = x;
	f->fim ++;
	return 1;
}

int vazia (Fila f)
{
	if (f->fim == 0) return 1;
	return 0;
}

int Desenfileira (Fila f, int *x)
{
	int i;
	if (vazia (f)) return 0;
	*x = f->vet[0];
	for (i = 0; i < f->fim; i ++) f->vet[i] = f->vet[i + 1];
	f->fim --;
	return 1;
}

void Imprimir (Fila f)
{
	int i;
	printf ("Elementos: ");
	for (i = 0; i < f->fim; i ++) printf ("%d ", f->vet[i]);
}
