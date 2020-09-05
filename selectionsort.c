#include <stdio.h>
#include <stdlib.h>
#include "selectionksort.h"

void swap(struct ListEntry* a, struct ListEntry* b)
{
    char* aux1 = a->content;
    int aux2 = a->frequence;

    a->content = b->content;
    a->frequence = b->frequence;

    b->content = aux1;
    b->frequence = aux2;
}

void prt(struct ListEntry* lst){
    while(lst != NULL){
        printf("%i ", lst->frequence);

        lst = lst->next;
    }
}

void selectionSort(struct ListEntry* start)
{
    struct ListEntry* ax1 = NULL;
    struct ListEntry* ax2 = NULL;
    int swapped = 0;

    do
    {
        swapped = 0;
        ax2 = start;

        while (ax2->next != ax1)
        {
            if (ax2->frequence < ax2->next->frequence)
            {
                swap(ax2, ax2->next);
                swapped = 1;
            }
            ax2 = ax2->next;
        }
        ax1 = ax2;
    }
    while (swapped);

}
