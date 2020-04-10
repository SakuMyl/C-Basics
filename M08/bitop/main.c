#include <stdio.h>
#include "bits.h"

/* Feel free to modify this function to test different things */

int main(void) {

    /* op_bit_set tests */
    printf("\n*** Testing your op_bit_set function..\n");
    unsigned char arr[2] = {0, 0};

    printf("At first arr[0] == 0x%02X and arr[1] == 0x%02X\n", arr[0], arr[1]);
    // Afterwards should be: arr[0] is 0x80, arr[1] is 0.
    printf("Setting bit 0\n");
    op_bit_set(arr, 0);
    printf("arr[0] is 0x%02X, should be 0x80\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    // Afterwards should be: arr[0] is 0x80+0x40 (0xC0), arr[1] is 0.
    printf("Setting bit 1\n");
    op_bit_set(arr, 1);
    printf("arr[0] is 0x%02X, should be 0x80+0x40 == 0xC0\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    // Afterwards should be: arr[0] is 0xC0+0x10 (0xD0), arr[1] is 0.
    printf("Setting bit 3\n");
    op_bit_set(arr, 3);
    printf("arr[0] is 0x%02X, should be 0xC0+0x10 == 0xD0\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    // Afterwards should be: arr[0] is 0xD0, arr[1] is 0x40.
    printf("Setting bit 9\n");
    op_bit_set(arr, 9);
    printf("arr[0] is 0x%02X, should be 0xC0+0x10 == 0xD0\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x40\n", arr[1]);


    
    /* for practice: make your own op_bit_unset tests here */
    printf("\n*** Testing your op_bit_unset function..\n");

    printf("At first arr[0] == 0x%02X and arr[1] == 0x%02X\n", arr[0], arr[1]);
    
    printf("Unsetting bit 9\n");
    op_bit_unset(arr, 9);
    printf("arr[0] is 0x%02X, should be 0xD0\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    printf("Unsetting bit 3\n");
    op_bit_unset(arr, 3);
    printf("arr[0] is 0x%02X, should be 0xD0-0x10 == 0xC0\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    printf("Unsetting bit 1\n");
    op_bit_unset(arr, 1);
    printf("arr[0] is 0x%02X, should be 0xC0-0x40 == 0x80\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    printf("Unsetting bit 0\n");
    op_bit_unset(arr, 0);
    printf("arr[0] is 0x%02X, should be 0x00\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);


    /* op_bit_get tests */
    printf("\n*** Testing your op_bit_get function..\n");
    printf("Setting bits 0, 1, 3 and 9\n");
    op_bit_set(arr, 0);
    op_bit_set(arr, 1);
    op_bit_set(arr, 3);
    op_bit_set(arr, 9);
    printf("Bit number 0 is %d, should be 1\n", op_bit_get(arr,0));
    printf("Bit number 1 is %d, should be 1\n", op_bit_get(arr,1));
    printf("Bit number 3 is %d, should be 1\n", op_bit_get(arr,3));
    printf("Bit number 9 is %d, should be 1\n", op_bit_get(arr,9));
    printf("Bit number 2 is %d, should be 0\n", op_bit_get(arr,2));
    printf("Bit number 12 is %d, should be 0\n", op_bit_get(arr,12));

    /* op_print_byte tests */
    printf("\n*** Testing your op_print_byte function..\n");
    unsigned char b = 0x80;
    printf("Printing out 10000000, got ");
    op_print_byte(b); // This should print out 10000000
    printf("\n");

    b = 0xFF;
    printf("Printing out 11111111, got ");
    op_print_byte(b); // This should print out 11111111
    printf("\n");
    
    /* op_bit_get_sequence tests */
    printf("\n*** Testing your op_bit_get_sequence function..\n");

    printf("Getting sequence... Should be 0x68, was 0x%02X\n", op_bit_get_sequence(arr, 0, 7));

    return 0;
}
