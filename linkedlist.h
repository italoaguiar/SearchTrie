/* ------------------------------------------------------------
 * Representa a estrutura de dados da lista encadeada
 * ------------------------------------------------------------
 */
struct ListEntry{
    char * content;
    int frequence;
    struct ListEntry* next;
};



/* -------------------------------------------------------------
 * Insere um novo elemento no come�o da lista encadeada
 * -------------------------------------------------------------
 */
struct ListEntry* insertEntry(char* value, int frequence, struct ListEntry* lst);



/* -------------------------------------------------------------
 * Imprime os elementos da lista encadeada
 * -------------------------------------------------------------
 */
printList(struct ListEntry* lst);



/* -------------------------------------------------------------
 * Imprime os elementos da lista encadeada e os desaloca da mem�ria
 * -------------------------------------------------------------
 */
printListAndFree(struct ListEntry* lst);
