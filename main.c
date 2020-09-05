#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bubblesort.h"
#include "instrumentation.h"


struct Node *root;
struct ListEntry* linkedList;
bool interactive = false;



int main(int argc, char *argv[])
{
    root = createRoot();

    if(strcmp(argv[2], "-i") == 0){
        loadFile(argv[1], root);
        compressTree(root);

        char input[20]; //buffer de 20 caracteres de entrada

        while(strcmp(input, "0")){
            printf("%s", "Entre com o sulfixo ou digite 0 para sair: ");

            scanf("%s", input);

            if(strcmp(input, "0") == 0)
                return;

            linkedList = NULL; //necessário para a função find alocar novo espaço de memória
            linkedList = find(input, root);
            bubbleSort(linkedList);
            printListAndFree(linkedList);
            printf("\n");
        }
    }

    if(strcmp(argv[2], "-exp"))
    {
        startMeasure(argv[1]);
    }

    return 0;
}
