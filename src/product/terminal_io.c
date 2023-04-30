#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "terminal_io.h"

#define MAX_STRLEN 80

static bool MenuPrinting = true;

static const char* MenuStrings[] = {
    "Allocate mMemory",
    "Free memory",
    "Show lists",
    "Show/hide menu",
    "Quit",
};
static const size_t NrMenuStrings =
            sizeof(MenuStrings) / sizeof(MenuStrings[0]);

int GetInt(const char* message)
{
    char line[MAX_STRLEN];
    char* result = NULL;
    int value = -1;

    if (MenuPrinting)
    {
        printf("%s", message);
    }
    result = fgets(line, sizeof(line), stdin);
    if (result != NULL)
    {
        sscanf(result, "%d", &value);
    }

    return value;
}

int GetLimitedInt(const char* message, const char* items[], int nrItems)
{
    int choice = -1;
    do
    {
        if (items != NULL && MenuPrinting)
        {
            for (int i = 1; i <= nrItems; i++)
            {
                printf("  [%d] %s\n", i, items[i-1]);
            }
        }
        choice = GetInt(message);
    } while (choice <= 0 || choice > nrItems);

    return choice;
}

MenuOptions GetMenuChoice()
{
    if (MenuPrinting)
    {
        printf("\n\nMENU\n====\n");
    }

    return (MenuOptions)GetLimitedInt("choice: ", MenuStrings, NrMenuStrings);
}

void ToggleMenuPrinting()
{
    MenuPrinting = !MenuPrinting;
    if (!MenuPrinting)
    {
        printf("printing of MENU is diabled\n");
    }
}

void PrintProgramHeader()
{
    printf("PRC 'MemoryC' (version 5)\n"
           "-------------------------\n");
}
