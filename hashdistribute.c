#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OUT_FILE "hashdistribute.txt"
#define DICT_FILE "./dictionary/words.txt"
#define MAX_LAST_NAME_SIZE 16

unsigned int HASH_SIZE=0x7FF;

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131;
    unsigned int hash = 0;
    while(*str)
        hash = hash * seed +(*str++);

    return (hash & HASH_SIZE);
}

unsigned int APHash(char *str)
{
    unsigned int hash = 0;
    int i;
    for (i=0; *str; i++) {
        if ((i & 1) == 0)
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        else
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
    }
    return (hash & HASH_SIZE);
}

unsigned int DJB2Hash(char *str)
{
    unsigned int hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return (hash & HASH_SIZE );
}

unsigned int ELFHash(char *str)
{
    unsigned int hash = 0;
    unsigned int x    = 0;

    while (*str) {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }

    return (hash & HASH_SIZE);
}

unsigned int hash(char str[])
{
    //return BKDRHash(str);
    //return APHash(str);
    //return DJB2Hash(str);
    return ELFHash(str);
}


int main(int argc,char *argv[])
{
    if(argc > 1)
        HASH_SIZE = (unsigned int)atoi(argv[1]);

    printf("HASH_SIZE = %u\n",HASH_SIZE);
    int hash_value[HASH_SIZE+1],i=0,count=0;
    for(i=0; i<HASH_SIZE+1; i++)
        hash_value[i] = 0;

    double standard=0.0;
    char str[MAX_LAST_NAME_SIZE];
    FILE *fp = fopen(DICT_FILE,"r");
    if(fp==NULL) {
        printf("cannot open the file\n");
        return -1;
    }
    i=0;
    while(fgets(str,sizeof(str),fp)) {
        while(str[i] != '\0')
            i++;
        str[i-1] = '\0';
        i = 0;
        hash_value[hash(str)]++;
        count ++;
    }
    fclose(fp);

    fp = fopen(OUT_FILE,"w");
    if(fp==NULL) {
        printf("cannot open the file\n");
        return -1;
    }
    double average = ((double)count)/((double)(HASH_SIZE+1));
    for(i=0; i<HASH_SIZE+1; i++) {
        fprintf(fp,"%d %d\n",i,hash_value[i]);
        standard += ((double)hash_value[i]-average)*((double)hash_value[i]-average);
    }
    fclose(fp);
    standard = standard / (double)(HASH_SIZE+1);
    standard = sqrt(standard);
    printf("total numbers of string = %d,Standard deviation = %lf,coefficient of variation = %lf\n",count,standard,standard / average);

    return 0;
}
