#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef struct aluno
{
	int mat;
	char nome[100];
	char curso[50];
	int disponibilidade;
} aluno;

int hash (int key) 
{
	return (key %= 1000) % N;	
}

void inicializar (char *nomeArq)
{
	FILE *arq = fopen (nomeArq, "wb");
	aluno a;
	int i;
	a.disponibilidade = 1;
	for (i = 0; i< N; i ++) fwrite (&a, sizeof (aluno), 1, arq);
	fclose (arq);
}

int AcharPosicao (char *nomeArq, int x)
{
	int pos = hash (x);
	aluno a;
	FILE *arq = fopen (nomeArq, "rb");
	fseek (arq, pos * sizeof (aluno), SEEK_SET);
	fread (&a, sizeof (aluno), 1, arq);
	while (a.disponibilidade == 0)
	{
		pos = (pos + 1) % N;
		fseek (arq, pos * sizeof (aluno), SEEK_SET);
		fread (&a, sizeof (aluno), 1, arq);
	}
	fclose (arq);
	return pos;
}

void inserir (char *nomeArq, int x, char *n, char *c)
{
	int pos = AcharPosicao (nomeArq, x);
	FILE *arq = fopen (nomeArq, "r+b");
	
	aluno a = {x, n, c, 0};
	
	fseek (arq, pos * sizeof (aluno), SEEK_SET);
	fwrite (&a, sizeof (aluno), 1, arq);
	
	fclose (arq);
	
	printf ("\nInserido\n\n");
}

void imprimirAluno (char *nomeArq, int x)
{
	aluno a;
	int i;
	FILE *arq = fopen (nomeArq, "rb");
	
	for (i = 0; i < N; i ++)
	{
		fseek (arq, i * sizeof (aluno), SEEK_SET);
		fread (&a, sizeof (aluno), 1, arq);
		if (a.mat == x) printf ("%d\n%s\n%s\n", a.mat, a.nome, a.curso);
	}
	
	fclose (arq);
}

void remover (char *nomeArq, int x)
{
	FILE *arq = fopen (nomeArq, "r+b");
	aluno a;
	aluno b;
	int i;
	a.disponibilidade = 1;
	for (i = 0; i < N; i ++)
	{
		fseek (arq, i * sizeof (aluno), SEEK_SET);
		fread (&b, sizeof (aluno), 1, arq);
		if (b.mat == x) fwrite (&a, sizeof (aluno), 1, arq);
	} 
	
	fclose (arq);
}

void imprimirHash (char *nomeArq)
{
	FILE *arq = fopen (nomeArq, "rb");
	aluno a;
	int i;
	for (i = 0; i < N; i ++)
	{
		fseek (arq, i * sizeof (aluno), SEEK_SET);
		fread (&a, sizeof (aluno), 1, arq);	
		printf ("%d\n", a.mat % 1000);
	}
	
	fclose (arq);
}

int main ()
{
	char str[] = "arquivo.bin";
	inicializar (str);
	
	int cmd = 0, m;
	char *n, *c;
	
	while (cmd != 4)
	{
		printf ("1 - Inserir\n");
		printf ("2 - Imprimir as informacoes de um determinado aluno\n");
		printf ("3 - Imprimir a tabela hash\n");
		printf ("4 - Sair\n");
		printf ("Escolha: ");
		scanf ("%d", &cmd);
		switch (cmd)
		{
			case 1:
				printf ("Digite os dados do aluno a ser inserido:\n");
				printf ("Matricula: ");
				scanf ("%d", &m);
				printf ("Nome: ");
				scanf ("%s", &n);
				printf ("Curso: ");
				scanf ("%s", &c);
				inserir (str, m, n, c);
			break;
			case 2:
				printf ("Digite a matricula do aluno a ter os dados impressos: ");
				scanf ("%d", &m);
				imprimirAluno (str, m);
			break;
			case 3:
				imprimirHash (str);
			break;
			case 4:
					
			break;
		}
	}
	
	
	/*FILE *arq = fopen (str, "rb");
	fseek (arq, 1 * sizeof (aluno), SEEK_SET);
	aluno a;
	fread (&a, sizeof (aluno), 1, arq);
	printf ("%d\n%s\n%s\n%d\n", a.mat, a.nome, a.curso, a.disponibilidade); */
	
	return 0;
}
