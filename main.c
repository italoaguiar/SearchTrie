#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bubblesort.h"


struct Node *root;
struct ListEntry* linkedList;
bool interactive = false;



int main(int argc, char *argv[])
{
    root = createRoot();

    if(strcmp(argv[2], "-i") == 0){
        loadFile(argv[1], root);

        char input[20]; //buffer de 20 caracteres de entrada

        while(strcmp(input, "0")){
            printf("%s", "Entre com o sulfixo ou digite 0 para sair: ");

            scanf("%s", input);

            if(strcmp(input, "0") == 0)
                return;

            linkedList = NULL; //necess�rio para a fun��o find alocar novo espa�o de mem�ria
            linkedList = find(input, root);
            bubbleSort(linkedList);
            printListAndFree(linkedList);
            printf("\n");
        }
    }

    return 0;
}
