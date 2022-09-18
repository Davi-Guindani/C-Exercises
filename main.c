#include <stdio.h>
#include "fila.h"

int main () 
{
	int cmd = 0, dado;
	Fila a = Inicializar ();
	
	while (cmd != 4)
	{
		printf ("1 Inserir um elemento na fila\n");
		printf ("2 Remover um elemento da fila (imprima o elemento removido)\n");
		printf ("3 Imprimir a fila\n");
		printf ("4 Sair\n");
		printf ("Escolha: ");
		scanf ("%d", &cmd);
		
		switch (cmd)
		{
			case 1:
				printf ("Digite o numero a ser enfileirado: ");
				scanf ("%d", &dado);
				Enfileira (a, dado);
			break;
			case 2:
				Desenfileira (a, &dado);
				printf ("\nNumero desenfileirado: %d", dado);
			break;
			case 3:
				Imprimir (a);
				printf ("\n");
			break;
			case 4:
				a = Destruir (a);
			break;
		}
		printf ("\n");
	}
	
	return 0;
}
