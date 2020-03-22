#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int myprint(char *str, ...)
{
    va_list args;
    int count = 0;
    va_start(args, str);
    while (*str) {
        if (*str != '&') {
            fputc(*str, stdout);
        }
        else {
            count++;
            printf("%d", va_arg(args, int));
        }
        str++;
    }
    va_end(args);
    return count;
}
