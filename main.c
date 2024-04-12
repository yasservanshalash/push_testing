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

// void sortStackAsc(t_stack** a, t_stack** b) {
//     int maxBits = findMaxBits(*a);
//     for (int bit = 0; bit < maxBits; bit++) {
//         int size = lstsize(*a);
//         for (int i = 0; i < size; i++) {
//             int mask = 1 << bit; // Calculate mask for the current bit
//             if (((*a)->head->data & mask) == 0) {
//                 // If the bit is not set, perform action A (rotate)
//                 ra(*a);
//             } else {
//                 // If the bit is set, perform action B (push to B)
//                 pb(a, b);
//             }
//         }

//         // Move elements back from B to A, ensuring those with bit 0 are now at the bottom
//         while (!isEmpty(*b)) {
//             pa(a, b);
//         }
//     }
//     // After the final iteration, stack A will be sorted in ascending order.
// }
int is_sorted(t_stack *list) {
    if (list == NULL || list->head == NULL || list->head->next == NULL) {
        // Empty list or single element is considered sorted
        return 1;
    }

    t_node *current = list->head;
    t_node *prev = current;
    current = current->next;

    do {
        if (prev->data > current->data) {
            // Not sorted
            return 0;
        }

        prev = current;
        current = current->next;
    } while (current != list->head); // Loop until we reach the head again

    // Reached the end (head) without finding any unsorted elements
    return 1;
}

void sortStackAsc(t_stack** a, t_stack** b) {
    while (!isEmpty(*a) && !is_sorted(*a)) {
        // Find the smallest element in stack a
        int min = (*a)->head->data;
        int size = lstsize(*a);
        int minIndex = 0;
        for (int i = 0; i < size && !is_sorted(*a); i++) {
            if ((*a)->head->data < min) {
                min = (*a)->head->data;
                minIndex = i;
            }
            ra(*a);
        }

        // Move the smallest element to the top of stack a
        if (minIndex <= size / 2) {
            for (int i = 0; i < minIndex && !is_sorted(*a); i++) {
                ra(*a);
            }
        } else {
            for (int i = 0; i < size - minIndex && !is_sorted(*a); i++) {
                rra(*a);
            }
        }

        // Push the smallest element to stack b
        pb(a, b);
    }

    // Move all elements back to stack a
    while (!isEmpty(*b)) {
        pa(a, b);
    }
}


void sortStackDesc(t_stack** a, t_stack** b) {
    int maxBits = findMaxBits(*a);
    for (int bit = 0; bit < maxBits && !is_sorted(*a); bit++) {
        int size = lstsize(*a);
        for (int i = 0; i < size && !is_sorted(*a); i++) {
            int mask = 1 << bit; // Calculate mask for the current bit
            if (((*a)->head->data & mask) == 0) {
                // If the bit is not set, perform action A (rotate) instead of B (push to B)
                ra(*a);
            } else {
                // If the bit is set, perform action B (push to B) instead of A (rotate)
                pb(a, b);
            }
        }

        // Move elements back from B to A, ensuring those with bit 0 are now at the bottom
        while (!isEmpty(*b)) {
            pa(a, b);
        }
    }
    // After the final iteration, stack A will be sorted in ascending order.
}


void radix_sort(t_stack **a, t_stack **b) {
    int max_bits = findMaxBits(*a);
    t_node *current;

    for (int k = 0; k < max_bits; k++) {
        int count = 0; // count number of nodes in stack A
        current = (*a)->head;
        if (current != NULL) {
            do {
                t_node *next = current->next; // Save next node since current might move to B
                count++;
                if (((current->data >> k) & 1) == 0) {
                    pb(a, b); // Push to B if current bit is 0
                } else {
                    ra(*a); // Rotate A to access the next node
                }
                current = next;
            } while (count < max_bits && current != (*a)->head);
        }

        // Bring all elements back from B to A
        while ((*b)->head != NULL) {
            pa(a, b);
        }
    }
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
    // printArray(numbers_array, size);
	a = array_to_stack(numbers_array, size);
	b = (t_stack *)malloc(sizeof(t_stack));
    b->head = NULL;
    // display_col(a);
    sortStackDesc(&a,&b);
    // sa(a);
    display_col(a);
    // pb(&a, &b);
    // pb(&a, &b);
    // pb(&a, &b);
    // display_col(a);
    // display_col(b);
    // ra(a);
    // rb(b);
    // display_col(a);
    // display_col(b);
    // rra(a);
    // rrb(b);
    // display_col(a);
    // display_col(b);
    // sa(a);
    // display_col(a);
    // display_col(b);
    // pa(&a, &b);
    // pa(&a, &b);
    // pa(&a, &b);
    // display_col(a);
    // display_col(b);
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
