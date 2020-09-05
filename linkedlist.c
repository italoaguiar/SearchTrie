#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"


/* -------------------------------------------------------------
 * Insere um novo elemento no começo da lista encadeada
 * -------------------------------------------------------------
 */
struct ListEntry* insertEntry(char* value, int frequence, struct ListEntry* lst){
    if(lst == NULL){
        lst = (struct ListEntry*)malloc(sizeof(struct ListEntry));
        lst->content = value;
        lst->frequence = frequence;
        lst->next = NULL;
        return lst;
    }

    struct ListEntry* n = (struct ListEntry*)malloc(sizeof(struct ListEntry));
    n->content = value;
    n->frequence = frequence;
    n->next = lst;

    return n;
}

/* -------------------------------------------------------------
 * Imprime os elementos da lista encadeada
 * -------------------------------------------------------------
 */
printList(struct ListEntry* lst){
    while(lst != NULL){
        printf("%s (%i)\n", lst->content, lst->frequence);

        lst = lst->next;
    }
}


/* -------------------------------------------------------------
 * Imprime os elementos da lista encadeada e os desaloca da memória
 * -------------------------------------------------------------
 */
printListAndFree(struct ListEntry* lst){
    struct ListEntry* aux;
    while(lst != NULL){
        printf("%s (%i)\n", lst->content, lst->frequence);

        aux = lst;
        lst = lst->next;
        free(aux);
    }
    free(lst);
}
