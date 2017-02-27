#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define HASH_SIZE 0x7FF

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 1
typedef struct __PHONE_BOOK_ENTRY_DATA {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} entryData;
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY_DATA *data;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;
typedef struct __ENTRY_HASH {
    entry *pHead;
    entry *pTail;
} entry_hash;
entry_hash hash_table[HASH_SIZE];

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);
unsigned int hash(char str[]);


#define MEMORYPOOL
#define POOL_SIZE 1000

typedef struct __MEMORYPOOL_HANDLE {
    void *ptr;
} mpHandle;

#endif
