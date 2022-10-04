#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree
{
	int info;
	struct tree *left, *right;
} tree;

tree *readTree (FILE *f)
{
	int n;
	char c;
	
	fscanf (f, "%c", &c); // reading the '('
	fscanf (f, "%d", &n);
	if (n == -1) // null tree
	{	
		fscanf (f, "%c", &c); // reading the ')'
		return NULL;
	}
	else // not null
	{
		tree *t;
		t = (tree*) malloc (sizeof (tree));
		t->info = n;
		t->left = readTree (f);
		t->right = readTree (f);
		fscanf (f, "%c", &c); // reading the ')'
		return t;
	}
}

void printPreOrder (tree *t)
{
	if (t != NULL)
	{
		printf ("%d ", t->info);
		printPreOrder (t->left);
		printPreOrder (t->right);
	}
}

void printInOrder (tree *t)
{
	if (t != NULL)
	{
		printInOrder (t->left);
		printf ("%d ", t->info);
		printInOrder (t->right);
	}
}

void printPostOrder (tree *t)
{
	if (t != NULL)
	{
		printPostOrder (t->left);
		printPostOrder (t->right);
		printf ("%d ", t->info);
	}
}

void printLevel (tree *t, int count, int level)
{
	if (t != NULL)
	{
		if (count == level) printf ("%d ", t->info);
		else 
		{
			printLevel (t->left, count + 1, level);
			printLevel (t->right, count + 1, level);
		}
	}
}

int height (tree *t)
{
	if (t == NULL) return 0;
	else
	{
		int hr, hl;
		hl = height (t->left);
		hr = height (t->right);
		if (hl > hr) return hl + 1;
		else return hr + 1;
	}
}

void printInWidth (tree *t, int n)
{
	if (t != NULL && n < height (t))
	{
		printLevel (t, 0, n);
		printf ("\n");
		printInWidth (t, ++n);
	} 
}

int exists (tree * t, int n)
{
	if (t != NULL) 
	{
		if (t->info != n) return (exists (t->left, n) || exists (t->right, n));
		else return 1;
	}
	else return 0;
}

int nodeLevel (tree *t, int count, int n)
{
	if (t != NULL)
	{
		if (t->info != n) return (nodeLevel (t->left, count + 1, n) + nodeLevel (t->right, count + 1, n));
		else return count;
	}
	else return 0;
}


void printGreaterOrEqual (tree *t, int n)
{
	if (t!= NULL)
	{
		if (t->info >= n)
		{
			printf ("%d ", t->info);
			printGreaterOrEqual (t->left, n);
			printGreaterOrEqual (t->right, n);
		}	
		else printGreaterOrEqual (t->right, n);
	}
}

void printSmallerLeafs (tree *t, int n)
{
	if (t != NULL)
	{
		if ((t->left == NULL) && (t->right == NULL) && (t->info < n)) printf ("%d ", t->info);
		else
		{
			if ((t->info + 2) <= n)
			{
				printSmallerLeafs (t->left, n);
				printSmallerLeafs (t->right, n);
			}
			else printSmallerLeafs (t->left, n);
		}
	}
}

tree *insert (tree *t, int n)
{
	if (t == NULL)
	{
		t = (tree*)malloc(sizeof(tree));
		t->info = n;
		t->left = NULL;
		t->right = NULL;
	}
	else if (n <= t->info) t->left = insert (t->left, n);
	else t->right = insert (t->right, n);
	return t;
}

void remove (tree **t, int n)
{
	if (*t != NULL)
	{
		if ((*t)->info == n)
		{
			if (((*t)->left == NULL) && ((*t)->right == NULL))
			{
				free (*t);
				*t = NULL;
			}
			else if ((*t)->left == NULL)
			{
				tree *aux = (*t)->right;
				free (*t);
				*t = aux;
			}
			else if ((*t)->right == NULL)
			{
				tree *aux = (*t)->left;
				free (*t);
				*t = aux;
			}
			else
			{
				tree *aux = (*t)->left;
				while (aux->right != NULL) aux = aux->right;
				(*t)->info == aux->info;
				remove (&((*t)->left), aux->info);
			}
		}
		else if (n < (*t)->info) remove (&((*t)->left), n);
		else remove (&((*t)->right), n);
	}
}

void nodeDestroy (tree *t)
{
	if (t != NULL)
	{
		nodeDestroy (t->left);	
		nodeDestroy (t->right);
		free (t);
	}
}

void treeDestroy (tree *t)
{
	if (t != NULL)
	{
		nodeDestroy (t);
		free (t);	
	}	
}

int main ()
{
	int cmd = 0;
	int data = 0;
	char entry [50];
	tree *t;
	FILE *f;
	
	printf ("Provide the file of a tree to be worked on (don't forget the .txt):\n");
	scanf ("%s", &entry);
	printf ("\n");
	f = fopen (entry, "rt");
	while (cmd != 8)
	{
		printf ("Choose one of the operations below:\n");
		printf ("1: Read a tree from a user-supplied file\n");
		printf ("2: Print the tree\n");
		printf ("3: Check if an specific element existis in the tree\n");
		printf ("4: Print the level value of a specific node\n");
		printf ("5: Imprimir as folhas menores que um valor x\n");
		printf ("6: Insert a node x in the tree\n");
		printf ("7: Remove a node x from the tree\n");
		printf ("8: Halt\n");
		printf ("Choice: ");
		scanf ("%d", &cmd);
		switch (cmd)
		{
			case 1:
				t = readTree (f);
				printf ("Tree read.\n");
			break;
			case 2:
				printf ("Choose print order:\n");
				printf ("1: pre-order\n");
				printf ("2: in order\n");
				printf ("3: post-order\n");
				printf ("4: in width\n");
				printf ("Choice: ");
				scanf ("%d", &data);
				switch (data)
				{
					case 1: 
						printPreOrder (t); 
						printf ("\n");
					break;
					case 2:
						printInOrder (t);
						printf ("\n");
					break;
					case 3:
						printPostOrder (t);
						printf ("\n");
					break;
					case 4:
						printInWidth (t, 0);
					break;
				}
			break;
			case 3:
				printf ("Type a number to be verified: ");
				scanf ("%d", &data);
				if (exists (t, data)) printf ("The number is in the tree\n");
				else printf ("The number is not in the tree\n");
			break;
			case 4:
				printf ("Type the node to have its level value printed\n");
				scanf ("%d", &data);
				if (exists (t, data)) printf ("The not is on the level %d\n", nodeLevel (t, 0, data));
				else printf ("The number is not in the tree\n");
			break;
			case 5:
				printf ("Type the x value\n");
				scanf ("%d", &data);
				printSmallerLeafs (t, data);
			break;
			case 6:
				printf ("Type the number to be entered\n");
				scanf ("%d", &data);
				Inserir (t, data);
				printf ("Entered number.\n");
			break;
			case 7:
				printf ("Type the number to be removed\n");
				scanf ("%d", &data);
				remove (&t, data);
				printf ("Number removed.\n");
			break;
			case 8:
				treeDestroy (t);
			break;
		}
		printf ("\n");
	}
	
	fclose (f);	
	return 0;
}
