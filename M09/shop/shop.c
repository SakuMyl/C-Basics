#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "shop.h"


int write_binary(const char* filename, const Product* shop)
{
	FILE *f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    int ret = 0;
    while (!ret && shop->name[0] != 0) {
        if (fwrite(shop, sizeof(Product), 1, f) != 1) ret = 1;
        shop++;
    }
    fclose(f);
    return ret;
}

Product* read_binary(const char* filename)
{
    FILE *f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Error opening file\n");
        return NULL;
    }
    Product *products = malloc(sizeof(Product));
    if (!products) {
        fprintf(stderr, "Error allocating memory\n");
        fclose(f);
        return NULL;
    }
    int i = 1;
    while (fread(products + i - 1, sizeof(Product), 1, f) == 1) {
        i++;
        products = realloc(products, i * sizeof(Product));
        if (!products) {
            fprintf(stderr, "Error reallocating memory\n");
            fclose(f);
            return NULL;
        }
    }
    products[i - 1].name[0] = 0;
    if (ferror(f)) {
        fprintf(stderr, "Error reading file: %s\n", strerror(ferror(f)));
        fclose(f);
        free(products);
        return NULL;
    }
    fclose(f);
    return products;
}

int write_plaintext(const char* filename, const Product* shop)
{
	FILE *f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    while (shop->name[0] != 0) {
        if (fprintf(f, "%s %f %d\n", shop->name, shop->price, shop->in_stock) < 3) {
            fprintf(stderr, "Error writing to file: %s\n", strerror(ferror(f)));
            fclose(f);
            return 1;
        }
        shop++;
    }
    fclose(f);
    return 0;
}

Product* read_plaintext(const char* filename)
{
	FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error opening file\n");
        return NULL;
    }
    Product *products = malloc(sizeof(Product));
    if (!products) {
        fprintf(stderr, "Error allocating memory\n");
        fclose(f);
        return NULL;
    }
    Product p;
    int i = 1;
    while (fscanf(f, "%s %f %d\n", p.name, &p.price, &p.in_stock) == 3) {
        products[i - 1] = p;
        i++;
        Product *ptr = products;
        products = realloc(products, i * sizeof(Product));
        if (!products) {
            free(ptr);
            fprintf(stderr, "Error reallocating memory");
            fclose(f);
            return NULL;
        }
    }
    if (ferror(f)) {
        fprintf(stderr, "Error reading file: %s\n", strerror(ferror(f)));
        free(products);
        fclose(f);
        return NULL;
    }
    products[i - 1] = p;
    products[i - 1].name[0] = 0;
    fclose(f);
    return products;
}
