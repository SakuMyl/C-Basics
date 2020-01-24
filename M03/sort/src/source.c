
#include "source.h"


/* Selection sort */
/* Parameters:
 * start: start of an array
 * size: length of an array
 */
void swap(int *array, int a, int b)
{
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

int partition(int *array, int lo, int hi)
{
    int pivot = array[hi];
    int i = lo;
    for (int j = lo; j <= hi; j++) {
        if (array[j] < pivot) {
            swap(array, i, j);
            i++;
        }
    }
    swap(array, i, hi);
    return i;
}

void quicksort(int *array, int lo, int hi)
{
    if (lo < hi) {
        int p = partition(array, lo, hi);
        quicksort(array, lo, p - 1);
        quicksort(array, p + 1, hi);
    }    
}

void sort(int *start, int size)
{
    quicksort(start, 0, size - 1);
}
