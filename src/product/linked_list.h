#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

typedef struct linkedList LinkedList;

LinkedList* InitialiseLinkedList(size_t unitSize);
void DestroyLinkedList(LinkedList** thisListPtr);

int LinkedListAddTail(LinkedList* thisList, void* data);
int LinkedListAddAt(LinkedList* thisList, size_t index, void* data);
int LinkedListAddAfterLastAccessed(LinkedList* thisList, void* data);

void* LinkedListGetHead(LinkedList* thisList);
void* LinkedListGetNext(LinkedList* thisList);

size_t LinkedListGetLength(LinkedList* thisList);

int LinkedListRemoveTail(LinkedList* thisList);
int LinkedListRemoveAt(LinkedList* thisList, size_t index);
int LinkedListRemove(LinkedList* thisList, void *data);
int LinkedListRemoveAll(LinkedList* thisList);


#endif