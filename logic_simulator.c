//
// Created by jlr on 10/9/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gates.h"

//Defines linked list structure
typedef struct Gate {
    int index;
    char type;              // 'I', 'A', 'O', 'X', 'N', 'Q'
    int *inputs;            // Dynamic array of inputs
    int nInputs;            // Count of inputs in array
    int value;              // Computed output value (0 or 1, -1 = uninitialized)
    struct Gate *next;      // Pointer to next gate in list
} Gate;

//Prototypes
void truthTable(int gate);
void logic(int a, int b, int gate);
Gate* readCircuitFile(const char* filename, int* nGates);
void freeCircuit(Gate *head);
void getInputValues(Gate *head);
void evaluateCircuit(Gate *head);
int getGateValue(Gate *head, int index);
void displayOutput(Gate *head);
const char* getGateTypeName(char type);


int main() {
    char filename[256];
    int nGates;

    printf("\nLogic Circuit Simulator\n\n");

    //Gets filename from user
    printf("Enter circuit filename: ");
    if (scanf("%255s", filename) != 1) {
        printf("Error reading file name\n");
        return 1;
    }

    printf("\n");

    //Reads circuit and constructs linked list
    Gate *circuit = readCircuitFile(filename, &nGates);
    if (circuit == NULL) {
        printf("Error: Failed to read circuit file\n");
        return 1;
    }

    printf("Success: read circuit file with %d gates\n\n", nGates);

    //Get input values from user for all input gates
    getInputValues(circuit);

    //Evaluates the circuit
    evaluateCircuit(circuit);

    //Display final output
    printf("\n\nCircuit Output:\n\n");
    displayOutput(circuit);

    printf("\n");

    freeCircuit(circuit);

    return 0;
}

//Reads circuit description from file, makes linked list
Gate* readCircuitFile(const char* filename, int* nGates) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file '%s'\n", filename);
        return NULL;
    }

    if (fscanf(file, "%d", nGates) != 1) {
        printf("Error reading file\n");
        fclose(file);
        return NULL;
    }

    if (*nGates <= 0) {
        printf("Error: invalid number of gates. Must be >0\n");
        fclose(file);
        return NULL;
    }

    fgetc(file); // Get rid of newline left by fscanf

    Gate *head = NULL;
    Gate *tail = NULL;

    //read gates and build linked list
    for (int i = 0; i < *nGates; i++) {
        Gate *newGate = (Gate*)malloc(sizeof(Gate));
        if (newGate == NULL) {
            printf("Error allocating memory\n");
            fclose(file);
            freeCircuit(head);
            return NULL;
        }

        // Init newGate
        newGate->inputs = NULL;
        newGate->nInputs = 0;
        newGate->value = -1;
        newGate->next = NULL;

        char lineBuffer[256];
        if (fgets(lineBuffer, sizeof(lineBuffer), file) == NULL) {
            printf("Error: File ended unexpectedly on line %d\n", i+2);
            free(newGate);
            fclose(file);
            freeCircuit(head);
            return NULL;
        }

        //Parse the line
        char *token = strtok(lineBuffer, " \t:\n");
        if (token == NULL) {
            continue;
        }

        newGate->index = atoi(token);

        token = strtok(NULL, " \t:\n");
        if (token == NULL) {
            continue;
        }

        newGate->type = token[0];

        //Reads all remaining tokens as inputs
        while ((token = strtok(NULL, " \t:\n")) != NULL) {
            int input = atoi(token);
            if (input == 0) {
                continue;
            }
            newGate->nInputs++;

            newGate->inputs = (int*)realloc(newGate->inputs, newGate->nInputs * sizeof(int));
            if (newGate->inputs == NULL) {
                printf("Error allocating memory for inputs\n");
                return NULL;
            }
            newGate->inputs[newGate->nInputs - 1] = input;
        }

        //Confirm gate types
        if (newGate->type != 'I' && newGate->type != 'A' &&
            newGate->type != 'O' && newGate->type != 'X' &&
            newGate->type != 'N' && newGate->type != 'Q')
        {
            printf("Error: Invalid gate type '%c' at gate %d\n", newGate->type, newGate->index);
            free(newGate->inputs);
            free(newGate);
            fclose(file);
            freeCircuit(head);
            return NULL;
        }

        //newGate->value = -1;
        //newGate->next = NULL;

        //Add to linked list (FIFO)
        if (head == NULL) {
            head = tail = newGate;
        } else {
            tail->next = newGate;
            tail = newGate;
        }
    }

    fclose(file);
    return head;
}

//frees all memory allocated for the linked list
void freeCircuit(Gate *head) {
    Gate *current = head;

    while (current != NULL) {
        Gate *temp = current;
        current = current->next;
        free(temp->inputs);
        free(temp);
    }
}

