//
// Created by jlr on 10/17/2025.
//

/*
 *  DISABLED
 *

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gates.h"
#define SIZE 16


int main() {
    int a[SIZE], b[SIZE];
    int menu;
    // Seed the random number generator
    srand(time(NULL));

    printf("Enter 1 for random values\nEnter 2 for user-input values:\n");
    if (scanf("%d", &menu) != 1) {
        printf("Wrong input\n");
        return 1;
    }

    switch (menu) {
        case 1:
            printf("Random Values are:\n   a b\n");
            for (int i = 0; i < SIZE; i++) {
                // Get a random boolean value
                a[i] = rand() % 2;
                b[i] = rand() % 2;
                printf("%d: %d %d\n", i+1, a[i], b[i]);
            }
            break;

        case 2:
            if(SIZE == 8)
                printf("\n                                     . . . . . . . .");
            else
                printf("\n                                      . . . . . . . . . . . . . . . .");
            printf("\nPlease enter %d boolean values for a: ", SIZE);
            for (int i = 0; i < SIZE; i++) {
                if (scanf("%d", &a[i]) != 1) {
                    printf("Invalid input.\n");
                    return 1;
                }
            }
            if(SIZE == 8)
                printf("\n                                     . . . . . . . .");
            else
                printf("\n                                      . . . . . . . . . . . . . . . .");
            printf("\nPlease enter %d boolean values for b: ", SIZE);
            for (int i = 0; i < SIZE; i++) {
                if (scanf("%d", &b[i]) != 1) {
                    printf("Invalid input.\n");
                    return 1;
                }
            }

            // Check for boolean value
            for (int i = 0; i < SIZE; i++) {
                if (a[i] < 0 || a[i] > 1 || b[i] < 0 || b[i] > 1 ) {
                    printf("\nError: All inputs must be 0 or 1.\n");
                    return 1;
                }
            }
            break;

        default:
            printf("Invalid menu option.\n");
            return 1;
    }

    if(SIZE == 8) {
        int circuit1 = NOT(XNOR(AND_N(&a[0], &b[0], SIZE),OR_N(&a[4],&b[4], SIZE)));
        printf("\nYou are simulating Circuit 1\nResult: %d\n\n", circuit1);
    } else if (SIZE == 16) {
        int circuit2 = OR(OR(AND_N(&a[12], &b[0], SIZE), OR_N(&a[8], &b[4], SIZE)), AND(OR_N(&a[4], &b[8], SIZE), AND_N(&a[0], &b[12], SIZE)));
        printf("\nYou are simulating Circuit 2\nResult: %d\n\n", circuit2);
    } else {
        printf("Invalid number for SIZE\n");
        return 1;
    }

    return 0;

}

*/