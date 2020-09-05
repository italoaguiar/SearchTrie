#include <stdbool.h>


//define o tamanho do alfabeto
#define ALFABET_SIZE 53

/* ------------------------------------------------
 * Gera o n� raiz da �rvore
 * ------------------------------------------------
 */
struct Node* createRoot();


/* ------------------------------------------------
 * Efetua a abertura de um arquivo e o carrega na �rvore
 * ------------------------------------------------
 */
void loadFile(char* file, struct Node* root);


/* ------------------------------------------------------
 * Representa a estutura de dados de cada n� da arvore
 * ------------------------------------------------------
 */
struct Node {
    int frequence;
    char* value;
    struct Node* childs[ALFABET_SIZE];
};


/* ------------------------------------------------
 * Converte o �ndice da tabela ASCII para
 * um �ndice do array de entradas da �rvore
 * ------------------------------------------------
 */
int getIndex(char c);


/* ------------------------------------------------
 * Converte o �ndice da entrada na �rvore para
 * um caractere da tabela ASCII
 * ------------------------------------------------
 */
char getChar(int index);


/* --------------------------------------------------
 * Insere um caractere em um n� espec�fico da �rvore
 * --------------------------------------------------
 */
struct Node* insertAt(char c, struct Node* node);


/* ------------------------------------------------
 * Retorna se um caractere est� presente no conjunto
 * v�lido de entradas da �rvore: "[A-Z|a-z|-]*"
 * ------------------------------------------------
 */
bool isValidToken(char c);



/* ------------------------------------------------
 * Insere um novo caractere na �rvore. Quando um caractere
 * n�o presente no alfabeto � recebido, a palavra � finalizada
 * ------------------------------------------------
 */
void insert(char c, struct Node* root);



/* ------------------------------------------------
 * Concatena um caractere com uma string
 * ------------------------------------------------
 */
char * char_concat(char* string, char c);



/* ------------------------------------------------
 * Calcula todas as permuta��es de n�s de uma
 * �rvore ou sub �rvore junto da frequ�ncia
 * ------------------------------------------------
 */
struct ListEntry* getCombinations(struct Node* node, char * prefix);


/* -------------------------------------------------
 * Comprime a �rvore removendo n�s com um �nico filho
 * e adicionando seus valores aos n�s pais
 * -------------------------------------------------
 */
void compressTree(struct Node* node);


/* ------------------------------------------------
 * Busca por um termo na �rvore.
 * Busca por um determinado n� e retorna sua permuta��o de filhos
 * ------------------------------------------------
 */
struct ListEntry* find(char* input, struct Node* root);


/* -----------------------------------------------
 * Calcula o n�mero de n�s da �rvore
 * -----------------------------------------------
 */
int count(struct Node* node);



