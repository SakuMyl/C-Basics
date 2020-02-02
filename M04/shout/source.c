#include "source.h"
#include <ctype.h>

char *my_toupper(char *dest, const char *src)
{
    int cursor = 0;
	while (*src != '\0') {
        if (*src == '?') {
            dest[cursor] = '!';
            cursor++;
        }
        else if (*src == '.') {
            for (int i = 0; i < 3; i++) {
                dest[cursor + i] = '!';
            }
            cursor += 3;
        }
        else {
            dest[cursor] = toupper(*src);
            cursor++;
        }
        src++;
    }
    dest[cursor] = 0;
    return dest;
}
