#include "memory.h"
#include "terminal_io.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    const int MemorySize = 100;

    MenuOptions choice = MO_ALLOCATE_MEMORY;
    
    PrintProgramHeader();

    if (argc != 1)
    {
        fprintf(stderr, "%s: argc=%d\n", argv[0], argc);
    }

    /* initialisate van lijsten dus freeList bevat alle geheugen en allocList is
     * leeg */
    ConstructMemory(MemorySize);

    while (choice != MO_QUIT)
    {
        choice = GetMenuChoice();

        switch (choice)
        {
        case MO_ALLOCATE_MEMORY:
        {
            int nrofBytes = GetInt("Give nr of bytes: ");
            int addr = ClaimMemory(nrofBytes);
            if (addr == -1)
            {
                printf("[ALLOC] not enough memory for %d byte\n", nrofBytes);
            }
            else
            {
                printf("[ALLOC] address: %4d (%d byte)\n", addr, nrofBytes);
            }
        }
        break;
        case MO_FREE_MEMORY:
        {
            int addr = GetInt("Give address to be freed: ");
            int nrofBytes = FreeMemory(addr);
            if (nrofBytes == -1)
            {
                printf("[FREE]  address: %4d was not allocated\n", addr);
            }
            else
            {
                printf("[FREE]  address: %4d (%d byte)\n", addr, nrofBytes);
            }
        }
        break;
        case MO_SHOW_LISTS:
        {
            PrintList(stdout);
        }
        break;
        case MO_SHOW_HIDE_MENU:
            ToggleMenuPrinting();
            break;
        case MO_QUIT:
            // nothing to do here
            break;
        default:
            printf("invalid choice: %d\n", choice);
            break;
        }
    }

    /* opruimen van de lijsten */
    DestructMemory();

    return 0;
}
