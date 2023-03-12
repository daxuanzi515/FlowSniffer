#include "try.h"
void Try::command(char *str)
{
    char com[50];
    strcpy(com, str);
    system(com);
}
