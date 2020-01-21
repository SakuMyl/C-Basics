#include "source.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void ascii_chart(char min, char max)
{
    int column = 1;
    for(int i = min; i <= max; ++i) {
        printf("%3d ", i);
        printf("0x%02x ", i);
        int printable = isprint(i);
        if(printable)
            printf("%c", i);
        else
            printf("?");
        if(column == 4) {
            printf("\n");
            column = 1;
        }
        else {
            printf("\t");
            column++;
        }
    }
}
