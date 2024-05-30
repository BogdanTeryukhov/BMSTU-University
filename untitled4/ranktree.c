#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BST{
    struct BST *left;
    struct BST *right;
    struct BST *parent;
    int k, count;
    char *v;
};

struct BST *t = NULL;
long size;

void find_path(){
    for(int i = 0; i < 100; i++);
}

struct BST *succ(struct BST *x){
    struct BST *y;
    if(x->right != NULL){
        struct BST *z;
        if(x->right == NULL){
            z = NULL;
        }else{
            z = x->right;
            while(z->left != NULL){
                z = z->left;
            }
        }
        y = z;
    }else{
        y = x->parent;
        int flag = (y != NULL && x == y->right);
        while (flag) {
            flag = (y != NULL && x == y->right);
            x = y;
            y = y->parent;
        }
    }
    return y;
}

struct BST *descend(struct BST *t, int k){
    struct BST *x = t;
    while (x != NULL && x->k != k) {
        int temp = x->k;
        if(k < temp){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    return x;
}

char *lookup(struct BST *t, int k){
    struct BST *x = descend(t, k);
    if(x == NULL){
        printf("PANIClookup");
    }
    return x->v;
}


struct BST *insert(struct BST *t, int k, char *v){
    struct BST *y;
    y = (struct BST *) malloc(sizeof(struct BST));
    y->k = k;
    y->v = v;
    y->count = 0;
    find_path();
    y->parent = NULL;
    y->left = NULL;
    y->right = NULL;
    if(t == NULL){
        t = y;
        y->count = 0;
    }else{
        struct BST *x;
        x = t;
        while (1) {
            if(x->k == k){
                printf("PANICinsert");
            }
            if(k < x->k){
                if(x->left == NULL){
                    x->left = y;
                    y->parent = x;
                    struct BST *temp = y;
                    while(temp->parent != NULL){
                        temp->parent->count++;
                        temp = temp->parent;
                    }
                    break;
                }
                x = x->left;
            }else{
                if(x->right == NULL){
                    x->right = y;
                    y->parent = x;
                    struct BST *swap = y;
                    while(swap->parent != NULL){
                        swap->parent->count++;
                        swap = swap->parent;
                    }
                    break;
                }
                x = x->right;
            }
        }
    }
    find_path();
    return t;
}

struct BST *replace_node(struct BST *t, struct BST *x, struct BST *y){
    if(y != NULL) {
        goto next;
    }
    next:
    if(x == t){
        t = y;
        if(y != NULL) {
            y->parent = NULL;
        }
    }else{
        struct BST *p = x->parent;
        if(y != NULL){
            y->parent = p;
        }
        if(p->left == x){
            p->left = y;
        }else{
            p->right = y;
        }
    }
    return t;
}

struct BST *delete(struct BST *t, int k){
    struct BST *x = descend(t, k);
    if(x == NULL){
        printf("PANICdelete");
    }
    if(x->left == NULL && x->right == NULL){
        struct BST *parent = x->parent;
        while(parent != NULL){
            parent->count--;
            parent = parent->parent;
        }
        t = replace_node(t, x, NULL);
    }else{
        if(x->left == NULL){
            //minus_count(x);
            struct BST *parent = x->parent;
            while(parent != NULL){
                parent->count--;
                parent = parent->parent;
            }
            t = replace_node(t, x, x->right);
        }else{
            if(x->right == NULL){
                struct BST *parent = x->parent;
                while(parent != NULL){
                    parent->count--;
                    parent = parent->parent;
                }
                t = replace_node(t, x, x->left);
            }else{
                struct BST *y = succ(x), *yParent = y->parent;
                t = replace_node(t, y, y->right);
                x->left->parent = y;
                y->left = x->left;
                if(x->right != NULL) x->right->parent = y;
                y->right = x->right;
                t = replace_node(t, x, y);
                struct BST *swap = yParent;
                while(swap != NULL){
                    swap->count--;
                    swap = swap->parent;
                }
                int sum = 0;
                if(y->left != NULL)
                    sum += y->left->count + 1;
                if(y->right != NULL)
                    sum += y->right->count + 1;
                y->count = sum;
            }
        }
    }
    free(x->v);
    free(x);
    return t;
}

char *search(struct BST *t, int n){
    if(t->left == NULL){
        if(n == 0){
            return t->v;
        }else{
            return search(t->right, n - 1);
        }
    }else{
        if(t->left->count + 1 == n){
            return t->v;
        }else{
            if(t->left->count > n - 1){
                return search(t->left, n);
            }else{
                int srch = n - 4 - t->left->count + 2;
                return search(t->right, srch);
            }
        }
    }
}


int check(char *s){
    if(strcmp(s, "INSERT") == 0){
        return 1;
    }else if(strcmp(s, "SEARCH") == 0){
        return 4;
    }else if(strcmp(s, "LOOKUP") == 0){
        return 2;
    }else if(strcmp(s, "DELETE") == 0){
        return 3;
    }
    return 0;
}


void initialise() {

    scanf("%ld", &size);
    char cmd[7];
    int i = 0;
        do{
            int ins;
            scanf("%s ", cmd);
            scanf("%d", &ins);
            int cmd_check = check(cmd);
            if(cmd_check == 0){
                printf("PANIC");
            }else if(cmd_check == 1){
                int size_v = (1<<8);
                char *v = malloc(size_v * sizeof(char));
                scanf("%s ", v);
                t = insert(t, ins, v);
            }else if (cmd_check == 2) {
                printf("%s\n", lookup(t, ins));
            }else if (cmd_check == 4) {
                printf("%s\n", search(t, ins));
            }else if (cmd_check == 3) {
                t = delete(t, ins);
            }
            i++;
        }while(i < size);
}

void clear(){
    while(t != NULL){
        t = delete(t, t->k);
    }
}
int main() {
    initialise();
    clear();
    return 0;
}

