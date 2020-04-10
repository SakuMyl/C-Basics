#include "book.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int init_book(struct book *p_book, const char *p_id, const char *p_title, const char * p_author, struct date release)
{
	if (strlen(p_id) > 9) {
        return 0;
    }
    char *new_title = malloc(strlen(p_title) + 1);
    if (new_title == NULL) {
        return 0;
    }
    char *new_author = malloc(strlen(p_author) + 1);
    if (new_author == NULL) {
        free(new_title);
        return 0;
    }
    p_book->title = new_title;
    p_book->author = new_author;
    strcpy(p_book->id, p_id);
    strcpy(p_book->title, p_title);
    strcpy(p_book->author, p_author);
    p_book->release_date = release;
    return 1;
}

struct book *add_to_collection(struct book *collection, unsigned int size, struct book new_book)
{
	struct book *new_collection = realloc(collection, (size + 1) * sizeof(struct book));
    if (new_collection == NULL) {
        return NULL;
    }
    struct book *book = malloc(sizeof(struct book));
    if (!book) {
        free(new_collection);
        return NULL;
    }
    if(!init_book(book, new_book.id, new_book.title, new_book.author, new_book.release_date)) {
        free(new_collection);
        free(book);
        return NULL;
    }
    new_collection[size] = *book;
    free(book);
    return new_collection;
}
