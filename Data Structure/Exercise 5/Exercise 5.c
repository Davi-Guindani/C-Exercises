#include <stdio.h>

int moedas[5] = {1, 5, 10, 25, 50};

void ComboChar (char *vet, int pos, int n, char *vetAux)
{
	int i;
	if (pos == n)
	{
		int cont = 0;
		for (i = 0; i <= n; i ++) if (vet[i] == 'a') cont ++;
		if (cont >= 2) 
		{
			for (i = 0; i <= n; i ++) printf ("%c ", vet[i]);
			printf ("\n");
		}
		cont = 0;
	}
	else 
	{
		for (i = 0; i <= 2; i ++)
		{
			vet[pos] = vetAux[i];
			ComboChar (vet, pos + 1, n, vetAux);
		}
	}
}

void ComboInt (int *vet, int pos, int n, int *vetAux)
{
	int i;
	if (pos == n)
	{
		int soma = 0;
		for (i = 0; i < n; i ++) soma += vet[i];
		if (soma % 2 == 0)
		{
			for (i = 0; i < n; i ++) printf ("%d ", vet[i]);
			printf ("\n");
		}
		soma = 0;
	}
	else
	{
		for (i = 0; i <= 3; i ++)
		{
			vet[pos] = vetAux[i];
			ComboInt (vet, pos + 1, n, vetAux);
		}
	}
}

void ImprimirCombinacoes (int vet[], int pos, int valor)
{
    int i;
	if (pos == 5)
	{
        int soma = 0;
        for (i = 0; i < 5; i ++) soma += moedas[i]*vet[i];
        if (soma == valor)
		{
            printf("\n");
            for (i = 0; i < 5; i ++) if (vet[i] != 0) printf("%d moedas de %d\n", vet[i], moedas[i]);
        }
    }
    else
	{
        for (i = 0; i <= valor / moedas[pos]; i ++)
		{
            vet[pos] = i;
            ImprimirCombinacoes (vet, pos + 1, valor);
        }
    }
}

int main ()
{
  int cmd = 0;
  int dado = 0;
  int vet[5];
  
  while (cmd != 4)
  {
  		printf ("1: Combinacoes de a, e, i, de tamanho n...\n");
		printf ("2: Combinacoes de 15, 31, 55, 44, de tamanho n...\n");
		printf ("3: Moedas\n");
		printf ("4: Sair\n");
		printf ("Escolha: ");
		scanf ("%d", &cmd);
		printf ("\n");
		
		printf ("Digite o valor de N ou de centavos\n");
		scanf ("%d", &dado);
		printf ("\n");

		char vetcaux[] = {'a','e','i'};
		char vetc[dado];
		int vetiaux[] = {15, 31, 55, 44};
		int veti[dado];
		
		switch (cmd)
		{
			case 1:
				ComboChar (vetc, 0, dado, vetcaux);
				printf ("\n");
			break;
			case 2:
				ComboInt (veti, 0, dado, vetiaux);
				printf ("\n");
			break;
			case 3:
				ImprimirCombinacoes (vet, 0, dado);
			break;
			case 4:
				
			break;
		}
  }
  return 0;
}
