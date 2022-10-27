#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
	int destiny;
	int cost;
	struct list *next;
}	list;

void init (list **g, int n)
{
	int i;
	for (i = 0; i <= n; i ++) g[i] = NULL;
}

list *insertList (list *l, int d, int c)
{
	list *node = (list *) malloc (sizeof (list));
	node->destiny = d;
	node->cost = c;
	node->next = l;
	return node;
}

void insertEdge (list **g, int origin, int destiny, int cost) 
{
	g[origin] = insertList (g[origin], destiny, cost);
}

void printList (list *l)
{
	if (l != NULL)
	{
		printf ("-(%d, %d)", l->destiny, l->cost);
		printList (l->next);
	}
}

void printGraph (list **g, int n)
{
	int i;
	printf ("Graph: ");
	for (i = 0; i <= n; i ++)
	{
		printf ("\n\t%d", i);
		printList (g[i]);
	}
}

list *removeList (list *l, int d)
{
	list *aux = l;
	if (l->destiny == d)
	{
		l = l->next;
		free (aux);
	}
	else l->next = removeList (l->next, d);
	return l;
}

void removeEdge (list **g, int origin, int destiny)
{
	g[origin] = removeList (g[origin], destiny);
}

int countS (list *l)
{
    if (l == NULL) return 0;
    return 1 + countS (l->next);
}

int GS (list **g, int origin)
{
    return countS (g[origin]);
}

int ContE (list *l, int destiny)
{
    if (l == NULL) return 0;
    if (l->destiny == destiny) return 1 + ContE (l->next, destiny);
    return ContE (l->next, destiny);
}

int GE (list **g, int origin, int n)
{
    int count = 0, i;
    for (i = 1; i <= n; i++) count += ContE (g[i], origin);
    return count;
}

int countEdges (list *l)
{
    if (l == NULL) return 0;
    return 1 + countEdges (l->next);
}

int fullGraph (list **g, int n)
{
    int edges = 0, i;
    for (i = 1; i <= n; i ++) edges += countEdges (g[i]);
    if (edges != (n* (n - 1))) return 0;
    return 1;
}

int main () 
{
	int cmd = 0, n, gs, ge, test, data, data1, data2;
  
  	printf("Type the graph's size: ");
	scanf("%d",&n);
  
  	list *g[n];
  	init (g, n);
  
 	 while (cmd != 6)
 	 {
  		printf ("1: Insert an edge in the graph\n");
		printf ("2: Remove an graph's edge\n");
		printf ("3: Print graph\n");
		printf ("4: Print the in and out degrees of a vertex\n");
		printf ("5: Check if a graph is full\n");
		printf ("6: Halt\n");
		printf ("Choice: ");
		scanf ("%d", &cmd);
		printf ("\n");
	
		switch (cmd)
		{
			case 1:
				printf ("Enter the origin of this edge, the destination and the cost\n");
				scanf ("%d %d %d", &data, &data1, &data2);
				printf ("\n");
				insertEdge (g, data, data1, data2);
			break;
			case 2:
				printf("Choose origin and destination:\n");
				scanf ("%d %d", &data, &data1);
				removeEdge(g, data, data1);
			break;
			case 3:
				printGraph(g, n);
				printf ("\n\n");
			break;
			case 4:
				printf ("Enter the vertex\n");
				scanf ("%d", &data);
				printf("vertex's Gs %d and: %d entrys\n", data, GE (g, data, n));
				printf("vertex's in %d and: %d out", data, GS (g, data));
				printf ("\n");
			break;
			case 5:
                if (fullGraph (g, n)) printf ("The graph is full\n");
                else printf("The graph is not full\n");
                printf ("\n");
			break;
			case 6:
				
			break;
		}
	}
	
	return 0;
}
