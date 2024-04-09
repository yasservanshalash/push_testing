#include "push_swap.h"

void printArray(long *array, int size);
int findMaxBits(t_stack *stack); // Finds the max number of bits among all numbers in the stack
int lstsize(t_stack *stack); // Returns the number of elements in the stack
int isEmpty(t_stack *stack); // Checks if the stack is empty

int findMaxBits(t_stack *stack) {
    int maxBits = 0;
    t_node *current = stack->head;
    long maxValue = 0;
    // Find the max value in the stack
    while (current != NULL) {
        if (current->data > maxValue) maxValue = current->data;
        current = current->next;
        if (current == stack->head) break; // Assuming circular linked list
    }
    // Calculate max bits needed for the max value
    while (maxValue) {
        maxValue >>= 1;
        maxBits++;
    }
    return maxBits;
}

int isBitSet(int number, int bit) {
    return (number >> bit) & 1;
}

void sortStackA(t_stack **a, t_stack **b) {
    int maxBits = findMaxBits(*a);
    for (int bit = 0; bit < maxBits; bit++) {
        int size = lstsize(*a);
        for (int i = 0; i < size; i++) {
            // Assuming the top node is accessed directly from the stack's head
            if (isBitSet((*a)->head->data, bit) == 0) {
                pb(a, b);
            } else {
                ra(*a);
            }
        }
        while (!isEmpty(*b)) {
            pa(a, b);
        }
    }
}


void sortStack(t_stack **a, t_stack **b) {
    int maxBits = findMaxBits(*a);
    for (int bit = 0; bit < maxBits; bit++) {
        int size = lstsize(*a);
        for (int i = 0; i < size; i++) {
            if (isBitSet((*a)->head->data, bit) == 1) {
                pb(a, b);
            } else {
                ra(*a);
            }
        }

        // Move elements back from B to A, ensuring those with bit 0 are now at the bottom
        while (!isEmpty(*b)) {
            pa(a, b);
        }
    }
    // After the final iteration, stack A will be sorted in ascending order.
}

void reverseStackOrder(t_stack **a, t_stack **b) {
    // Move all elements from A to B, reversing their order
    while (!isEmpty(*a)) {
        pb(a, b);
    }
    
    // Move all elements back from B to A, maintaining the reversed order
    while (!isEmpty(*b)) {
        pa(a, b);
    }
}

int	main(int argc, char **argv)
{
	long	*numbers_array;
	int		size;
	t_stack	*a;
	t_stack	*b;

	numbers_array = return_numbers(argc, argv, &size);
	a = array_to_stack(numbers_array, size);
	b = (t_stack *)malloc(sizeof(t_stack));
    b->head = NULL;
    sortStack(&a,&b);
    display(a);
	free(numbers_array);
	free_stack(a);
	free(b);
	return (0);
}

void printArray(long *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%ld ", array[i]);
    }
    printf("\n");
}

int lstsize(t_stack *stack) {
    if (isEmpty(stack)) {
        return 0;
    }

    int count = 0;
    t_node *current = stack->head;
    do {
        count++;
        current = current->next;
    } while (current != stack->head);

    return count;
}

// Function to check if the stack is empty
int isEmpty(t_stack *stack) {
    return (stack == NULL || stack->head == NULL);
}

// Function to check if the stack is sorted in ascending order
int isSortedAscending(t_stack *stack) {
    if (stack == NULL || stack->head == NULL || stack->head->next == stack->head) {
        return 1; // The list is sorted if it's empty or has one element
    }

    long x = LONG_MIN; // Start with the smallest possible long value
    t_node *current = stack->head;

    do {
        if (current->data < x) {
            // If any node's data is smaller than the previous node's data, the list is not sorted
            return 0; // The list is not sorted
        }
        x = current->data; // Update x to the current node's data
        current = current->next; // Move to the next node
    } while (current != stack->head); // Continue until we've looped back to the start

    return 1; // The list is sorted
}
