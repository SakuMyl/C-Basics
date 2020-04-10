#include "stringsplit.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>


/* Split string by another string, return split parts + NULL in array.
 *
 * Parameters: 
 *  str: the string to split
 *  split: the string to split str with
 *
 * Returns:
 *  A dynamically reserved array of dynamically reserved string parts.
 *
 * For example called with "Test string split" and " ",
 * returns ["Test", "string", "split", NULL].
 * Or called with "Another - test" and " - ",
 * returns ["Another", "test", NULL].
 */

char** split_string(const char *str, const char* split) {
    //First find the number of splits to avoid reallocations
    int split_count = 1;
    int split_len = strlen(split);
    const char *ptr = strstr(str, split);
    for (; ptr; split_count++) {
        ptr = strstr(ptr + split_len, split);
    }
    //Initialise the array according to how many splits were found
    char **arr = malloc(sizeof(char *) * (split_count + 1));
    if (!arr) return NULL;
    //Last element should be NULL
    arr[split_count] = NULL;

    ptr = str;
    const char *next_ptr = strstr(str, split);

    for (int i = 0; i < split_count; i++) {
        int size = 0;
        if (next_ptr) size = next_ptr - ptr;
        else for (; ptr[size]; size++);
        arr[i] = malloc(sizeof(char) * (size + 1));
        if (!arr[i]) {
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
        }
        memcpy(arr[i], ptr, size);
        arr[i][size] = 0;
        if (next_ptr) {
            ptr = next_ptr + split_len;
            next_ptr = strstr(next_ptr + split_len, split);
        }
    }
    return arr;
}

void print_split_string(char **split_string) {
    for (; *split_string; split_string++) {
        printf("%s\n", *split_string);
    }
}

void free_split_string(char **split_string) {
    char **ptr = split_string;
    for (; *ptr; ptr++) {
        free(*ptr);
    }
    free(split_string);
}



