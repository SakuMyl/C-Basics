#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filebasics.h"


/* Print give file <filename> to the standard output stream.
 * Return number of characters printed, -1 if file opening fails.
 */
int print_file_and_count(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    char buf[100];
    int n = 0;
    while(fgets(buf, sizeof(buf), f) != NULL) {
        printf("%s", buf);
        n += strlen(buf);
    }
    if (ferror(f)) {
        fclose(f);
        return -1;
    }
    fclose(f);
    return n;
}

/* Compare two files. The function should return the first lines that differ
 * in the two files, concatenated together, separated by four dashes, on
 * different lines. If the files are equal, NULL is returned. 
 * Function stops immediately, if either one of the files end and returns NULL.
 * You can assume that lines are not longer than 1000 characters.
 */
char *difference(const char *file1, const char *file2)
{
    const int MAXLINE = 1000;
    FILE *f1 = fopen(file1, "r");
    if (!f1) return NULL;
    FILE *f2 = fopen(file2, "r");
    if (!f2) {
        fclose(f1);
        return NULL;
    }
    char buf1[MAXLINE];
    char buf2[MAXLINE];
    const char *diff = "----\n";
    while (fgets(buf1, MAXLINE, f1) != NULL && fgets(buf2, MAXLINE, f2) != NULL) {
        if (strcmp(buf1, buf2) != 0) {
            fclose(f1);
            fclose(f2);
            size_t len1 = strlen(buf1);
            size_t len2 = strlen(buf2);
            char *ret = malloc(len1 + len2 + strlen(diff) + 1);
            if (!ret) {
                return NULL;
            }
            strcpy(ret, buf1);
            strcpy(ret + len1, diff);
            strcpy(ret + len1 + strlen(diff), buf2);
            return ret;
        }
    }
    fclose(f1);
    fclose(f2);
    return NULL;
}


