#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include <limits.h>
# include <stdbool.h>

typedef struct t_node
{
	long			data;
	int				index;
	struct t_node	*prev;
	struct t_node	*next;
}					t_node;

typedef struct t_stack
{
	struct t_node	*head;
}					t_stack;

int					ft_atoi(const char *nptr);
char				**ft_split(const char *s, char delimiter);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
long				*return_numbers(int argc, char **argv, int *size);
t_stack				*array_to_stack(long arr[], int size);
t_stack	*array_to_stack_asc(long arr[], int size);
t_stack	*array_to_stack_desc(long arr[], int size);
int					duplicate_numbers(long *numbers, int size);
void	display_row(t_stack *stack);
void display_col(t_stack *stack);
void				free_stack(t_stack *stack);
int					swap(t_stack *stack);
void				sa(t_stack *stack);
void				sb(t_stack *stack);
void				ss(t_stack *stack_a, t_stack *stack_b);
void				push_to(t_stack **dest, t_stack **src);
void				pa(t_stack **a, t_stack **b);
void				pb(t_stack **a, t_stack **b);
void				rotate(t_stack *stack);
void				ra(t_stack *stack);
void				rb(t_stack *stack);
void				rr(t_stack *a, t_stack *b);
void				reverse_rotate(t_stack *stack);
void				rra(t_stack *stack);
void				rrb(t_stack *stack);
void				rrr(t_stack *a, t_stack *b);

#endif
