#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

#ifndef hash_table
entry_hash hash_table[HASH_SIZE];
#endif

entry *findName(char lastName[], entry *pHead)
{
    pHead = hash_table[hash(lastName)].pHead;
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
    if(t->pHead == NULL) {
        t->pHead = (entry *) malloc(sizeof(entry));
        t->pHead->pNext = (entry *) malloc(sizeof(entry));
        t->pTail = t->pHead->pNext;
        strcpy(t->pTail->lastName,lastName);
        t->pTail->pNext = NULL;
    } else {
        t->pTail->pNext = (entry *) malloc(sizeof(entry));
        t->pTail = t->pTail->pNext;
        strcpy(t->pTail->lastName,lastName);
        t->pTail->pNext = NULL;
    }

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
