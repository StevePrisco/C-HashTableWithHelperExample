/*
* File: hashTableA6.c
* Author: Steve Prisco
* Description: Hash table designed for use with a6
* A LOT OF INTERNET SOURCES WERE USED WHEN DESIGNING THIS. SparkNotes, TutorialsPoint, and a few YouTube videos
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

hashTableStructure *createHashTable() // creates a hash table with a size of 1000
{
 hashTableStructure *newTable;
 int i = 0;

 if ((newTable = malloc(sizeof(hashTableStructure))) == NULL)
 {
   fprintf(stderr,"ERROR: cannot allocate memory - exiting\n");
   exit(1);
 }

 if ((newTable->table = malloc(sizeof(list *) * 1000)) == NULL)
 {
  fprintf(stderr,"ERROR: cannot allocate memory - exiting\n");
  exit(1);
 }

 for(i = 0; i < 1000; i++) newTable->table[i] = NULL;
 newTable->size = 1000;

 return newTable;
}

int hash(hashTableStructure *hashtable, char *word) // function used to find hash values for strings
{
 int key = 0, i;
 int len = strlen(word);
 
 for (i = 0; i < len; i++) // apparently this is a fairly common method of hashing? taken from various internet sources
 {
  key += word[i];
 }

 key %= 1000; // key values will be between 0 - 999
 return key;
}

list *find(hashTableStructure *hashtable, char *str) // attempts find a string in the hash table, returns NULL if string cannot be found
{
 list *list;
 int hashVal = hash(hashtable, str);

 for(list = hashtable->table[hashVal]; list != NULL; list = list->next)
 {
  if (strcmp(str, list->str) == 0)
  {
   return list;
  }
 }
    
 return NULL;
}

int insert(hashTableStructure *hashtable, char *str) // attempts to insert string into the hash table, will update timesRead variable if string already exists
{
 list *tempList;
 list *currentList;
 int hashVal = hash(hashtable, str);

 currentList = find(hashtable, str);
   
 if (currentList != NULL) // if the word is already in the table
 {
  currentList->timesRead += 1;
  return 0;
 }
    
 if ((tempList = malloc(sizeof(list))) == NULL)
 {
  fprintf(stderr,"ERROR: cannot allocate memory - exiting\n");
  exit(1);
 }  
 
 tempList->str = strdup(str);  // creating list data
 tempList->timesRead = 1;
 tempList->next = hashtable->table[hashVal];
 hashtable->table[hashVal] = tempList;

 return 0;
}

void deallocateTable(hashTableStructure *hashtable) // deallocates entire table
{
 int i;
 list *list, *temp;

 if (!hashtable)
 {
  return;
 }

 for (i = 0; i < hashtable->size; i++)
 {
  list = hashtable->table[i];
  while(list)
  {
   temp = list;
   list = list->next;
   free(temp->str);
   free(temp);
  }
 }

 free(hashtable->table);
 free(hashtable);
}

void toFile(hashTableStructure * hashtable) //puts content of table into a file
{
 int i;
 list *list, *temp;

 FILE *fp;

 fp = fopen("wordfrequency.txt", "w");

 if (!fp)
 {
  fp = fopen("wordfrequency.txt", "ab+");
 }

 for (i = 0; i < hashtable->size; i++)
 {
  list = hashtable->table[i];

  while (list)
  {
   temp = list;
   list = list->next;
   fprintf(fp, "%s, %d\n", temp->str, temp->timesRead);
  }
 }

 fclose(fp);
}

/*
                               //           MAIN FUNCTION USED FOR TESTING
int main(void)
{
 hashTableStructure *myHashTable;
 myHashTable = createHashTable();

 char *names[15] = {"John", "Timmy", "Allison", "Yamamoto", "Flooby Dooby Jakoobi", "Frank", "Jane", "Crawling in my skin", "Fluttershy", "Spongebob", "Spongebob", "Spongebob", "Crawling in my skin", "Crawling in my skin", "Allison"};

 int i;

 for (i = 0; i < 15; i++)
 {
  insert(myHashTable, names[i]);
 }

 toFile(myHashTable);
 deallocateTable(myHashTable);

 return 0;
}

*/
