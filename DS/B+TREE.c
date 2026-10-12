#include <stdio.h>
#include <stdlib.h>

#define mindegree 3

typedef struct Node
{
    int* keys;
    int t;
    struct Node** children;
    int n;
    int leaf;
    struct Node* next;
} Node;

typedef struct BTree
{
    Node* root;
    int t;
} BTree;


/* Create Node */
Node* createNode(int t, int leaf)
{
    Node* newNode;

    newNode = (Node*)malloc(sizeof(Node));

    newNode->t = t;
    newNode->leaf = leaf;

    newNode->keys =
        (int*)malloc((2 * t - 1) * sizeof(int));

    newNode->children =
        (Node**)malloc((2 * t) * sizeof(Node*));

    newNode->n = 0;
    newNode->next = NULL;

    return newNode;
}

BTree* createBTree(int t)
{
    BTree* btree;

    btree = (BTree*)malloc(sizeof(BTree));

    btree->t = t;

    
    btree->root = createNode(t, 1);

    return btree;
}

void display(Node* node)
{
    int i;

    if (node == NULL)
        return;

    for (i = 0; i < node->n; i++)
    {
        if (!node->leaf)
        {
            display(node->children[i]);
        }

        printf("%d ", node->keys[i]);
    }

    if (!node->leaf)
    {
        display(node->children[i]);
    }
}

int search(Node* node, int key)
{
    int i = 0;

    while (i < node->n && key > node->keys[i])
    {
        i++;
    }

    if (i < node->n && key == node->keys[i])
    {
        return 1;
    }

    if (node->leaf)
    {
        return 0;
    }

    return search(node->children[i], key);
}

void splitChild(Node* parent, int i, Node* child)
{
    int t;
    int j;

    Node* newChild;

    t = child->t;

    newChild = createNode(t, child->leaf);

    newChild->n = t - 1;

    for (j = 0; j < t - 1; j++)
    {
        newChild->keys[j] =
            child->keys[j + t];
    }

    if (!child->leaf)
    {
        for (j = 0; j < t; j++)
        {
            newChild->children[j] =
                child->children[j + t];
        }
    }

    child->n = t - 1;

    for (j = parent->n; j >= i + 1; j--)
    {
        parent->children[j + 1] =
            parent->children[j];
    }

    parent->children[i + 1] = newChild;

    for (j = parent->n - 1; j >= i; j--)
    {
        parent->keys[j + 1] =
            parent->keys[j];
    }

    parent->keys[i] =
        child->keys[t - 1];

    parent->n++;
}

void insertNonFull(Node* node, int key)
{
    int i;

    i = node->n - 1;

    if (node->leaf)
    {
        while (i >= 0 && node->keys[i] > key)
        {
            node->keys[i + 1] =
                node->keys[i];

            i--;
        }

        node->keys[i + 1] = key;

        node->n++;
    }
    else
    {
        while (i >= 0 && node->keys[i] > key)
        {
            i--;
        }

        i++;

        if (node->children[i]->n ==
            2 * node->t - 1)
        {
            splitChild(node, i,
                       node->children[i]);

            if (node->keys[i] < key)
            {
                i++;
            }
        }

        insertNonFull(node->children[i], key);
    }
}

void insert(BTree* btree, int key)
{
    Node* root;
    Node* newRoot;

    root = btree->root;

    if (root->n == 2 * btree->t - 1)
    {

        newRoot =
            createNode(btree->t, 0);

        newRoot->children[0] = root;

        splitChild(newRoot, 0, root);

        insertNonFull(newRoot, key);

        btree->root = newRoot;
    }
    else
    {
        insertNonFull(root, key);
    }
}

void deleteKeyHelper(Node* node, int key);
int findKey(Node* node, int key);
void removeFromLeaf(Node* node, int idx);
int getPredecessor(Node* node, int idx);
void fill(Node* node, int idx);
void borrowFromPrev(Node* node, int idx);
void borrowFromNext(Node* node, int idx);
void merge(Node* node, int idx);

void deleteKey(BTree* btree, int key)
{
    Node* root;

    root = btree->root;

    deleteKeyHelper(root, key);

    if (root->n == 0 && !root->leaf)
    {
        btree->root =
            root->children[0];

        free(root);
    }
}

void deleteKeyHelper(Node* node, int key)
{
    int idx;
    int isLastChild;

    idx = findKey(node, key);

    if (idx < node->n &&
        node->keys[idx] == key)
    {
        if (node->leaf)
        {
            removeFromLeaf(node, idx);
        }
        else
        {
            int predecessor;

            predecessor =
                getPredecessor(node, idx);

            node->keys[idx] = predecessor;

            deleteKeyHelper(
                node->children[idx],
                predecessor);
        }
    }
    else
    {
        if (node->leaf)
        {
            printf("Key %d not found in the B+ tree.\n",
                   key);

            return;
        }

        isLastChild =
            (idx == node->n);

        if (node->children[idx]->n <
            node->t)
        {
            fill(node, idx);
        }

        if (isLastChild &&
            idx > node->n)
        {
            deleteKeyHelper(
                node->children[idx - 1],
                key);
        }
        else
        {
            deleteKeyHelper(
                node->children[idx],
                key);
        }
    }
}

