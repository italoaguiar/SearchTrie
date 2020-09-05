#include <stdbool.h>


//define o tamanho do alfabeto
#define ALFABET_SIZE 53

/* ------------------------------------------------
 * Gera o nó raiz da árvore
 * ------------------------------------------------
 */
struct Node* createRoot();


/* ------------------------------------------------
 * Efetua a abertura de um arquivo e o carrega na árvore
 * ------------------------------------------------
 */
void loadFile(char* file, struct Node* root);


/* ------------------------------------------------------
 * Representa a estutura de dados de cada nó da arvore
 * ------------------------------------------------------
 */
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
int getIndex(char c);


/* --------------------------------------------------
 * Insere um caractere em um nó específico da árvore
 * --------------------------------------------------
 */
struct Node* insertAt(char c, struct Node* node);


/* ------------------------------------------------
 * Retorna se um caractere está presente no conjunto
 * válido de entradas da árvore: "[A-Z|a-z|-]*"
 * ------------------------------------------------
 */
bool isValidToken(char c);



/* ------------------------------------------------
 * Insere um novo caractere na árvore. Quando um caractere
 * não presente no alfabeto é recebido, a palavra é finalizada
 * ------------------------------------------------
 */
void insert(char c, struct Node* root);



/* ------------------------------------------------
 * Concatena um caractere com uma string
 * ------------------------------------------------
 */
char * char_concat(char* string, char c);



/* ------------------------------------------------
 * Calcula todas as permutações de nós de uma
 * árvore ou sub árvore junto da frequência
 * ------------------------------------------------
 */
struct ListEntry* getCombinations(struct Node* node, char * prefix);



/* ------------------------------------------------
 * Busca por um termo na árvore.
 * Busca por um determinado nó e retorna sua permutação de filhos
 * ------------------------------------------------
 */
struct ListEntry* find(char* input, struct Node* root);



