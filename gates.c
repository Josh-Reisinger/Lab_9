//
// Created by jlr on 10/9/2025.
//
// This file contains the logic gates

#include "gates.h"
#include <stdio.h>

int NOT(int a) {
    return !a;
}

int AND(int a, int b) {
    return a && b;
}

int OR(int a, int b) {
    return a || b;
}

int NAND(int a, int b) {
    return !(a && b);
}

int NOR(int a, int b) {
    return !(a || b);
}

int XOR(int a, int b) {
    return a ^ b;
}

int XNOR(int a, int b) {
    return !(a ^ b);
}

// Updated for Milestone 4
int AND_N(int *values, int n) {
    for (int i = 0; i < n; i++) {
        if (values[i] == 0) {
            return 0; // If any input is 0, the result is 0
        }
    }
    return 1; // All inputs were 1
}

// Updated for Milestone 4
int OR_N(int *values, int n) {
    for (int i = 0; i < n; i++) {
        if (values[i] == 1) {
            return 1; // If any input is 1, the result is 1
        }
    }
    return 0; // All inputs were 0
}