int findKey(Node* node, int key)
{
    int idx;

    idx = 0;

    while (idx < node->n &&
           key > node->keys[idx])
    {
        idx++;
    }

    return idx;
}

void removeFromLeaf(Node* node, int idx)
{
    int i;

    for (i = idx + 1;
         i < node->n;
         i++)
    {
        node->keys[i - 1] =
            node->keys[i];
    }

    node->n--;
}

int getPredecessor(Node* node, int idx)
{
    Node* curr;

    curr = node->children[idx];

    while (!curr->leaf)
    {
        curr =
            curr->children[curr->n];
    }

    return curr->keys[curr->n - 1];
}

void fill(Node* node, int idx)
{
    if (idx != 0 &&
        node->children[idx - 1]->n >= node->t)
    {
        borrowFromPrev(node, idx);
    }
    else if (idx != node->n &&
             node->children[idx + 1]->n >= node->t)
    {
        borrowFromNext(node, idx);
    }
    else
    {
        if (idx != node->n)
        {
            merge(node, idx);
        }
        else
        {
            merge(node, idx - 1);
        }
    }
}

void borrowFromPrev(Node* node, int idx)
{
    Node* child;
    Node* sibling;
    int i;

    child = node->children[idx];
    sibling = node->children[idx - 1];

    for (i = child->n - 1;
         i >= 0;
         i--)
    {
        child->keys[i + 1] =
            child->keys[i];
    }

    if (!child->leaf)
    {
        for (i = child->n;
             i >= 0;
             i--)
        {
            child->children[i + 1] =
                child->children[i];
        }
    }

    child->keys[0] =
        node->keys[idx - 1];

    if (!child->leaf)
    {
        child->children[0] =
            sibling->children[sibling->n];
    }

    node->keys[idx - 1] =
        sibling->keys[sibling->n - 1];

    child->n++;
    sibling->n--;
}

void borrowFromNext(Node* node, int idx)
{
    Node* child;
    Node* sibling;
    int i;

    child = node->children[idx];
    sibling = node->children[idx + 1];

    child->keys[child->n] =
        node->keys[idx];

    if (!child->leaf)
    {
        child->children[child->n + 1] =
            sibling->children[0];
    }

    node->keys[idx] =
        sibling->keys[0];

    for (i = 1;
         i < sibling->n;
         i++)
    {
        sibling->keys[i - 1] =
            sibling->keys[i];
    }

    if (!sibling->leaf)
    {
        for (i = 1;
             i <= sibling->n;
             i++)
        {
            sibling->children[i - 1] =
                sibling->children[i];
        }
    }

    child->n++;
    sibling->n--;
}

void merge(Node* node, int idx)
{
    Node* child;
    Node* sibling;
    int i;

    child = node->children[idx];
    sibling = node->children[idx + 1];

    child->keys[child->n] =
        node->keys[idx];

    if (!child->leaf)
    {
        child->children[child->n + 1] =
            sibling->children[0];
    }

    for (i = 0;
         i < sibling->n;
         i++)
    {
        child->keys[i + child->n + 1] =
            sibling->keys[i];
    }

    if (!child->leaf)
    {
        for (i = 0;
             i <= sibling->n;
             i++)
        {
            child->children[i + child->n + 1] =
                sibling->children[i];
        }
    }

    for (i = idx + 1;
         i < node->n;
         i++)
    {
        node->keys[i - 1] =
            node->keys[i];
    }

    for (i = idx + 2;
         i <= node->n;
         i++)
    {
        node->children[i - 1] =
            node->children[i];
    }

    child->n += sibling->n + 1;

    node->n--;

    free(sibling);
}

int main()
{
    BTree* btree;

    int n;
    int key;
    int i;

    int searchKey;
    int deleteKeyValue;

    int found;

    btree = createBTree(mindegree);

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("\nEnter %d elements:\n", n);

    for (i = 0; i < n; i++)
    {
        printf("Enter element %d: ",
               i + 1);

        scanf("%d", &key);

        insert(btree, key);
    }

    printf("\nB+ Tree after insertion: ");

    display(btree->root);

    printf("\n");

    printf("\nEnter key to search: ");
    scanf("%d", &searchKey);

    found =
        search(btree->root, searchKey);

    if (found)
    {
        printf("Key %d found in the B+ tree.\n",
               searchKey);
    }
    else
    {
        printf("Key %d not found in the B+ tree.\n",
               searchKey);
    }

    printf("\nEnter key to delete: ");
    scanf("%d", &deleteKeyValue);

    deleteKey(btree, deleteKeyValue);

    printf("\nB+ Tree after deletion: ");

    display(btree->root);

    printf("\n");

    found =
        search(btree->root,
               deleteKeyValue);

    if (found)
    {
        printf("Key %d found in the B+ tree.\n",
               deleteKeyValue);
    }
    else
    {
        printf("Key %d not found in the B+ tree.\n",
               deleteKeyValue);
    }

    return 0;
}