#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Elem {
    struct Elem *next;
    char *word;
};


struct Elem *bsort(struct Elem *list)
{
    if (list == NULL) return list;

    struct Elem* ast = list;
    while(true)
    {
        long i = 0;
        struct Elem *pst = ast;
        long len_pst = strlen(pst->word);
        long len_pst_next = strlen(pst->next->word);

        while(pst->next != NULL){
            if (len_pst > len_pst_next){
                char *c = pst->word;
                pst->word = pst->next->word;
                pst->next->word = c;
                i++;
            }
            pst = pst->next;
        }
        if (!i)
            return list;
    }
}
int main()
{
    char str[1000];
    gets(str);
    struct Elem * pl = NULL;
    char del[1000] = " ";
    char *word = strtok(str, del);
    struct Elem * fl;
    while (word != NULL){
        struct Elem * list = malloc(sizeof(struct Elem));
        list->word = word;
        if (pl != NULL) pl->next = list;
        else fl = list;
        pl = list;
        word = strtok(NULL, del);
    }
    if (pl != NULL) pl->next = NULL;
    fl = bsort(fl);
    struct Elem * list = fl;
    while(list != NULL){
        puts(list->word);
        struct Elem * c = list;
        list = list->next;
        free(c);
    }
    return 0;
}