/*
* File: wf.c
* Author: Steve Prisco
* Description: This file is to be compiled with hashTableA6.c. This file contains the code to take user-input, and the code to 'clean' the input.
*              This calls functions from hashTableA6.c to add words to a hash table.
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "hashTableA6.h"

int main(int argc, char *argv[]) // main function, takes in user-specified files and calls respective hashTableA6.c functions to put all files' words into a hash table
{
 if (argc < 2)
 {
  fprintf(stderr,"ERROR: no file(s) given - exiting\n");
  exit(1);
 }

 int i = 1, j = 0, k = 0, l = 0, used = 0; // i probably don't need this many counters...
 FILE *fp;
 char tempWord[1024], word[1024];

 hashTableStructure *myHashTable;
 myHashTable = createHashTable();

 while (i < argc)
 {
  fp = fopen(argv[i], "r");
  
  if (!fp)
  {
   fprintf(stderr,"ERROR: unable to open file %s - exiting\n", argv[i]);
   exit(1);
  }

  while (l < 1024)
   {
    tempWord[l] = '\0';
    word[l] = '\0';
    l++;
   }

  while (fscanf(fp, " %s", tempWord) >= 1)
  {
   j = 0;
   k = 0;
  
   while (tempWord[j]) // BEGIN 'CLEANING' THE WORD - only sends letters and numbers off to hash table, does not send blanks
   {
    if (isalpha(tempWord[j]))
    {
     if (isupper(tempWord[j]))
     {
      tempWord[j] = tolower(tempWord[j]);
     }
   
     word[k] = tempWord[j];
     used++;
     k++;
    }else if (isdigit(tempWord[j]))
    {
     word[k] = tempWord[j];
     used++;
     k++;
    }

    j++;
   } // END 'CLEANING' THE WORD
   
   if (used > 0)
   {
    insert(myHashTable, word);
   }
   
   used = 0;
   l = 0;
   while (tempWord[l])
   {
    tempWord[l] = '\0';
    word[l] = '\0';
    l++;
   }
  }
 
  i++;
  fclose(fp);
 }

 toFile(myHashTable);
 deallocateTable(myHashTable);

 return 0;
}
