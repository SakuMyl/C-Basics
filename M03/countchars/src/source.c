#include <stdio.h>

unsigned int arraylen(const char *array)
{
    int i = 0;
    while (array[i] != 0) i++;
    return i;    
}

void countchars(const char *array, unsigned int *counts)
{
    for (int i = 0; i < 255; i++) counts[i] = 0;
    unsigned int n = arraylen(array);
    for (int i = 0; i < n; i++) {
        int j = array[i];
        counts[j]++;
    }
}




