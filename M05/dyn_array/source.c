#include <stdio.h>
#include <stdlib.h>
#include "source.h"


/* Dynamic Array Reader */
/* Parameters:
 * n: Number of values to be read
 * 
 * Returns: pointer to the dynamically allocated array
 */
int *create_dyn_array(unsigned int n)
{
    int *p = malloc(n * sizeof(int));
    if(!p) return NULL;
    for (unsigned int i = 0; i < n; i++) {
        int res = scanf("%d", p + i);
        if (res != 1) {
            printf("Not an integer");
        }
    }
    return p;
}

/* Add to array */
/* Parameters:
 * arr: Existing array of integers
 * num: number of integers in the array before the call
 * newval: new value to be added
 * 
 * Returns: pointer to the allocated array
 */
int *add_dyn_array(int *arr, unsigned int num, int newval)
{
    int *new_arr = realloc(arr, (num + 1) * sizeof(int));
    if(!new_arr) {
        return NULL;
    }
    new_arr[num] = newval;
    return new_arr;
}
