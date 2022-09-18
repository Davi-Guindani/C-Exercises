#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct professor 
{
	int mat;
	char nome[50];
	int salario;
} Professor;

typedef struct aluno
{
	int mat;
	char nome[50];
	char curso[50];
	int ano;
} Aluno;

typedef struct pessoa
{
	int tipo;
	void *item;
} Pessoa;

void Inserir (Pessoa *vet, int pos, void *info, int tipo)
{
	
	vet[pos].tipo = tipo;
	vet[pos].item = info;
}

void Inicializar (Pessoa *vet)
{
	int i;
	for (i = 0; i < MAX; i ++)
	{
		vet[i].tipo = 0;
		vet[i].item = NULL;
	}
}

void Remover (Pessoa *vet, int mat)
{
	int i;
	for (i = 0; i < MAX; i ++)
	{
		if (vet[i].tipo == 1) 
		{
			Professor *p = (Professor *) vet[i].item;
			if (p->mat == mat)
			{
				vet[i].tipo = 0;
				vet[i].item = NULL;
			}
		}
		else if (vet[i].tipo == 2) 
		{
			Aluno *a = (Aluno *) vet[i].item;
			if (a->mat == mat)
			{
				vet[i].tipo = 0;
				vet[i].item = NULL;
			}
		}
	}
}

void ImprimirPelaMat (Pessoa *vet, int mat)
{
	int i;
	for (i = 0; i < MAX; i ++)
	{
		if (vet[i].tipo == 1) 
		{
			Professor *p = (Professor *) vet[i].item;
			if (p->mat == mat) printf ("%d, %s, %d\n", p->mat, p->nome, p->salario);
		}
		else if (vet[i].tipo == 2) 
		{
			Aluno *a = (Aluno *) vet[i].item;
			if (a->mat == mat) printf ("%d %s %s %d\n", a->mat, a->nome, a->curso, a->ano);
		}
	}
}

int ContaCurso (Pessoa *vet, char *curso)
{
	int i, cont = 0;
	for (i = 0; i < MAX; i ++)
	{
		if (vet[i].tipo == 2) 
		{
			Aluno *a = (Aluno *) vet[i].item;
			if (strcmp (a->curso, curso) == 0) cont ++;
		}
	}
	return cont;
}

void ImprimirProfsMaiorSalario (Pessoa *vet)
{
	int i, maior = 0;
	for (i = 0; i < MAX; i ++)
	{
		if (vet[i].tipo == 1) 
		{
			Professor *p = (Professor *) vet[i].item;
			if (p->salario > maior) maior = p->salario;
		}
	}
	for (i = 0; i < MAX; i ++)
	{
		if (vet[i].tipo == 1)
		{
			Professor *p = (Professor *) vet[i].item;
			if (p->salario == maior) printf ("%s\n", p->nome);
		}
	}
	printf ("\n");
}

int main ()
{
	int cmd = 0, pos = 0, tipo = 0, mat, i;
	char c[50];
	Pessoa vet [MAX];
	Professor *p;
	Aluno *a;
	
	p = (Professor*) malloc (sizeof (Professor));
	a = (Aluno*) malloc (sizeof (Aluno));
	
	Inicializar (vet);
	
	while (cmd != 6)
	{
		printf ("1 - Inserir uma pessoa na lista\n");
		printf ("2 - Remover uma pessoa pela matricula\n");
		printf ("3 - Buscar uma pessoa pela matricula\n");
		printf ("4 - Contar o numero de alunos em um determinado curso\n");
		printf ("5 - Imprimir os professores de maior salario\n");
		printf ("6 - Sair\n");
		printf ("Escolha: ");
		scanf ("%d", &cmd);
		switch (cmd)
		{
			case 1:
				printf ("Digite 1 para professor ou 2 para aluno\n");
				scanf ("%d", &tipo);
				switch (tipo)
				{
					case 1:
						printf ("Digite a matricula, nome e salario\n");
						scanf ("%d %s %d", &p->mat, p->nome, &p->salario);
						Inserir (vet, pos, p, tipo);
					break;
					case 2:
						printf ("Digite a matricula, nome, curso e ano\n");
						scanf ("%d %s %s %d", &a->mat, a->nome, a->curso, &a->ano);
						Inserir (vet, pos, a, tipo);	
					break;
				}
				pos ++;
			break;
			case 2:
				printf ("Digite a matricula da pessoa a ser removida\n");
				scanf ("%d", &mat);
				Remover (vet, mat);
			break;
			case 3:
				printf ("Digite a matricula\n");
				scanf ("%d", &mat);
				ImprimirPelaMat (vet, mat);
			break;
			case 4:
				printf ("Digite o nome do curso\n");
				scanf ("%s", c);
				printf ("%d\n", ContaCurso (vet, c)); 
			break;
			case 5:
				ImprimirProfsMaiorSalario (vet);
			break;
			case 6:
				
			break;
		}
		printf ("\n");
	}
	
	return 0;
}
