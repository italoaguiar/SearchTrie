#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

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

printList(struct ListEntry* lst){
    while(lst != NULL){
        printf("%s (%i)\n", lst->content, lst->frequence);

        lst = lst->next;
    }
}
