typedef struct list
{
 char *str;
 int timesRead;
 struct list *next;
} list;

typedef struct hashTableStructure
{
 int size;
 list **table;
} hashTableStructure;

hashTableStructure *createHashTable();
int hash(hashTableStructure *hashtable, char *word);
int insert(hashTableStructure *hashtable, char *str);
void deallocateTable(hashTableStructure *hashtable);
void toFile(hashTableStructure * hashtable);
