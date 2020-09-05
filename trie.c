#include <stdio.h>
#include <stdbool.h>
#include "trie.h"

char lastToken;
struct Node* currentNode;

/* ------------------------------------------------
 * Gera o nó raiz da árvore
 * ------------------------------------------------
 */
struct Node* createRoot(){
    struct Node *root = malloc(sizeof(struct Node));
    for(int i = 0; i< ALFABET_SIZE; i++)
        root->childs[i] = NULL;


    currentNode = root;
    return root;
};


/* ------------------------------------------------
 * Efetua a abertura de um arquivo e o carrega na árvore
 * ------------------------------------------------
 */
void loadFile(char* file, struct Node* root){
    FILE * fp;
    int buffer_size = 1024;
    char* buffer = malloc(buffer_size);
    size_t message;

    fp = fopen(file, "r");
    if (fp == NULL){
        printf("Arquivo nao encontrado.");
        return;
    }

    int i = 0;
    //otimiza a leitura utilizando um buffer
    while ((message = fread(buffer, 1, buffer_size, fp)) > 0) {
        for(i = 0; i< message; i++)
            insert(buffer[i], root);

        i++;
    }
}

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

/* ------------------------------------------------
 * Converte o índice da entrada na árvore para
 * um caractere da tabela ASCII
 * ------------------------------------------------
 */
char getChar(int index){
    if(index < 26)
        return (char)(index + 65);
    if(index < ALFABET_SIZE -1)
        return (char)(index + 71);

    return (char)45;
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

        //atribui a frequência
        node->childs[index]->frequence = 0;
        node->childs[index]->value = NULL;

    }
    //retorna o novo nó
    return node->childs[index];
}


/* ------------------------------------------------
 * Retorna se um caractere está presente no conjunto
 * válido de entradas da árvore: "[A-Z|a-z|-]*"
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
void insert(char c, struct Node* root)
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



/* ------------------------------------------------
 * Concatena um caractere com uma string
 * ------------------------------------------------
 */
char * char_concat(char* string, char c)
{
    size_t len = strlen(string);
    char *aux = malloc(len + 2 );
    strcpy(aux, string);
    aux[len] = c;
    aux[len + 1] = '\0';
    return aux;
}


/* ------------------------------------------------
 * Calcula todas as permutações de nós de uma
 * árvore ou sub árvore junto da frequência
 * ------------------------------------------------
 */
struct ListEntry* linkedList;
struct ListEntry* getCombinations(struct Node* node, char * prefix)
{
    if(node->frequence > 0){
        if(node->value != NULL)
            linkedList = insertEntry(strcat(prefix, node->value), node->frequence, linkedList);
        else
            linkedList = insertEntry(prefix, node->frequence, linkedList);
    }

    for(int i = 0; i< ALFABET_SIZE; i++)
    {
        if(node->childs[i] != NULL)
        {
            getCombinations(node->childs[i], char_concat(prefix, getChar(i)));
        }
    }


    return linkedList;
}


/* ------------------------------------------------
 * Calcula se um nó possui um único filho
 * ------------------------------------------------
 */
int hasOneChild(struct Node* node){
    int r = 0;
    int out = -1;
    for(int i = 0; i< ALFABET_SIZE; i++){
        if(node->childs[i] != NULL){
            r = r + 1;
            out = i;
        }
    }

    if(r > 1) return -1;

    return out;
}

/* ------------------------------------------------
 * Calcula se um no não possui
 * ------------------------------------------------
 */
int hasNoChild(struct Node* node){
    for(int i = 0; i< ALFABET_SIZE; i++){
        if(node->childs[i] != NULL){
            return false;
        }
    }
    return true;
}


/* -------------------------------------------------
 * Comprime a árvore removendo nós com um único filho
 * e adicionando seus valores aos nós pais
 * -------------------------------------------------
 */
void compressTree(struct Node* node){
    for(int i = 0; i< ALFABET_SIZE; i++)
    {
        if(node->childs[i] != NULL)
        {
            compressTree(node->childs[i]);
        }
    }

    int oneChild = hasOneChild(node);
    if(node->frequence == 0 && oneChild != -1 && hasNoChild(node->childs[oneChild]))
    {
        struct Node* item = node->childs[oneChild];
        node->frequence = item->frequence;
        char* value = char_concat("", getChar(oneChild));
        if(item->value != NULL){
            node->value = strcat(value, item->value);
        }
        else{
            node->value = value;
        }
        free(item);
        node->childs[oneChild] = NULL;
    }
}


/* ------------------------------------------------
 * Busca por um termo na árvore.
 * Busca por um determinado nó e imprime sua permutação de filhos
 * ------------------------------------------------
 */
struct ListEntry* find(char* input, struct Node* root)
{
    int len = strlen(input);
    struct Node * aux = root;
    int index = 0;
    int index2 = 0;

    for(int i = 0; i< len; i++)
    {
        index = getIndex(input[i]);
        if(aux->childs[index] != NULL)
        {
            aux = aux->childs[index];
            continue;
        }
        if(aux->value != NULL){
            if(aux->value[index2] == input[i]){
                index2 = index2 + 1;
                continue;
            }
        }
        printf("Nao foi encontrado nenhum resultado\n");
        return;
    }

    return getCombinations(aux, input);
}

/* -----------------------------------------------
 * Calcula o número de nós da árvore
 * -----------------------------------------------
 */
int count(struct Node* node){
    int level = 1;
    for(int i = 0; i< ALFABET_SIZE; i++)
    {
        if(node->childs[i] != NULL)
        {
            level += count(node->childs[i]) + 1;
        }
    }
    return level;
}
