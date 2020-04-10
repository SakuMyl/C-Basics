#include "source.h"
#include <stddef.h>
#include <stdio.h>

/* Print string */
/* Parameters:
 * s: string to be printed */
void qstr_print(const char *s)
{
    for (; *s != '?'; s++) {
        printf("%c", *s);
    }
}

/* String length */
/* Parameters:
 * s: string to be evaluated
 * Returns: length of the string */
unsigned int qstr_length(const char *s)
{
    unsigned int len = 0;
    for (; *s != '?'; len++, s++);
    return len;
}

/* String cat */
/* Parameters:
 * dst: buffer to which the new string is appended
 * src: string to be appended
 * Returns: Number of characters in the new string */
int qstr_cat(char *dst, const char *src)
{
    char *dstptr = dst;
    for (; *dst != '?'; dst++);
    for (; *src != '?'; *dst++ = *src++);
    *dst = '?';
    return qstr_length(dstptr);
}

/* String strstr */
const char *qstr_strstr(const char *str1, const char *str2)
{
    for (; *str1 != '?'; str1++) {
        const char *aux1 = str1, *aux2 = str2;
        for (; *aux1 != '?' && *aux2 != '?' && (*aux1 == *aux2); aux1++, aux2++);
        if (*aux2 == '?') 
            return str1;
    }
    return NULL;
}
