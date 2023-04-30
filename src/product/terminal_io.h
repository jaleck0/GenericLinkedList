#ifndef TERMINAL_IO_H
#define TERMINAL_IO_H

typedef enum
{
    MO_ALLOCATE_MEMORY = 1,
    MO_FREE_MEMORY,
    MO_SHOW_LISTS,
    MO_SHOW_HIDE_MENU,
    MO_QUIT
} MenuOptions;

int GetInt(const char* message);
int GetLimitedInt(const char* message, const char* items[], int nrItems);
MenuOptions GetMenuChoice();
void ToggleMenuPrinting();
void PrintProgramHeader();

#endif
