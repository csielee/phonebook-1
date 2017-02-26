#include <stdio.h>
#include <stdlib.h>

#define MAX_LAST_NAME_SIZE 16

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
    struct __PHONE_BOOK_ENTRY *pNext;
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY_DATA data;
} entry;

unsigned long int struct_size=32;
int count=1;
void append(entry *pHead)
{
    entry *tmp=pHead;

    for(int i=0; i<350000; i++) {
        tmp->pNext = (entry *)malloc(struct_size);
        tmp = tmp->pNext;
        tmp->pNext = NULL;
    }
}
void find(entry *pHead)
{
    entry *tmp = pHead;
    while(tmp!=NULL) {
        tmp->lastName[0]='a';
        tmp->lastName[1]='\0';
        tmp = tmp->pNext;
    }
}


int main(int argc, char *argv[])
{
    sscanf(argv[1],"%d",&count);
    sscanf(argv[2],"%ld",&struct_size);
    printf("count=%d,entry size=%ldbytes\n",count,struct_size);
    entry *pHead;
    pHead =(entry *) malloc(struct_size);
    printf("pHead=%ldbytes\n",sizeof(*pHead));

    append(pHead);

    while(count!=0) {
        find(pHead);
        count--;
    }


    return 0;
}
