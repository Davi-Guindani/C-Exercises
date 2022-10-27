#include <stdio.h>

int coins[5] = {1, 5, 10, 25, 50};

void charCombo (char *vet, int pos, int n, char *vetAux)
{
	int i;
	if (pos == n)
	{
		int count = 0;
		for (i = 0; i <= n; i ++) if (vet[i] == 'a') count ++;
		if (count >= 2) 
		{
			for (i = 0; i <= n; i ++) printf ("%c ", vet[i]);
			printf ("\n");
		}
		count = 0;
	}
	else 
	{
		for (i = 0; i <= 2; i ++)
		{
			vet[pos] = vetAux[i];
			charCombo (vet, pos + 1, n, vetAux);
		}
	}
}

void intCombo (int *vet, int pos, int n, int *vetAux)
{
	int i;
	if (pos == n)
	{
		int sum = 0;
		for (i = 0; i < n; i ++) sum += vet[i];
		if (sum % 2 == 0)
		{
			for (i = 0; i < n; i ++) printf ("%d ", vet[i]);
			printf ("\n");
		}
		sum = 0;
	}
	else
	{
		for (i = 0; i <= 3; i ++)
		{
			vet[pos] = vetAux[i];
			intCombo (vet, pos + 1, n, vetAux);
		}
	}
}

void printCombinations (int vet[], int pos, int value)
{
    int i;
	if (pos == 5)
	{
        int sum = 0;
        for (i = 0; i < 5; i ++) sum += coins[i]*vet[i];
        if (sum == value)
		{
            printf("\n");
            for (i = 0; i < 5; i ++) if (vet[i] != 0) printf("%d moedas de %d\n", vet[i], coins[i]);
        }
    }
    else
	{
        for (i = 0; i <= value / coins[pos]; i ++)
		{
            vet[pos] = i;
            printCombinations (vet, pos + 1, value);
        }
    }
}

int main ()
{
  int cmd = 0;
  int data = 0;
  int vet[5];
  
  while (cmd != 4)
  {
  		printf ("1: Combinations of a, e, i, of size n...\n");
		printf ("2: Combinations of 15, 31, 55, 44, size n...\n");
		printf ("3: Coins\n");
		printf ("4: Halt\n");
		printf ("Choice: ");
		scanf ("%d", &cmd);
		printf ("\n");
		
		printf ("Enter the value of N or cents\n");
		scanf ("%d", &data);
		printf ("\n");

		char vetcaux[] = {'a','e','i'};
		char vetc[data];
		int vetiaux[] = {15, 31, 55, 44};
		int veti[data];
		
		switch (cmd)
		{
			case 1:
				ComboChar (vetc, 0, data, vetcaux);
				printf ("\n");
			break;
			case 2:
				ComboInt (veti, 0, data, vetiaux);
				printf ("\n");
			break;
			case 3:
				ImprimirCombinacoes (vet, 0, data);
			break;
			case 4:
				
			break;
		}
  }
  return 0;
}
