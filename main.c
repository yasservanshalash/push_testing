#include "push_swap.h"

void printArray(long *array, int size);
int findMaxBits(t_stack *stack); // Finds the max number of bits among all numbers in the stack
int lstsize(t_stack *stack); // Returns the number of elements in the stack
int isEmpty(t_stack *stack); // Checks if the stack is empty
void pb(t_stack **a, t_stack **b); // Push top element of A to B
void pa(t_stack **a, t_stack **b); // Push top element of B to A
void ra(t_stack *a); // Rotate all elements of A up by 1
void bitwiseSort(t_stack **a, t_stack **b);
void correctOrder(t_stack **a, t_stack **b, int maxBits);
int isSortedAscending(t_stack *stack);

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
    // display(a);
    // display(b);
    if (!isSortedAscending(a)) {
        bitwiseSort(&a, &b);
        // Any additional sorting or order correction logic here...
    }

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

void bitwiseSort(t_stack **a, t_stack **b) {
    int maxBits = findMaxBits(*a);

    while(!isSortedAscending(*a))
    {
    for (int bit = 0; bit < maxBits; bit++) {
        int size = lstsize(*a);
        for (int i = 0; i < size; i++) {
            t_node *node = (*a)->head; // Fetch the current head
            if (((node->data >> bit) & 1) == 1) {
                pb(a, b); // Execute pb if the bit is 1
            } else {
                ra(*a); // Execute ra to move to the next node
            }
        }
        while (!isEmpty(*b)) {
            pa(a, b);
        }
    }
    }
}



void correctOrder(t_stack **a, t_stack **b, int maxBits) {
    // After sorting, all elements are in reverse order in stack A.
    // Push all elements to B, then back to A to reverse the order.
    while (!isEmpty(*a)) {
        pb(a, b);
    }
    while (!isEmpty(*b)) {
        pa(a, b);
    }
}


// Function to find the maximum number of bits required to represent any number in the stack
int findMaxBits(t_stack *stack) {
    if (isEmpty(stack)) {
        return 0;
    }

    long maxVal = LONG_MIN;
    t_node *current = stack->head;
    do {
        if (current->data > maxVal) {
            maxVal = current->data;
        }
        current = current->next;
    } while (current != stack->head);

    int maxBits = 0;
    while (maxVal != 0) {
        maxBits++;
        maxVal >>= 1; // Right-shift the value
    }

    return maxBits;
}

// Function to determine the size of the stack
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