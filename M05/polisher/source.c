#include <stdlib.h>
#include "source.h"

/* Remove C comments from the program stored in memory block <input>.
 * Returns pointer to code after removal of comments.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *delete_comments(char *input)
{
    int input_size = 1;
    char *ptr = input;
    for (; *ptr; ptr++, input_size++);
    char *buf = malloc(input_size);
    if (buf == NULL) return NULL;
    int i = 0;
    ptr = input;
    while (*ptr) {
        if (*ptr == '/' && *(ptr + 1) == '/') {
            for (; *ptr && *ptr != '\n'; ptr++);
            ptr++;
        }
        else if(*ptr == '/' && *(ptr + 1) == '*') {
            for (; *ptr && !(*ptr == '*' && *(ptr + 1) == '/'); ptr++);
            ptr += 2;
        }
        else {
            buf[i] = *ptr;
            i++;
            ptr++;
        }
    }
    buf[i] = 0;
    char * new_buf = realloc(buf, i + 1);
    if (new_buf == NULL) {
        return NULL;
    }
    free(input);
    return new_buf;
}
