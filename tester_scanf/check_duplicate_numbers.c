#include "push_swap.h"

int	duplicate_numbers(long *numbers, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (numbers[j] == numbers[i])
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}