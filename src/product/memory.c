#include "linked_list.h"
#include "memory.h"

static const int startAddress = 1000;

LinkedList* freeList;
LinkedList* allocList;

typedef struct memoryBlock MemoryBlock;
struct memoryBlock
{
   int address;
   int size;
};

static MemoryBlock MakeMemoryBlock(int address, int size);
static int DecideBlockAddressAndAddMemoryBlock(int nrOfBytes);
static int DetermineFreeSizeAndFreeMemory(int addr);

/* function: ConstructMemory
 * pre: -
 * post: memory administration is constructed
 */
void ConstructMemory(int size)
{
    freeList = InitialiseLinkedList(sizeof(MemoryBlock));
    allocList = InitialiseLinkedList(sizeof(MemoryBlock));

    MemoryBlock firstfreeElement = MakeMemoryBlock(startAddress, size);
    LinkedListAddAt(freeList, 0, &firstfreeElement);
}

/* function: DestructMemory
 * pre: -
 * post: memory administration is destructed
 */
void DestructMemory()
{
    DestroyLinkedList(&freeList);
    DestroyLinkedList(&allocList);
}


/* function: PrintList
 * pre: -
 * post: if stream is valid, list information is printed to stream and 0 is returned
 *       if stream is NULL, -1 is returned
 */
int PrintList(FILE* stream)
{
    if (stream == NULL) 
    {
        return -1;
    }

    size_t freeListLength = LinkedListGetLength(freeList);
    size_t allocListLength = LinkedListGetLength(allocList);

    MemoryBlock* currentFreeBlock = LinkedListGetHead(freeList);
    MemoryBlock* currentAllocBlock = LinkedListGetHead(allocList);

    printf("FreeList:\n");
    printf("---------\n");

    if (freeListLength == 0)
    {
        printf("  <empty>\n");
    }
    else
    {
        for(size_t i = 0; i < freeListLength; i++)
        {
            printf("%3ld:  addr:%4d  size:%4d\n", i, currentFreeBlock->address, currentFreeBlock->size);
            currentFreeBlock = (MemoryBlock*)LinkedListGetNext(freeList);
        }
    }

    printf("AllocList:\n");
    printf("----------\n");

    if (allocListLength == 0)
    {
        printf("  <empty>\n");
    }
    else
    {
        for(size_t i = 0; i < allocListLength; i++)
        {
            printf("%3ld:  addr:%4d  size:%4d\n", i, currentAllocBlock->address, currentAllocBlock->size);
            currentAllocBlock = (MemoryBlock*)LinkedListGetNext(allocList);
        }
    }

    return 0;
}

/* function: ClaimMemory
 * pre: nrofBytes > 0
 * post: if no memory block of nrofBytes available return -1
 *       otherwise the first block that is large enough is claimed and the start address is returned
 */
int ClaimMemory(int nrofBytes)
{
    if (nrofBytes < 1) 
    {
        return -1;
    }

    return DecideBlockAddressAndAddMemoryBlock(nrofBytes);
}

/* function: FreeMemory
 * pre: Parameter addr must match the start of an allocatd memory block. Otherwhise return -1.
 * post: Memory is freed and the number of freed bytes is returned
 *
 */
int FreeMemory(int addr)
{

    if (addr < startAddress)
    {
        return -1;
    }

    
    return DetermineFreeSizeAndFreeMemory(addr);
}

static MemoryBlock MakeMemoryBlock(int address, int size)
{
    MemoryBlock newBlock;//= malloc(sizeof(MemoryBlock));

    newBlock.address = address;
    newBlock.size = size;

    return newBlock;
}

static int DecideBlockAddressAndAddMemoryBlock(int nrOfBytes)
{
    int blockStartAddress = -1;

    size_t freeListLength = LinkedListGetLength(freeList);

    MemoryBlock* currentFreeBlock = LinkedListGetHead(freeList);
    MemoryBlock* currentAllocBlock = LinkedListGetHead(allocList);

    if (currentFreeBlock == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < freeListLength; i++)
    {
        if (nrOfBytes <= currentFreeBlock->size)
        {
            blockStartAddress = currentFreeBlock->address;

            MemoryBlock newAllocElement = MakeMemoryBlock(blockStartAddress, nrOfBytes);

            size_t insertPosIndex = 1;

            if (currentAllocBlock != NULL)
            {
                if (blockStartAddress == startAddress)
                {
                    insertPosIndex = 0;
                } 
                else
                {
                    while ((currentAllocBlock->address + currentAllocBlock->size) != blockStartAddress)
                    {
                        currentAllocBlock = LinkedListGetNext(allocList);
                        insertPosIndex++;
                    }
                }
            }

            if (nrOfBytes == currentFreeBlock->size)
            {
                LinkedListRemoveAt(freeList, i);
            } 
            else 
            {
                currentFreeBlock->address += nrOfBytes;
                currentFreeBlock->size -= nrOfBytes;
            }

            LinkedListAddAt(allocList, insertPosIndex, &newAllocElement);

        
            return blockStartAddress;
        }

        currentFreeBlock = (MemoryBlock*)LinkedListGetNext(freeList);
    }
    return -1;
}

static int DetermineFreeSizeAndFreeMemory(int addr)
{
    MemoryBlock* getAllocBlock = LinkedListGetHead(allocList);
    MemoryBlock* currentAllocBlock = NULL;//LinkedListGetHead(allocList);

    size_t allocListLength = LinkedListGetLength(allocList);

    int freeSize = -1;
    int freeAddr = startAddress;
    size_t allocListIndex = 0;

    for (size_t i = 0; i < allocListLength; i++)
    {
        if (getAllocBlock->address == addr)
        {
            currentAllocBlock = getAllocBlock;
            allocListIndex = i;
        }
        getAllocBlock = LinkedListGetNext(allocList);
    }

    if (currentAllocBlock == NULL)
    {
        return -1;
    }
    
    freeSize = currentAllocBlock->size;
    freeAddr = currentAllocBlock->address;

    LinkedListRemoveAt(allocList, allocListIndex);

    size_t freeListLength = LinkedListGetLength(freeList);
    MemoryBlock* currentFreeBlock = LinkedListGetHead(freeList);

    for(size_t i = 0; i < freeListLength; i++)
    {
        
        if (currentFreeBlock->address == (freeAddr + freeSize))
        {
            currentFreeBlock->address = freeAddr;
            currentFreeBlock->size += freeSize;

            return freeSize;
        }

        if ((currentFreeBlock->address + currentFreeBlock->size) == freeAddr)
        {
            currentFreeBlock->size += freeSize;
            MemoryBlock* latterFreeBlock = currentFreeBlock;
            currentFreeBlock = LinkedListGetNext(freeList);

            if (currentFreeBlock->address == (freeAddr + freeSize))
            {

                int newFreeSize = currentFreeBlock->size;
                latterFreeBlock->size += newFreeSize;
                LinkedListRemoveAt(freeList, i+1);
            }
            return freeSize;
        }
        
        currentFreeBlock = LinkedListGetNext(freeList);
    }

    currentFreeBlock = LinkedListGetHead(freeList);
    MemoryBlock newFreeBlock = MakeMemoryBlock(freeAddr, freeSize);

    for(size_t i = 0; i < freeListLength; i++)
    {
        if (freeAddr < currentFreeBlock->address)
        {
            LinkedListAddAt(freeList, i, &newFreeBlock);
            return freeSize;
        }
        currentFreeBlock = LinkedListGetNext(freeList);
    }

    LinkedListAddTail(freeList, &newFreeBlock);
    return freeSize;
}