//Gets input values from user
void getInputValues(Gate *head) {
    Gate *current = head;
    int inputCount = 0;

    //Count input gates
    Gate *temp = head;
    while (temp != NULL) {
        if (temp->type == 'I') {
            inputCount++;
        }
        temp = temp->next;
    }
    if (inputCount == 0) {
        printf("Error: No input gate found\n");
        return;
    }

    printf("\nEnter Input Values\nThe circuit has %d input gate(s). Please enter boolean values:\n\n", inputCount);

    while (current != NULL) {
        if (current->type == 'I') {
            int inputValue;
            int validInput = 0;

            while (!validInput) {
                printf("Input gate %d: ", current->index);

                if (scanf("%d", &inputValue) != 1) {
                    printf("Invalid input.\n");
                    //clear input buffer
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    continue;
                }

                //Check for boolean
                if (inputValue == 0 || inputValue == 1) {
                    current->value = inputValue;
                    validInput = 1;
                } else {
                    printf("Invalid input.\n");
                }
            }
        }
        current = current->next;
    }
}

//Evaluates all gates in circuit
void evaluateCircuit(Gate *head) {
    Gate *current = head;

    while (current != NULL) {
        // Skip gates that are already evaluated (like Inputs)
        if (current->value != -1) {
            current = current->next;
            continue;
        }

        switch (current->type) {
            case 'I':
                // Input gate. Value is already set. Do nothing.
                break;

            case 'A':
            case 'O': {
                int *inputValues = (int*)malloc(current->nInputs * sizeof(int));
                // Create temp array to hold values
                if (inputValues == NULL) {
                    printf("Error: Malloc failed in evaluateCircuit\n");
                    current->value = 0;
                    break;
                }

                // Populate array with values
                for (int i = 0; i < current->nInputs; i++) {
                    inputValues[i] = getGateValue(head, current->inputs[i]);
                }

                // Call appropriate gates
                if (current->type == 'A') {
                    current->value = AND_N(inputValues, current->nInputs);
                } else {
                    current->value = OR_N(inputValues, current->nInputs);
                }

                free(inputValues);
            }
                break;

            case 'X': // 2-input XOR (based on M3 and M4 example)
                current->value = XOR(
                    getGateValue(head, current->inputs[0]),
                    getGateValue(head, current->inputs[1])
                );
                break;

            case 'N': // 1-input NOT
                current->value = NOT(getGateValue(head, current->inputs[0]));
                break;

            case 'Q': // 1-input OUTPUT
                current->value = getGateValue(head, current->inputs[0]);
                break;

            default:
                printf("Unknown gate type '%c' at gate %d. Setting value to 0.\n", current->type, current->index);
                current->value = 0;
                break;
        }
        current = current->next;
    }
}

//Finds gate value by index
int getGateValue(Gate *head, int index) {
    //index 0 = unused input
    if (index == 0)
        return 0;

    Gate *current = head;
    while (current != NULL) {
        if (current->index == index) {
            if (current->value == -1) {
                printf("Error: Gate %d hasn't been evaluated yet.\n", index);
                return 0;
            }
            return current->value;
        }
        current = current->next;
    }

    printf("Error: Gate %d not found in circuit", index);
    return 0;
}

//Displays output gate value
void displayOutput(Gate *head) {
    Gate *current = head;
    int output = 0;

    while (current != NULL) {
        if (current->type == 'Q') {
            printf("Gate %d (OUTPUT): %d\n", current->index, current->value);
            output = 1;
        }
        current = current->next;
    }

    if (!output) {
        printf("Error: Gate %d not found in circuit\n", current->index);
    }
}

//Display circuit topology
void displayCircuitStructure(Gate *head) {
    Gate *current = head;

    printf("Circuit Structure:\n");

    while (current != NULL) {
        const char *gateTypeName = getGateTypeName(current->type);
        printf("Gate %d: %-8s", current->index, gateTypeName);

        if (current->type == 'I') {
            printf("[user input]\n");
        } else if (current->nInputs == 0) {
            printf("\n"); // No inputs
        } else {
            printf(" <- gate(s) ");
            for (int i = 0; i < current->nInputs; i++) {
                printf("%d ", current->inputs[i]);
            }
            printf("\n");
        }
        current = current->next;
    }
    printf("\n");
}

//Converts gate letter representations to words
const char* getGateTypeName(char type) {
    switch (type) {
        case 'I': return "INPUT";
        case 'A': return "AND";
        case 'O': return "OR";
        case 'X': return "XOR";
        case 'N': return "NOT";
        case 'Q': return "OUTPUT";
        default: return "UNKNOWN";
    }
}
