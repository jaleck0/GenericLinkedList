#include "linked_list.h"
#include <string.h>

typedef struct element Element;
struct element
{
   void* data;
   Element* next;
};


struct linkedList
{
    Element* head;
    Element* lastAccessed;
    size_t UnitSize;
};

static int DeleteElement(Element** element);

LinkedList* InitialiseLinkedList(size_t unitSize) 
{
    if (unitSize == 0)
    {
        return NULL;
    }

    LinkedList* thisList = malloc(sizeof(LinkedList));
    thisList->head = NULL;
    thisList->lastAccessed = NULL;
    thisList->UnitSize = unitSize;
    return thisList;
}

void DestroyLinkedList(LinkedList** thisListPtr) 
{
    if (thisListPtr != NULL || *thisListPtr != NULL)
    {
        LinkedListRemoveAll(*thisListPtr);
        free(*thisListPtr);
        *thisListPtr = NULL;
    }
}

int LinkedListAddTail(LinkedList* thisList, void* data)
{
    if (thisList == NULL || data == NULL) 
    {
        return -1;
    }

    Element* newElement = malloc(sizeof(Element));
    
    if (newElement == NULL) 
    {
        return -1;
    }

    void* newDataPointer = malloc(thisList->UnitSize);
    
    if (newDataPointer == NULL)
    {
        return -1;
    }

    newElement->data = memcpy(newDataPointer, data, thisList->UnitSize);
    newElement->next = NULL;

    if (thisList->head == NULL) 
    {
        thisList->head=newElement;
    } 
    else 
    {
        Element* tailElement = thisList->head;

        while (tailElement->next != NULL)
        {
            tailElement = tailElement->next;
        }

        tailElement->next = newElement;
    }

    return 0;
}

int LinkedListAddAt(LinkedList* thisList, size_t index, void* data)
{
    if (thisList == NULL || data == NULL) 
    {
        return -1;
    }

    Element* newElement = malloc(sizeof(Element));

    if (newElement == NULL) 
    {
        return -1;
    }

    void* newDataPointer = malloc(thisList->UnitSize);

    if (newDataPointer == NULL)
    {
        return -1;
    }

    newElement->data = memcpy(newDataPointer, data, thisList->UnitSize);
    newElement->next = NULL;

    
    if (thisList->head == NULL) 
    {
        thisList->head=newElement;
    } 
    else if (index == 0) 
    {
        newElement->next = thisList->head;
        thisList->head = newElement;
    } 
    else 
    {
        size_t lookIndex = 0;
        Element* lookElementP = thisList->head;

        while(lookIndex != index-1) 
        {
            lookIndex++;
            if (lookElementP == NULL) 
            {
                return -1;
            }
            lookElementP = lookElementP->next;
        }

        newElement->next = lookElementP->next;
        lookElementP->next = newElement;
    } 

    return 0;
}

int LinkedListAddAfterLastAccessed(LinkedList* thisList, void* data)
{
    if (thisList == NULL || data == NULL) 
    {
        return -1;
    }

    Element* newElement = malloc(sizeof(Element));

    if (newElement == NULL) 
    {
        return -1;
    }

    newElement->data = data;
    newElement->next = NULL;

    if (thisList->head == NULL) 
    {
        thisList->head=newElement;
    } 
    else 
    {
        newElement->next = thisList->lastAccessed->next;
        thisList->lastAccessed->next = newElement;
    }

    return 0;
}

void* LinkedListGetHead(LinkedList* thisList)
{
    thisList->lastAccessed = thisList->head;
    if (thisList->head == NULL)
    {
        return NULL;
    }

    return thisList->head->data;
}

void* LinkedListGetNext(LinkedList* thisList)
{
    if (thisList->lastAccessed == NULL) 
    {
        if (thisList->head == NULL) 
        {
            return NULL;
        }
        thisList->lastAccessed = thisList->head;
    }
    else if (thisList->lastAccessed->next == NULL) 
    {
        thisList->lastAccessed = thisList->head;
    } 
    else 
    {
        thisList->lastAccessed = thisList->lastAccessed->next;
    }
    
    return thisList->lastAccessed->data;
}

size_t LinkedListGetLength(LinkedList* thisList)
{
    if (thisList == NULL) 
    {
        return 0;
    }

    if (thisList->head == NULL){
        return 0;
    }

    Element* lookElement = thisList->head;
    size_t count = 1;

    while(lookElement->next != NULL)
    {
        lookElement = lookElement->next;
        count++;
    }

    return count;
}

int LinkedListRemoveTail(LinkedList* thisList)
{
    if (thisList == NULL) 
    {
        return -1;
    }

    if (thisList->head == NULL)
    {
        return -1;
    }

    Element* currentElement = thisList->head;
    Element* nextElement = currentElement->next;

    if (thisList->head->next == NULL)
    {
        thisList->head = NULL;
        DeleteElement(&currentElement);
        return 0;
    }

    while(nextElement->next != NULL) 
    {  
        currentElement = nextElement;
        nextElement = currentElement->next;
    }

    currentElement->next = NULL;

    DeleteElement(&nextElement);
    return 0;
}

int LinkedListRemoveAt(LinkedList* thisList, size_t index)
{
    if (thisList == NULL) 
    {
        return -1;
    }

    if (thisList->head == NULL)
    {
        return -1;
    }

    if (index == 0) 
    {
        Element* headElement = thisList->head;
        thisList->head = thisList->head->next;
        DeleteElement(&headElement);
    }
    else 
    {
        size_t beforeIndex = 0;
        Element* elementBefore = thisList->head;

        while((beforeIndex) != (index-1)) 
        { 
            beforeIndex++;
            
            if (elementBefore->next == NULL) 
            {
                return -1;
            }
            elementBefore = elementBefore->next;
        }
        Element* elementAfter = elementBefore->next->next;
        
        DeleteElement(&(elementBefore->next));
        elementBefore->next = elementAfter;
        return 0;
    }
    
    return -1;
}

int LinkedListRemove(LinkedList* thisList, void *data)
{
    if (thisList == NULL || data == NULL) 
    {
        return -1;
    }

    Element* element = thisList->head;

    while(element->next != NULL) 
    {
        if (element->data == data) 
        {
            if (element == thisList->head)
            {
                thisList->head = element->next;
            }

            DeleteElement(&element);
    
            return 0;
        }

        element = element->next;
    }
    
    return -1;
}

int LinkedListRemoveAll(LinkedList* thisList)
{
    if (thisList == NULL) 
    {
        return -1;
    }

    while(thisList->head != NULL)
    {
        LinkedListRemoveTail(thisList);
    }

    thisList->head = NULL;
    thisList->lastAccessed = NULL;

    return 0;
}

static int DeleteElement(Element** element)
{
    if (element == NULL || *element == NULL) 
    {
        return -1;
    }

    Element* deleteElement = *element;

    free(deleteElement->data);
    deleteElement->data = NULL;

    free(deleteElement);
    *element = NULL;

    return 0;
}