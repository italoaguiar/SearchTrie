#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALFABET_SIZE 53

struct Node {
    char value;
    int frequence;
    struct Node* childs[ALFABET_SIZE];
};


/* ------------------------------------------------
 * Converte o índice da tabela ASCII para
 * um índice do array de entradas da árvore
 * ------------------------------------------------
 */
int getIndex(char c)
{
    if(c > 64 && c < 91)
        return c - 65;

    if(c > 96 && c < 123)
        return c - 71;

    if(c == 45)
        return ALFABET_SIZE -1;

    return -1; //caractere inválido
}



/* --------------------------------------------------
 * Insere um caractere em um nó específico da árvore
 * --------------------------------------------------
 */
struct Node* insertAt(char c, struct Node* node)
{
    int index = getIndex(c);
    if(node->childs[index] == NULL)
    {
        //aloca o espaço do novo nó em memória
        node->childs[index] = malloc(sizeof(struct Node));

        //inicializa as posições do array de caracteres
        for(int i = 0; i< ALFABET_SIZE; i++)
            node->childs[index]->childs[i] = NULL;

        //atribui o caractere e a frequência
        node->childs[index]->value = c;
        node->childs[index]->frequence = 0;

    }
    //retorna o novo nó
    return node->childs[index];
}


/* ------------------------------------------------
 * Retorna se um caractere está presente no conjunto
 * válido de entradas da árvore: "[A-Z|a-z|-]"
 * ------------------------------------------------
 */
bool isValidToken(char c)
{
    return ((c > 64 && c < 91) || (c > 96 && c < 123));
}



/* ------------------------------------------------
 * Insere um novo caractere na árvore. Quando um caractere
 * não presente no alfabeto é recebido, a palavra é finalizada
 * ------------------------------------------------
 */
char lastToken;
struct Node *root;
struct Node* currentNode;
void insert(char c)
{
    if(isValidToken(c) || (isValidToken(lastToken) && c == 45)) //mantem palavras com hífem (45)
    {
        currentNode = insertAt(c, currentNode);
    }
    else if(isValidToken(lastToken))
    {
        currentNode->frequence++;
        currentNode = root;
    }

    lastToken = c;
}

char * char_concat(char* string, char c)
{
    size_t len = strlen(string);
    char *aux = malloc(len + 2 );
    strcpy(aux, string);
    aux[len] = c;
    aux[len + 1] = '\0';
    return aux;
}

void print(struct Node* node, char * prefix)
{
    if(node->frequence > 0)
        printf("%s (%i)\n", prefix, node->frequence);

    for(int i = 0; i< ALFABET_SIZE; i++)
    {
        if(node->childs[i] != NULL)
        {
            print(node->childs[i], char_concat(prefix, node->childs[i]->value));
        }
    }
    return;
}

void find(char* input)
{
    int len = strlen(input);
    struct Node * aux = root;
    int index = 0;

    for(int i = 0; i< len; i++)
    {
        index = getIndex(input[i]);
        if(aux->childs[index] != NULL)
        {
            aux = aux->childs[index];
            continue;
        }
        printf("Nao foi encontrado nenhum resultado\n");
        return;
    }

    print(aux, input);
}


int main()
{
    FILE * fp;
    int buffer_size = 1024;
    char* buffer = malloc(buffer_size);
    size_t message;

    fp = fopen("baskersvilles.txt", "r");
    if (fp == NULL){
        printf("Arquivo nao encontrado.");
        exit(EXIT_FAILURE);
    }

    root = malloc(sizeof(struct Node));
    for(int i = 0; i< ALFABET_SIZE; i++)
        root->childs[i] = NULL;

    currentNode = root;

    int i = 0;
    //otimiza a leitura utilizando um buffer
    while ((message = fread(buffer, 1, buffer_size, fp)) > 0) {
        for(i = 0; i< message; i++)
            insert(buffer[i]);

        i++;
    }
    find("you");
    printf("Hello world!\n");
    return 0;
}
