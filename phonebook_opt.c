#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

#ifndef hash_table
entry_hash hash_table[HASH_SIZE];
#endif

int entry_memory_count=POOL_SIZE;
entry *entry_memorypool;

void *getEntry()
{
    if(entry_memory_count==POOL_SIZE) {
        printf("get pool\n");
        entry_memorypool = (entry *)malloc(sizeof(entry)*POOL_SIZE);
        entry_memory_count=0;
    }
    //entry *e = entry_memorypool+sizeof(entry)*entry_memory_count;
    void *a = &entry_memorypool[entry_memory_count];
    printf("%d,%lx\n",entry_memory_count,(unsigned long int)a);
    entry_memory_count++;
    return a;
}

entry *findName(char lastName[], entry *pHead)
{
    pHead = hash_table[hash(lastName)].pHead->pNext;
    while(pHead!=NULL) {
        if(strcasecmp(pHead->lastName,lastName)==0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    entry_hash *t = &hash_table[hash(lastName)];
    if(t->pHead == NULL || t->pTail==NULL) {
        t->pHead = (entry *) malloc(sizeof(entry));
        //t->pHead->pNext = (entry *) malloc(sizeof(entry));
        t->pHead->pNext = (entry *) getEntry();
        t->pTail = t->pHead->pNext;
    } else {
        //t->pTail->pNext = (entry *) malloc(sizeof(entry));
        t->pTail->pNext = (entry *) getEntry();
        t->pTail = t->pTail->pNext;
    }
    strcpy(t->pTail->lastName,lastName);
    t->pTail->pNext = NULL;
    return e;
}

unsigned int BKDRHash(char *str)
{
    unsigned int seed=131;
    unsigned int hash=0;
    while(*str)
        hash = hash * seed +(*str++);

    return (hash & HASH_SIZE);
}
unsigned int hash(char str[])
{
    return BKDRHash(str);
}
