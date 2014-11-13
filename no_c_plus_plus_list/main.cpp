#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hash.h"
#include "fileworking.h"
int main()
{
    hashTable hash1;
    hashTable hash2;
    hashTable hash3;
    hashTable hash4;
    hashTable hash5;
    hashTableConstructor(&hash1);
    hashTableConstructor(&hash2);
    hashTableConstructor(&hash3);
    hashTableConstructor(&hash4);
    hashTableConstructor(&hash5);
    char* book = NULL;
    long bookLen = -1;
    const char* filename = "book.txt";
    read_file(filename, &book, &bookLen);
    char* stringsInBook = NULL;
    int quantityString  = -1;
    stringsInBook = searchAllStr(book, bookLen, &quantityString);
    for(long i = 0; i < quantityString; i++ )
    {
        addNewInHash(hashFunc1(&stringsInBook[i], &hash1), &stringsInBook[i], &hash1);
        addNewInHash(hashFunc2(&stringsInBook[i], &hash2), &stringsInBook[i], &hash2);
        addNewInHash(hashFunc3(&stringsInBook[i], &hash3), &stringsInBook[i], &hash3);
        addNewInHash(hashFunc4(&stringsInBook[i], &hash4), &stringsInBook[i], &hash4);
        addNewInHash(hashFunc5(&stringsInBook[i], &hash5), &stringsInBook[i], &hash5);
    }
    //hashDump(&hash5);
    const char* outputfile = "exel.csv";

    FILE* output = fopen(outputfile, "wr");

    for(long i = 0; i < hash1.quantityElements; i++)
    {
        fprintf(output, "%d,", hash1.table[i].quantityElements);
    }
    fprintf(output, "\n");
    for(long i = 0; i < hash2.quantityElements; i++)
    {
        fprintf(output, "%d,", hash2.table[i].quantityElements);
    }
    fprintf(output, "\n");
    for(long i = 0; i < hash3.quantityElements; i++)
    {
        fprintf(output, "%d,", hash3.table[i].quantityElements);
    }
    fprintf(output, "\n");
    for(long i = 0; i < hash4.quantityElements; i++)
    {
        fprintf(output, "%d,", hash4.table[i].quantityElements);
    }
    fprintf(output, "\n");
    for(long i = 0; i < hash5.quantityElements; i++)
    {
        fprintf(output, "%d,", hash5.table[i].quantityElements);
    }
    return 0;
}