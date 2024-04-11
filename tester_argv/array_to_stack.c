#include "push_swap.h"

void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*temp;

	if (stack == NULL || stack->head == NULL)
		return ;
	current = stack->head;
	while (current->next != stack->head)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	free(current); // Free the last node
	stack->head = NULL;
	free(stack); // Free the stack itself
}

// Function to create a new Node
t_node	*create_node(long data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = data;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

// Function to push a new node onto the stack
void push(t_stack *stack, long data) {
    t_node *new_node = create_node(data);
    if (new_node == NULL) {
        // Handle memory allocation failure
        return;
    }

    if (stack->head == NULL) {
        // If the stack is empty, this new node is both the head and forms a circular reference to itself
        stack->head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    } else {
        // Insert the new node before the current head, making it the new head
        // This is because we want to maintain the order such that the last given number becomes the top of the stack
        new_node->prev = stack->head->prev; // New node's prev points to what was the last node
        new_node->next = stack->head;       // New node's next points to the current head
        
        stack->head->prev->next = new_node; // The old last node's next points to the new node
        stack->head->prev = new_node;       // The current head's prev points to the new node
        stack->head = new_node;             // Update the head to point to the new node
    }
}



// Function to display the elements of the stack
void	display_row(t_stack *stack)
{
	t_node	*current;

	if (stack == NULL || stack->head == NULL)
	{
		printf("Stack is empty.\n");
		return ;
	}
	printf("Stack: ");
	current = stack->head;
	while (1)
	{
		printf("%ld -> ", current->data);
		current = current->next;
		if (current == stack->head)
		{
			break ;
		}
	}
	printf("NULL\n");
}

void display_col(t_stack *stack)
{
    if (stack == NULL || stack->head == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }

    t_node *current = stack->head->prev; // Start from the bottom (the last node before head in the circular list)

    printf("Stack:\n");
    do {
        current = current->next; // Move upwards through the stack
        printf("| %ld |\n", current->data); // Print each value in the stack
    } while (current != stack->head->prev); // Loop until we've circled back to the start

    printf("'----'\n");
}


// Function to loop over an array of numbers
// and put each number in a node of a linked list called Stack
t_stack	*array_to_stack(long arr[], int size)
{
	t_stack	*stack;
	int		i;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (stack == NULL)
		return (NULL);
	stack->head = NULL;
	i = 0;
	while (i < size)
	{
		push(stack, arr[i]);
		i++;
	}
	return (stack);
}