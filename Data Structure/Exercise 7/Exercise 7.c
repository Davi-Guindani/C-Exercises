#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
	int destiny;
	int cost;
	struct list *next;
} list;

void init (list **g, int n)
{
	int i;
	for (i = 1; i <= n; i++)
		g[i] = NULL;
}

list *insertList (list *g, int d, int c)
{
	list *node = (list*) malloc(sizeof(list));
	node->destiny = d;
	node->cost = c;
	node->next = g;
	return node;
}

void insertEdge (list **g, int o, int d, int c)
{
	g[o] = insertList (g[o], d, c);
}

void removeEdge (list **g, int o, int d)
{
	list *ant = NULL;
	list *i;
	for (i = g[o]; i != NULL; i = i->next)
	{
		if (i->destiny == d)
		{
			if (ant == NULL)
			{
				g[o] = g[o]->next;
				free (i);
				break;
			}
			else
			{
				ant->next = i->next;
				free (i);
				break;
			}
		}
		ant = i;
	}
}

int exitDegree (list **g, int edge)
{
	int count = 0;
	list *i;
	for (i = g[edge]; i != NULL; i = i->next)
		count++;
	return count;
}

int entryDegree (list **g, int n, int edge)
{
	int count = 0;
	int i;
	for (i = 1; i <= n; i++)
	{
		list *j;
		for (j = g[i]; j != NULL; j = j->next)
		{
			if (j->destiny == edge)
				count++;
		}
	}
	return count;
}

int fullGraph (list **g, int n)
{
	int count = 0;
	int i;
	for (i = 1; i <= n; i++)
	{
		list *j;
		for (j = g[i]; j != NULL; j = j->next)
			count++;
	}
	return (count == (n * (n - 1)));
}

void printGraph (list **g, int n)
{
	int i;
	for (i = 1; i <= n; i++)
	{
		printf ("Graph %d: ", i);
		list *j;
		for (j = g[i]; j != NULL; j = j->next)
			printf("(%d %d) ", j->destiny, j->cost);
	}
	printf("\n");
}

int exists (int *vet, int value, int n)
{
	int i;
	for (i = 0; i < n; i++)
		return vet[i] == value;
	return 0;
}
int calculateCost (list **g, int o, int d)
{
	list *t;
	for (t = g[o]; t != NULL; t = t->next)
		if (t->destiny == d)
			return t->cost;
}
void paths (list **g, int b, int *vet, int pos, int *lowerCost, int *vetLowerCost, int *shortestWay, int choice, int *prevPos)
{
	if (vet[pos - 1] == b)
	{
		if (choice == 1)
		{
			printf ("\n");
			int i;
			for (i = 0; i < pos; i++)
				printf ("%d", vet[i]);
		}
		else
		{
			if (choice == 2)
			{
				if (pos < *prevPos)
				{
					int i;
					for(i = 0; i < pos; i++)
						shortestWay[i] = vet[i];
					*prevPos = pos;
				}
			}
			else
			{
				int aux = 0, sum = 0;
				int i;
				for (i = 1; i < pos; i++)
				{
					sum += calculateCost (g, vet[aux], vet[i]);
					aux ++;
				}
				if (sum < *lowerCost)
				{
					*lowerCost = sum;
					*prevPos = pos;
					int i;
					for (i = 0; i < pos; i++)
						vetLowerCost[i] = vet[i];
				}
			}
		}
	}
	else
	{
		list *p = g[vet[pos - 1]];
		while (p != NULL)
		{
			if (!exists(vet, p->destiny, pos))
			{
				vet[pos] = p->destiny;
				paths (g, b, vet, pos + 1, lowerCost, vetLowerCost, shortestWay, choice, prevPos);
			}
		}
		p = p->next;
	}
}
int main()
{
	int menu = 0;
	int origin, destiny, cost, edges, gs, ge, aux, lowerCost = 1000000, prevPos = 6;
	printf ("What is the number of edges?\n");
	scanf ("%d", &edges);
	list **g = (list**) malloc ((edges + 1) * sizeof (list*));
	int *vet = (int*) malloc (edges * sizeof (list));
	int *shortestWay = (int*) malloc (edges * sizeof (list));
	int *vetLowerCost = (int*) malloc (edges * sizeof (list));
	printf ("--------------------------MENU--------------------------\n1- Insert an edge into the graph\n2- Remove an edge from the graph\n3- Print graph\n4- Print the in and out degrees of a vertex\n5- Check if a graph is complete\n6- Print all paths between a source and a destination\n7- Print the shortest path (with the least number of edges)\n8- Print the least cost path(smallest sum of edge costs)\n9- Halt \n");
	scanf ("%d", &menu);
	init (g, edges);
	while (menu >= 0 && menu < 9)
	{
		int i;
		switch (menu)
		{
			case 1: printf ("What is the origin?\n");
					scanf ("%d", &origin);
					printf ("What is the destination?\n");
					scanf ("%d", &destiny);
					printf ("What is the cost?\n");
					scanf ("%d", &cost);
					insertEdge (g, origin, destiny, cost);
					break;
			case 2: printf ("What is the origin?\n");
					scanf ("%d", &origin);
					printf ("What is the destination?\n");
					scanf ("%d", &destiny);
					removeEdge (g, origin, destiny);
					break;
			case 3:	printGraph (g, edges);
					break;
			case 4:	printf ("What is the vertex?\n");
					scanf ("%d", &origin);
					gs = exitDegree (g, origin);
					ge = entryDegree (g, edges, origin);
					printf ("The entry degree is %d and the output is %d\n", ge, gs);
					break;
			case 5: aux = fullGraph (g, edges);
					if (aux == 1)
						printf ("The graph is full!\n");
					else
						printf ("The graph is not full!\n");		
			case 6: printf ("what is the origin?\n");
					scanf ("%d", &origin);
					printf ("What is the destination?\n");
					scanf ("%d", &destiny);
					vet[0] = origin;
					paths (g, destiny, vet, 1, &lowerCost, vetLowerCost, shortestWay, 1, &prevPos);
					break;
			case 7: printf ("What is the origin?\n");
					scanf ("%d", &origin);
					printf ("What is the destination?\n");
					scanf ("%d", &destiny);
					vet[0] = origin;
					paths (g, destiny, vet, 1, &lowerCost, vetLowerCost, shortestWay, 2, &prevPos);
					for (i = 0; i < prevPos; i++)
						printf ("%d ", shortestWay[i]);
					break;
			case 8: printf ("What is the origin?\n");
					scanf ("%d", &origin);
					printf ("What is the destination?\n");
					scanf ("%d", &destiny);
					vet[0] = origin;
					paths (g, destiny, vet, 1, &lowerCost, vetLowerCost, shortestWay, 3, &prevPos);
					printf ("The path with the least cost is the: ");
					for (i = 0; i < prevPos; i++)
						printf ("%d ", vetLowerCost[i]);
					printf ("with a cost of %d\n", lowerCost);
					break;
		}
		printf ("--------------------------MENU--------------------------\n1- Insert an edge into the graph\n2- Remove an edge from the graph\n3- Print graph\n4- Print the in and out degrees of a vertex\n5- Check if a graph is complete\n6- Print all paths between a source and a destination\n7- Print the shortest path (with the least number of edges)\n8- Print the least cost path(smallest sum of edge costs)\n9- Halt \n");
		scanf ("%d", &menu);
	}
	
	return 0;
}
