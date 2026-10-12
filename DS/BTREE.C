#include<stdio.h>
#include<conio.h>

typedef	 enum
{
	false = 0, true = 1
}bool ;

// B-Tree Node structure
struct BTreeNode
{
	int *keys;
	struct BTreeNode **children;
	int num_keys;
	bool is_leaf;
};

// B-Tree structure
struct BTree
{
	struct BTreeNode *root;
	int t;
};

// create a new B-Tree node
struct BTreeNode* createNode(int t, bool is_leaf)
{
	int i;
	struct BTreeNode *node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
	node->is_leaf = is_leaf;
	node->num_keys = 0;

	// Allocate memory for max keys (2*t - 1) and max children (2*t)
	node->keys = (int*)malloc(sizeof(int) * (2 * t - 1));
	node->children = (struct BTreeNode**)malloc(sizeof(struct BTreeNode*) * (2 * t));

	for (i = 0; i < 2 * t; i++)
	{
		node->children[i] = NULL;
	}

	return node;
}

// Function to initialize the B-Tree
struct BTree* createBTree(int t)
{
	struct BTree *tree ;
	if (t < 2)
	{
		printf("Error: Minimum degree 't' must be at least 2.\n");
		return NULL;
	}
	tree = (struct BTree*)malloc(sizeof(struct BTree));
	tree->t = t;
	tree->root = createNode(t, true);
	return tree;
}

// split a full child of a node
void splitChild(struct BTreeNode *parent, int i, struct BTreeNode *fullChild, int t)
{
	int j;
	struct BTreeNode *newChild ;

	printf("\n  [SPLIT TRIGGERED] Node is full with %d keys (Max allowed: %d).\n", fullChild->num_keys, 2 * t - 1);
	printf("  [SPLIT ACTION] Splitting node into two nodes of size %d...\n", t - 1);

	// Create a new node to store (t - 1) keys of fullChild
	newChild = createNode(t, fullChild->is_leaf);
	newChild->num_keys = t - 1;

	// Copy the last (t - 1) keys of fullChild to newChild
	for (j = 0; j < t - 1; j++)
	{
		newChild->keys[j] = fullChild->keys[j + t];
	}

	// Copy the last t children of fullChild to newChild if not leaf
	if (!fullChild->is_leaf)
	{
		for (j = 0; j < t; j++)
		{
			newChild->children[j] = fullChild->children[j + t];
		}
	}

	// Reduce the number of keys in fullChild
	fullChild->num_keys = t - 1;

	// Shift children of parent to make room for newChild
	for (j = parent->num_keys; j >= i + 1; j--)
	{
		parent->children[j + 1] = parent->children[j];
	}
	parent->children[i + 1] = newChild;

	// Shift keys of parent to insert median key from fullChild
	for (j = parent->num_keys - 1; j >= i; j--)
	{
		parent->keys[j + 1] = parent->keys[j];
	}

	// Move median key to parent
	parent->keys[i] = fullChild->keys[t - 1];
	parent->num_keys++;

	printf("   |-- Median key [%d] promoted to parent.\n", parent->keys[i]);
	printf("   |-- Split complete: Left node has %d keys, Right node has %d keys.\n", fullChild->num_keys, newChild->num_keys);
}

// Helper function to insert a key into a non-full node recursively
void insertNonFull(struct BTreeNode *node, int key, int t)
{
	int k;
	int i = node->num_keys - 1;

	if (node->is_leaf)
	{
		// Find insertion position and shift keys right
		while (i >= 0 && key < node->keys[i])
		{
			node->keys[i + 1] = node->keys[i];
			i--;
		}

		node->keys[i + 1] = key;
		node->num_keys++;

		printf(" --> Key [%d] inserted into %s node.\n", key, node->is_leaf ? "leaf" : "internal");
		printf("     Node status: Now contains %d key(s) [ ", node->num_keys);
		for (k = 0; k < node->num_keys; k++)
		{
			printf("%d ", node->keys[k]);
		}
		printf("] (Max capacity: %d)\n", 2 * t - 1);
	}
	else
	{
		// Find child to descend into
		while (i >= 0 && key < node->keys[i])
		{
			i--;
		}
		i++;

		// Check if child is full
		if (node->children[i]->num_keys == (2 * t - 1))
		{
			printf(" --> Target child node is FULL (%d keys). Splitting before descent...\n", node->children[i]->num_keys);
			splitChild(node, i, node->children[i], t);

			if (key > node->keys[i])
			{
				i++;
			}
		}
		insertNonFull(node->children[i], key, t);
	}
}

// Main insertion entry point
void insert(struct BTree *tree, int key)
{
	struct BTreeNode *r;
	struct BTreeNode *newRoot;
	int t;

	if (!tree || !tree->root) return;

	r = tree->root;
	t = tree->t;

	printf("\n==========================================\n");
	printf("[INSERTION START] Key to insert: %d\n", key);
	printf("==========================================\n");

	// Case 1: Root is full (contains 2*t - 1 keys)
	if (r->num_keys == (2 * t - 1))
	{
		printf(" --> Root node is FULL with %d keys.\n", r->num_keys);
		printf(" --> Splitting root node and increasing tree height...\n");

		newRoot = createNode(t, false);
		tree->root = newRoot;
		newRoot->children[0] = r;

		splitChild(newRoot, 0, r, t);
		insertNonFull(newRoot, key, t);
	}
	// Case 2: Root is not full
	else
	{
		insertNonFull(r, key, t);
	}
}

// Helper function for in-order traversal to view tree keys
void traverse(struct BTreeNode *root)
{
	int i;
	if (root == NULL) return;


	for (i = 0; i < root->num_keys; i++)
	{
		if (!root->is_leaf)
		{
			traverse(root->children[i]);
		}
		printf("%d ", root->keys[i]);
	}

	if (!root->is_leaf)
	{
		traverse(root->children[i]);
	}
}

// Interactive Main Menu
void main()
{
	struct BTree *bTree;
	int choice, t;



	printf("==========================================\n");
	printf("      INTERACTIVE B-TREE SIMULATION       \n");
	printf("==========================================\n");
	printf("Enter minimum degree 't' (minimum 2): ");
	scanf("%d", &t);

	while (t < 2)
	{
		printf("Invalid degree! Enter t >= 2: ");
		scanf("%d", &t);
	}

	bTree = createBTree(t);
	printf("\nB-Tree initialized with t = %d (Max keys per node = %d)\n", t, 2 * t - 1);

	while (1)
	{
		printf("\n-----------------------------\n");
		printf("Select an Option:\n");
		printf("1. Insert Key\n");
		printf("2. Traverse / Print Tree\n");
		printf("3. Exit\n");
		printf("-----------------------------\n");
		printf("Choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
			case 1:
			{
				int keyToInsert;
				printf("Enter key to insert: ");
				scanf("%d", &keyToInsert);
				insert(bTree, keyToInsert);
				break;
			}

			case 2:
			{
				printf("\nIn-order Traversal of B-Tree: ");
				traverse(bTree->root);
				printf("\n");
				break;
			}

			case 3:
			{
				printf("Exiting application.\n");
				free(bTree);
				exit(0) ;
			}

			default:
			{
				printf("Invalid choice! Choose between 1 and 3.\n");
				break;
			}
		}
	}
}