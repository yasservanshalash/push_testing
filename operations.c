#include "push_swap.h"

int swap(t_stack *stack) {
    t_node *first;
    t_node *second;
    long tmp_value; // Assuming data holds a value like 'long' for the swap; adjust type as needed
    int tmp_index; // Assuming an 'index' field exists and is relevant; adjust type as needed

    // Check if there are at least two nodes in the stack
    if (stack == NULL || stack->head == NULL || stack->head->next == stack->head) {
        // Not enough nodes to swap, or invalid stack
        return (-1);
    }

    first = stack->head;
    second = first->next;

    // Swap 'value' and 'index' between the first two nodes
    tmp_value = first->data; // Adjust 'data' to 'value' if your node structure uses 'value'
    tmp_index = first->index; // Assuming an 'index' exists

    first->data = second->data; // Adjust 'data' to 'value' if your node structure uses 'value'
    first->index = second->index;

    second->data = tmp_value; // Adjust 'data' to 'value' if your node structure uses 'value'
    second->index = tmp_index;

    return (0);
}



void sa(t_stack *stack) {
    swap(stack);
    write(1, "sa\n", 3);
}

void sb(t_stack *stack) {
    swap(stack);
    write(1, "sb\n", 3);
}

void ss(t_stack *stack_a, t_stack *stack_b) {
    swap(stack_a);
    swap(stack_b);
    write(1, "ss\n", 3);
}

void push_to(t_stack **dest, t_stack **src) {
    if (!src || !(*src)->head) return; // Ensure src is not empty

    t_node *node = (*src)->head; // Node to move from src
    // Remove node from src
    if (node->next == node) { // If only one element
        (*src)->head = NULL;
    } else {
        (*src)->head = node->next;
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }
    node->next = node->prev = node; // Isolate node
    
    // Add node to dest
    if (!(*dest)->head) { // If dest is empty
        (*dest)->head = node;
    } else {
        node->next = (*dest)->head;
        node->prev = (*dest)->head->prev;
        (*dest)->head->prev->next = node;
        (*dest)->head->prev = node;
    }
}

void pa(t_stack **a, t_stack **b) {
    push_to(a, b); // Take the first element at the top of B and put it at the top of A
    write(1, "pa\n", 3);
}

void pb(t_stack **a, t_stack **b) {
    push_to(b, a); // Take the first element at the top of A and put it at the top of B
    write(1, "pb\n", 3);
}


void rotate(t_stack *stack) {
    if (stack && stack->head && stack->head->next != stack->head) {
        stack->head = stack->head->next; // Move head to the next element
    }
}

void ra(t_stack *stack) {
    rotate(stack);
    write(1, "ra\n", 3);
}

void rb(t_stack *stack) {
    rotate(stack);
    write(1, "rb\n", 3);
}


void rr(t_stack *a, t_stack *b) {
    rotate(a);
    rotate(b);
    write(1, "rr\n", 3);
}

void reverse_rotate(t_stack *stack) {
    if (stack && stack->head && stack->head->next != stack->head) {
        stack->head = stack->head->prev; // Move head to the previous element
    }
}

void rra(t_stack *stack) {
    reverse_rotate(stack); // rrb is identical to rra, but operates on stack b
    write(1, "rra\n", 4);
}

void rrb(t_stack *stack) {
    reverse_rotate(stack); // rrb is identical to rra, but operates on stack b
    write(1, "rrb\n", 4);
}


void rrr(t_stack *a, t_stack *b) {
    reverse_rotate(a);
    reverse_rotate(b);
    write(1, "rrr\n", 4);
}