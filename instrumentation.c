#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#include "instrumentation.h"
#include "trie.h"

#define BUILD_TIMES 20
#define ALFABET_SIZE 53


char * randString(int _size){
    char* string = malloc(sizeof(char) * _size);

    for(int i = 0; i< _size; i++)
        string = char_concat(string, getChar((int)(rand() % ALFABET_SIZE)));

    return string;
}


void storeResult(double result[], int len, char* fileName){
    FILE *fp;

    fp = fopen(fileName, "w+");

    for(int i = 0; i< len; i++){
        fprintf(fp, "%.6lf\n", result[i]);
    }

    fclose(fp);
}

/* ---------------------------------------------------
 * Mede o tempo gasto para montar a árvore
 * A ideia aqui é multiplicar a entrada por n vezes
 * para simular diferentes tamanhos de entradas
 * ----------------------------------------------------
 */
struct Node* measureTreeConstructionTime(char* file){
    struct Node* root = createRoot();
    double times[10];
    char* files[] = {"baskersvilles.txt", "baskersvilles2.txt","baskersvilles3.txt",
                     "baskersvilles4.txt","baskersvilles5.txt","baskersvilles6.txt",
                     "baskersvilles7.txt","baskersvilles8.txt","baskersvilles9.txt","baskersvilles10.txt"};

    for(int i = 0; i< 10; i++){
        clock_t start,end;

        start = clock();
        loadFile(files[i], root);
        end = clock();

        double r  = (double)(end-start)/CLOCKS_PER_SEC;
        times[i] = r;
    }

    storeResult(times, 10, "constructionTime.txt");

    return root;
}


void measureSearchTime(struct Node* root){
    double times[ALFABET_SIZE];
    char* sample[40] = {
        "sher", "me", "mornings", "s",
        "she", "old", "well-polished", "silver-plated",
        "c", "Baskervill", "restricti", "BASKERVIL",
        "practitioner", "appreciat", "l", "unfortun",
        "r", "examination", "whatsoever", "Staplet",
        "infrequent", "a", "reassuring", "k",
        "coffee-pot", "i", "importance", "successful",
        "Excellent", "Gutenbe", "breakfast", "you",
        "following", "companion", "e", "included",
        "February", "Produced", "produced", "CONTENTS"

    };
    //compressTree(root);

    for(int i = 0; i< 40; i++)
    {
        clock_t start = clock();
        find(sample[i], root);
        clock_t end = clock();

        times[i] = (double)(end-start)/CLOCKS_PER_SEC;
    }
    storeResult(times, 40, "searchTime.txt");
}

void startMeasure(char* file){
    struct Node* root = measureTreeConstructionTime(file);

    measureSearchTime(root);
}



