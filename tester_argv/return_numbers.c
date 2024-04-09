#include "push_swap.h"
  
int	count_strings(char **array_of_strings)
{
	int	count;

	count = 0;
	while (array_of_strings[count] != NULL)
		count++;
	return (count);
}

void	get_numbers(char **numbers_as_strings, long **numbers, int *j)
{
	char	**split_result;
	int		i;

	i = 0;
	split_result = ft_split(*numbers_as_strings, ' ');
	if (!split_result)
		exit(1);
	*j = count_strings(split_result);
	*numbers = (long *)malloc(*j * sizeof(long));
	if (!numbers)
		exit(1);
	i = 0;
	while (i < *j)
	{
		(*numbers)[i] = ft_atoi(split_result[i]);
		i++;
	}
	i = 0;
	while (split_result[i] != NULL)
		free(split_result[i++]);
	free(split_result);
}

void	no_args(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

void	args(char **argv, char **numbers_as_strings, int *j, long **numbers)
{
	int	i;
	int	total_length;

	i = 1;
	total_length = 0;
	while (argv[i])
	{
		total_length += ft_strlen(argv[i]) + 1;
		i++;
	}
	*numbers_as_strings = (char *)malloc(total_length + 1);
	if (!(*numbers_as_strings))
	{
		write(1, "Error: Memory allocation failed\n", 32);
		exit(1);
	}
	(*numbers_as_strings)[0] = '\0';
	i = 1;
	while (argv[i])
	{
		ft_strlcat(*numbers_as_strings, argv[i], total_length + 1);
		ft_strlcat(*numbers_as_strings, " ", total_length + 1);
		i++;
	}
}

long	*return_numbers(int argc, char **argv, int *size)
{
	char	*numbers_as_strings;
	long	*numbers;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (argc < 2)
		no_args();
	else
		args(argv, &numbers_as_strings, &j, &numbers);
	get_numbers(&numbers_as_strings, &numbers, &j);
	if (duplicate_numbers(numbers, j) == 1)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	free(numbers_as_strings);
	*size = j;
	return (numbers);
}
