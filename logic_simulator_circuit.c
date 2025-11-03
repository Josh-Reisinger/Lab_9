//
// Created by jlr on 10/10/2025.
//

/*
 *  DISABLED
 *

#include <stdio.h>
#include "gates.h"

int circuit1(int a, int b);
int circuit2(int a, int b);

int main() {

    int a, b;
    printf("\nPlease enter a boolean value for a and b:");
    scanf("%d %d", &a, &b);

    //Check for boolean value
    if ( a < 0 || b < 0  || a > 1 || b > 1 ) {
        printf("\nInvalid input\n");
        return 0;
    }

    printf("\nCircuit 1: %d\nCircuit 2: %d\n\n", circuit1(a,b), circuit2(a,b));
    return 0;
}

int circuit1(int a, int b) {
    return OR(AND(a,b), AND(NOT(a),NOT(b)));
}
int circuit2(int a, int b) {
    return OR(AND(NOT(a),b), AND(a,NOT(b)));
}

*/
