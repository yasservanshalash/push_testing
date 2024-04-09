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
    if (stack->head == NULL) {
        stack->head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    } else {
        new_node->prev = stack->head->prev;
        new_node->next = stack->head;
        stack->head->prev->next = new_node;
        stack->head->prev = new_node;
        // Do not update stack->head to keep the order the same as the array
    }
}


// Function to display the elements of the stack
void	display(t_stack *stack)
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