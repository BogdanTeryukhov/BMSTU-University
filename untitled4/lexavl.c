#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node Node;

struct Node
{
    int v, balance;
    unsigned long k;
    Node *parent, *left, *right;
};

typedef struct Tree
{
    Node *root;
} Tree;

Node *Descend(Tree *t, unsigned long k)
{
    Node *x = t->root;
    while (x && x->k != k)
    {
        if (k < x->k) {
            x = x->left;
        }else {
            x = x->right;
        }
    }
    return x;
}

void Insert(Tree *t, unsigned long k, int v)
{
    Node *y = (Node*) malloc(sizeof(Node));
    y->parent = NULL; y->left = NULL; y->right = NULL;
    y->k = k;
    y->v = v;
    y->balance = 0;

    if (t->root == NULL){
        t->root = y;
        return;
    }

    Node *x = t->root;
    while (true)
    {
        if (k < x->k)
        {
            if (x->left == NULL)
            {
                x->left = y;
                y->parent = x;
                break;
            }
            x = x->left;
        }
        else
        {
            if (x->right == NULL)
            {
                x->right = y;
                y->parent = x;
                break;
            }
            x = x->right;
        }
    }
}

Tree *ReplaceNode(Tree *t, Node *x, Node *y)
{
    if (x == t->root){
        t->root = y;
        if (y != NULL) {
            y->parent = NULL;
        }
    }
    else{
        Node *p = x->parent;
        if (y != NULL) {
            y->parent = p;
        }
        if (p->left == x) {
            p->left = y;
        }else {
            p->right = y;
        }
    }
    return t;
}

void NodeClear(Node *x)
{
    if(x)
    {
        if(x->left) {
            NodeClear(x->left);
        }
        if(x->right) {
            NodeClear(x->right);
        }
        free(x);
    }
}

void TotalClear(Tree *t)
{
    if(t->root){
        NodeClear(t->root);
    }
}

Node *RotateLeft(Tree *t, Node *x)
{
    Node *y = x->right;
    if (y == NULL){
        printf("Error");
    }
    ReplaceNode(t, x, y);

    Node *b = y->left;
    if(b != NULL) {
        b->parent = x;
    }
    x->right = b;
    x->parent = y;
    y->left = x;
    //для АВЛ дерева следует дописать
    x->balance--;
    if(y->balance > 0)
        x->balance = x->balance - y->balance;

    y->balance--;
    if(x->balance < 0)
        y->balance = y->balance + x->balance;
}

Node *RotateRight(Tree *t, Node *x)
{
    Node *y = x->left;
    ReplaceNode(t, x, y);
    Node *b = y->right;

    if(b != NULL) {
        b->parent = x;
    }
    x->left = b;
    x->parent = y;
    y->right = x;
    //для АВЛ дерева следует дописать
    x->balance++;
    if(y->balance < 0)
        x->balance = x->balance - y->balance;

    y->balance++;
    if(x->balance > 0)
        y->balance = y->balance + x->balance;
}

Node *InsertAVL(Tree *t, unsigned long k, int v)
{
    Insert(t, k, v);

    Node *a = t->root;
    a->balance = 0;
    Node *x = a->parent;

    while (true){
        x = a->parent;
        if (x == NULL) {
            break;
        }
        if (a == x->left)
        {
            x->balance--;
            if (x->balance == 0) {
                break;
            }
            if (x->balance == -2){
                if (a->balance == 1) {
                    RotateLeft(t, a);
                }
                RotateRight(t, x);
                break;
            }
        }
        else
        {
            x->balance++;
            if (x->balance == 0) {
                break;
            }
            if (x->balance == 2){
                if (a->balance == -1){
                    RotateRight(t, a);
                }
                RotateLeft(t, x);
                break;
            }
        }
    }
    return a;
}

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    while((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int SPEC_COUNT = 6;
char SPECS[] = {'+', '-', '*', '/', '(', ')'};

int SpecIndex(char c)
{
    for(int i = 0; i < SPEC_COUNT; i++)
        if(c == SPECS[i]) return i;
    return -1;
}

int number_check(char c) { return c >= '0' && c <= '9'; }

int letter_check(char c){ return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z'; }

int main()
{
    int n;
    scanf("%d\n", &n);

    char *str = (char *)malloc(sizeof(char) * (n + 1));
    char *str_ptr_copy = str;
    gets(str);

    Tree t;
    t.root = NULL;
    int current_ident_id = 0;

    while(*str)
    {
        while(*str == ' ') str++;

        int spec_index = SpecIndex(*str);
        if(spec_index != -1)
        {
            printf("SPEC %d\n", spec_index);
            str++;
        }
        else if(number_check(*str))
        {

            char const_number[1024];
            int j = 0;
            while (SpecIndex(*str) == -1 && *str && *str != ' ')
                const_number[j++] = *(str++);
            const_number[j] = '\0';

            printf("CONST %s\n", const_number);
        }
        else if(letter_check(*str))
        {
            char *word = (char *)malloc(sizeof(char) * 1024);
            int j = 0;
            while (SpecIndex(*str) == -1 && *str && *str != ' ')
                word[j++] = *(str++);

            word[j] = '\0';
            unsigned long word_hash = hash(word);
            int found = Descend(&t, word_hash) != NULL;
            if(!found)
                InsertAVL(&t, word_hash, current_ident_id++);

            printf("IDENT %d\n", Descend(&t, word_hash)->v);

            if(found) free(word);
        }
    }

    TotalClear(&t);
    free(str_ptr_copy);
}
