#include "source.h"

#include <stdio.h>
#include <math.h>

void simple_multiply()
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d * %d = %d\n", a, b, a * b);
}

void simple_math()
{
    float a, b;
    char c;
    int ret = scanf("%f %c %f", &a, &c, &b);
    if(ret == 3 && (c == '+' || c == '-' || c == '*' || c == '/')) {
        float result;
        if(c == '+')
            result = a + b;
        else if(c == '-')
            result = a - b;
        else if(c == '*')
            result = a * b;
        else
            result = a / b;
        
        printf("%.1f\n", result); 
    }
    else {
        printf("ERR\n");
    }
}    
