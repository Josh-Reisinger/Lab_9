//
// Created by jlr on 10/9/2025.
//
// This header file declares the logic gates functions.

#ifndef GATES_H
#define GATES_H

// Function prototypes
int NOT(int a);
int AND(int a, int b);
int OR(int a, int b);
int NAND(int a, int b);
int NOR(int a, int b);
int XOR(int a, int b);
int XNOR(int a, int b);
int AND_N(int *values, int n);
int OR_N(int *values, int n);

#endif //GATES_H