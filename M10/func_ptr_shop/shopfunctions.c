#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shopfunctions.h"

int compareAlpha(const void* a, const void* b)
{
    Product *a_p = (Product *)a;
    Product *b_p = (Product *)b;
	return strcmp(a_p->name, b_p->name);
}

int compareNum(const void* a, const void* b)
{
    Product *a_p = (Product *)a;
    Product *b_p = (Product *)b;
	int ret = b_p->in_stock - a_p->in_stock;
    if (ret != 0) return ret;
    else return compareAlpha(a, b);
}

const Product* findProduct(const Product* p_array, const char* search_key, int (*cmp)(const void*, const void*))
{
    int i = 0;
    const Product *ptr = p_array;
    while (ptr[i].name[0]) i++;
    Product p;
    strcpy(p.name, search_key);
	return bsearch(&p, p_array, i, sizeof(Product), cmp);
}

