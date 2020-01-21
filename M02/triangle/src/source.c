#include <stdio.h>
#include <math.h>
#include "source.h"

void draw_triangle(unsigned int size)
{
    for(int i = 1; i <= size; ++i) {
        for(int j = size; j > i; --j) {
            printf(".");
        }
        for(int j = 0; j < i; ++j) {
            printf("#");    
        }
        printf("\n");
    }
}
