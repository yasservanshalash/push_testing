#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include <limits.h>
#include <stdbool.h>
typedef struct t_node
{
	long			data;
    int             index;
	struct t_node	*prev;
	struct t_node	*next;
}					t_node;

// Define the Stack structure
typedef struct t_stack
{
	struct t_node	*head;
}					t_stack;

int	ft_atoi(const char *nptr);
char	**ft_split(const char *s, char delimiter);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
long	*return_numbers(int argc, char **argv, int *size);
t_stack	*array_to_stack(long arr[], int size);
int	duplicate_numbers(long *numbers, int size);
void	display(t_stack *stack);
void	free_stack(t_stack *stack);
void pa(t_stack **a, t_stack **b);
void pb(t_stack **a, t_stack **b);
void ra(t_stack *stack);

#endif
