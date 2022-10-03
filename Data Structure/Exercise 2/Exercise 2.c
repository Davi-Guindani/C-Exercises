#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree
{
	int info;
	struct tree *left, *right;
} tree;

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
		tree *a;
		a = (tree*) malloc (sizeof (tree));
		a->info = n;
		a->left = readTree (f);
		a->right = readTree (f);
		fscanf (f, "%c", &c); // reading the ')'
		return a;
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

int countLevel (tree *t, int count, int level)
{
	if (t == NULL) return 0;
	else 
	{
		if (count == level) return 1;
		else return countLevel (t->left, count + 1, level) + countLevel (t->right, count + 1, level);
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

int countElements (tree *t) 
{
	if (t != NULL) return 1 + countElements (t->left) + countElements (t->right);
	else return 0;
}

void printLeafs (tree *t, int count, int h)
{
	if (t != NULL)
	{
		if (count == h - 1) printf ("%d ", t->info);
		else 
		{
			printLeafs (t->left, count + 1, h);
			printLeafs (t->right, count + 1, h);
		}
	}
}

int balanced (tree *t)
{
	if (t != NULL)
	{
		int hr, hl;
		hl = height (t->left);
		hr = height (t->right);
		if (abs (hl - hr) <= 1) return (balanced (t->left) && balanced (t->right));
		else return 0;
	}
	else return 1;
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
	while (cmd != 9)
	{
		printf ("Choose one of the operations below:\n");
		printf ("1: Read a tree from a user-supplied file\n");
		printf ("2: Print the tree\n");
		printf ("3: Check if an specific element existis in the tree\n");
		printf ("4: Count the elements in the tree\n");
		printf ("5: Print the leaf nodes in the tree\n");
		printf ("6: Check if a tree is balanced\n");
		printf ("7: Check if a tree is full\n");
		printf ("8: Print the level value of a specific node\n");
		printf ("9: Halt\n");
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
				printf ("The tree has %d elements\n", countElements (t));
			break;
			case 5:
				printLeafs (t, 0, height (t));
			break;
			case 6:
				if (balanced (t)) printf ("The tree is balanced\n");
				else printf ("The tree is not balanced\n");
			break;
			case 7:
				if (countElements (t) == (pow (2, height (t)) - 1)) printf ("The tree is full\n");
				else printf ("The tree is not full\n");
			break;
			case 8:
				printf ("Type the node to have its level value printed\n");
				scanf ("%d", &data);
				if (exists (t, data)) printf ("The not is on the level %d\n", nodeLevel (t, 0, data));
				else printf ("The number is not in the tree\n");
			break;
			case 9:
				treeDestroy (t);
			break;
		}
		printf ("\n");
	}
	fclose (f);
	return 0;
}
