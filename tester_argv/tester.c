#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_stack *initialize_stack(void) {
    t_stack *newStack = malloc(sizeof(t_stack));
    if (newStack == NULL) {
        // Handle memory allocation failure if necessary
        return NULL;
    }
    newStack->head = NULL; // Initially, the stack is empty
    return newStack;
}

t_node *createNode(long data) {
    t_node *newNode = (t_node *)malloc(sizeof(t_node));
    if (newNode == NULL) {
        // Memory allocation failed
        return NULL;
    }
    newNode->data = data; // Set the node's data
    newNode->next = NULL; // Next is NULL for now, will be set during push
    newNode->prev = NULL; // Prev is NULL for now, will be set during push if necessary
    return newNode;
}

// Function to push a new number onto the stack
void push_to_stack(t_stack **stack, long data) {
    if (stack == NULL) return; // Check if the stack pointer is valid

    t_node *newNode = createNode(data);
    if (newNode == NULL) {
        // Handle memory allocation failure if necessary
        return;
    }

    if ((*stack)->head == NULL) {
        // The stack is empty, so this node becomes the head
        (*stack)->head = newNode;
        newNode->next = newNode; // Point to itself, assuming a circular structure
        newNode->prev = newNode; // Point to itself, assuming a circular structure
    } else {
        // The stack is not empty, insert the node at the beginning
        newNode->next = (*stack)->head; // New node points to the current head
        newNode->prev = (*stack)->head->prev; // New node's prev points to what was the last node
        (*stack)->head->prev->next = newNode; // The last node's next points to the new node
        (*stack)->head->prev = newNode; // The current head's prev points to the new node
        (*stack)->head = newNode; // Update the head to be the new node
    }
}

void apply_operation(const char *op, t_stack **a, t_stack **b) {
    if (strcmp(op, "sa") == 0) sa(*a);
    else if (strcmp(op, "sb") == 0) sb(*b);
    else if (strcmp(op, "ss") == 0) ss(*a, *b);
    else if (strcmp(op, "pa") == 0) pa(a, b);
    else if (strcmp(op, "pb") == 0) pb(a, b);
    else if (strcmp(op, "ra") == 0) ra(*a);
    else if (strcmp(op, "rb") == 0) rb(*b);
    else if (strcmp(op, "rr") == 0) rr(*a, *b);
    else if (strcmp(op, "rra") == 0) rra(*a);
    else if (strcmp(op, "rrb") == 0) rrb(*b);
    else if (strcmp(op, "rrr") == 0) rrr(*a, *b);
}

void print_stack(t_stack *stack) {
    t_node *current = stack->head;
    if (current == NULL) {
        printf("Stack is empty\n");
        return;
    }
    do {
        printf("%ld ", current->data);
        current = current->next;
    } while (current != stack->head);
    printf("\n");
}

int main(int argc, char **argv) {
    t_stack *a = initialize_stack();
    t_stack *b = initialize_stack();

    // Example to add elements to stack A
    // Note: This section might need adjustment if you also want to pass these initial values via argv
    push_to_stack(&a, 8);
    push_to_stack(&a, 5);
    push_to_stack(&a, 6);
    push_to_stack(&a, 3);
    push_to_stack(&a, 1);
    push_to_stack(&a, 2);

    printf("Initial state of stack A:\n");
    display_col(a);
    printf("Initial state of stack B:\n");
    display_col(b);

    // Start processing operations from argv starting from index 1
    for (int i = 1; i < argc; i++) {
        apply_operation(argv[i], &a, &b);
        printf("After operation %s, stack A: ", argv[i]);
        display_col(a);
        printf("After operation %s, stack B: ", argv[i]);
        display_col(b);
    }

    printf("Final state of stack A:\n");
    display_col(a);
    printf("Final state of stack B:\n");
    display_col(b);

    // Free memory
    free_stack(a);
    free_stack(b);

    return 0;
}