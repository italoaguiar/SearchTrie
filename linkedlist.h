
struct ListEntry{
    char * content;
    int frequence;
    struct ListEntry* next;
};

struct ListEntry* insertEntry(char* value, int frequence, struct ListEntry* lst);


printList(struct ListEntry* lst);
