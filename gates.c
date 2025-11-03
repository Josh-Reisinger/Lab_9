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

int AND_N(int *slice_a, int *slice_b, int n) {
    for (int i = 0; i < n/2; i++) {
        if (slice_a[i] == 0 || slice_b[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int OR_N(int *slice_a, int *slice_b, int n) {
    for (int i = 0; i < n/2; i++) {
        if (slice_a[i] == 1 || slice_b[i] == 1) {
            return 1;
        }
    }
    return 0;
}