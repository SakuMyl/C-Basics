#include "hexread.h"
#include <stdio.h>
#include <stdint.h>

/* Prints the given file as hexdump, at most 16 numbers per line.
 * <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int file_to_hex(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) return -1;
    int line_length = 16;
    uint8_t buf[line_length];
    void *ptr = buf;
    int n, i = 0;
    while ((n = fread(ptr, 1, line_length, f))) {
        if (n != line_length && ferror(f)) return -1;
        for (int i = 0; i < n; i++) {
            printf("%02x ", buf[i]);
        }
        if (!feof(f)) printf("\n");
        i += n;
    }
    return i;
}
