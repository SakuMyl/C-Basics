#include <stdio.h> 
#include <string.h>
#include <ctype.h>
#include "filestats.h"


/* Returns the line count in given file
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * The number of lines in file. */
int line_count(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    //Initialise last to line feed so an empty file has 0 lines
    int n = 0, c = 0, last = '\n';
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') n++;
        last = c;
    }
    //In case the last line didn't end in a line feed
    if (last != '\n') n++;
    if (ferror(f)) {
        fclose(f);
        return -1;
    }
    fclose(f);
    return n;
}


/* Count the number of words in the file. Word has to include at least one
 * alphabetic character, and words are separated by whitespace.
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * number of words in the file */
int word_count(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    int n = 0, c = 0, last = 0, is_word = 0;
    while ((c = fgetc(f)) != EOF) {
        if (isspace(c) && is_word) {
            is_word = 0;
            n++;
        }
        else if (!is_word && isalpha(c)) is_word = 1;
        last = c;
    }
    //If file doesn't end in a space character, take into account the last word
    if (!isspace(last) && is_word) n++;
    if (ferror(f)) {
        fclose(f);
        return -1;
    }
    fclose(f);
    return n;
}
