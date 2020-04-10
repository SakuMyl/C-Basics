#include <stdlib.h>
#include <string.h>
#include "source.h"

int* join_arrays(unsigned int n1, const int *a1,
		 unsigned int n2, const int *a2,
		 unsigned int n3, const int *a3)
{
    int *ret = malloc((n1 + n2 + n3) * sizeof(int));
    if (ret == NULL) return NULL;
    int *ptr = ret;
    memcpy(ptr, a1, n1 * sizeof(int));
    ptr += n1;
    memcpy(ptr, a2, n2 * sizeof(int));
    ptr += n2;
    memcpy(ptr, a3, n3 * sizeof(int));
    return ret;
}
