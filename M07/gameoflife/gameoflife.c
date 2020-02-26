#include "gameoflife.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Exercise a: Allocates needed memory for the GameArea structure and
 * the actual game area. 'x_size' and 'y_size' indicate the horizontal and
 * vertical dimensions of the GameArea.
 * 
 * Returns: pointer to the GameArea structure allocated by this function.
 */
GameArea *createGameArea(unsigned int x_size, unsigned int y_size)
{
    CellStatus **cells = malloc(y_size * sizeof(CellStatus *));
    if (!cells) return NULL;
    GameArea *ret = malloc(sizeof(GameArea)); 
    if (!ret) {
        free(cells);
        return NULL;
    }
    ret->x_size = x_size;
    ret->y_size = y_size;
    ret->cells = cells;

    for (unsigned int i = 0; i < y_size; i++) {
        cells[i] = malloc(x_size * sizeof(CellStatus));
        if (!cells[i]) {
            for (unsigned int j = 0; j < i; j++) {
                free(cells[j]);
            }
            free(cells);
            free(ret);
            return NULL;
        }
        for (unsigned int j = 0; j < x_size; j++) {
            cells[i][j] = DEAD;
        }
    }
    return ret;
}

/* Free memory allocated for GameArea <a>.
 */
void releaseGameArea(GameArea *a)
{
    for (unsigned int i = 0; i < a->y_size; i++) {
        free(a->cells[i]);
    }
    free(a->cells);
    free(a);
}

/* Exercise b: Initialize game GameArea by setting exactly <n> cells into
 * ALIVE CellStatus in the game GameArea <a>.
 */
void initGameArea(GameArea *a, unsigned int n)
{
    srand(time(NULL));
    unsigned int size = a->y_size * a->x_size;
    unsigned int indices[size];
    for (unsigned int i = 0; i < size; i++) {
        indices[i] = i;
    }
    for (unsigned int i = 0; i < size; i++) {
        unsigned int index = rand() % (size - i) + i;
        unsigned int temp = indices[index];
        indices[index] = indices[i];
        indices[i] = temp;
    }
    unsigned int until = (n > size) ? size : n;
    for (unsigned int i = 0; i < until; i++) {
        unsigned int index = indices[i];
        a->cells[index / a->x_size][index % a->x_size] = ALIVE;
    }
}

/* Exercise c: Output the current CellStatus of GameArea <a>.
 */
void printGameArea(const GameArea *a)
{
    for (unsigned int i = 0; i < a->y_size; i++) {
        for (unsigned int j = 0; j < a->x_size; j++) {
            char c = (a->cells[i][j] == ALIVE) ? '*' : '.';
            printf("%c", c);
        }
        printf("\n");
    }
}

/* Calculates number of live neighbours around position (x,y),
 * and returns the count.
 */
unsigned int live_neighbours(const GameArea *a, unsigned int x, unsigned int y)
{
    unsigned int count = 0;
    unsigned int i = 0;
    if (y > 0) i = y - 1;
    unsigned int j = 0;
    if (x > 0) j = x - 1;
    for (; i <= y + 1; i++) {
        for (; j <= x + 1; j++) {
            if (i < a->y_size && j < a->x_size && i != y && j != x && a->cells[i][j] == ALIVE) {
                count++;
            }
        }
    }
    return count;
}

/* Exercise d: Advance GameArea <a> by one generation.
 */
void gameTick(GameArea *a)
{
    GameArea *copied_area = createGameArea(a->x_size, a->y_size);
    if (!copied_area) return;
    for (unsigned int i = 0; i < a->y_size; i++) {
        for (unsigned int j = 0; j < a->x_size; j++) {
            copied_area->cells[i][j] = a->cells[i][j];
        }
    }
    for (unsigned int i = 0; i < a->y_size; i++) {
        for (unsigned int j = 0; j < a->x_size; j++) {
            unsigned int n = live_neighbours(copied_area, j, i);
            CellStatus status = copied_area->cells[i][j];
            CellStatus new_status = DEAD;
            if ((status == ALIVE && (n == 2 || n == 3)) || 
                (status == DEAD && n == 3)) {
                new_status = ALIVE;
            }
            a->cells[i][j] = new_status;
        }
    }
    releaseGameArea(copied_area);
}
