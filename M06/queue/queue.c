#include "queue.h"
#include <stdlib.h>
#include <string.h>

int enqueue(struct studentqueue *q, const char *name)
{
    struct studentqueue *current = q;
    while (current->next) {
        current = current->next;
    };
    struct studentqueue *new_student = malloc(sizeof(struct studentqueue));
    if (!new_student) return 0;
    new_student->name = malloc(strlen(name) + 1);
    if (!new_student->name) {
        free(new_student);
        return 0;
    }
    strcpy(new_student->name, name);
    new_student->next = NULL;
    current->next = new_student;
    return 1;
}

int dequeue(struct studentqueue *q, char *buffer, unsigned int size)
{
    if (!q->next) return 0;
    strncpy(buffer, q->next->name, size - 1);
    struct studentqueue *first = q->next;
    q->next = first->next;
    free(first->name);
    free(first);
    return 1;
}
