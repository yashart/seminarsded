#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "list.h"

struct hashTable
{
    int quantityElements;
    listHeader* table;
};

errors hashTableConstructor(hashTable* hash);

int hashFunc1(listData data, hashTable* hash);

int hashFunc2(listData data, hashTable *hash);

int hashFunc3(listData data, hashTable *hash);

int hashFunc4(listData data, hashTable* hash);

int hashFunc5(listData data, hashTable* hash);

errors addNewInHash(int pos, listData data, hashTable* hash);

void hashDump(hashTable* hash);

#endif