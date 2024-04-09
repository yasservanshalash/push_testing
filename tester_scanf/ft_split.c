/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yshalash <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 09:17:11 by yshalash      #+#    #+#                 */
/*   Updated: 2024/02/05 15:42:58 by yshalash      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

static int	count_words_in_string(const char *str, char delimiter)
{
	int	word_count;
	int	in_word;

	word_count = 0;
	in_word = 0;
	while (*str != '\0')
	{
		if (*str != delimiter && !in_word)
		{
			in_word = 1;
			word_count++;
		}
		else if (*str == delimiter)
		{
			in_word = 0;
		}
		str++;
	}
	return (word_count);
}

static char	*duplicate_word(const char *str, int start, int end)
{
	char	*word;
	int		word_length;
	int		i;

	word_length = end - start;
	i = 0;
	word = malloc((word_length + 1) * sizeof(char));
	if (word == NULL)
	{
		return (NULL);
	}
	while (start < end)
	{
		word[i++] = str[start++];
	}
	word[i] = '\0';
	return (word);
}

static void	free_word(char **result, size_t *j)
{
	while (*j > 0)
		free(result[--(*j)]);
	free(result);
}

static int	logic(const char *s, char delimiter, char **result, size_t *j)
{
	size_t	i;
	int		start_index;
	char	*word;

	start_index = -1;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != delimiter && start_index < 0)
			start_index = i;
		else if ((s[i] == delimiter || i == ft_strlen(s)) && start_index >= 0)
		{
			word = duplicate_word(s, start_index, i);
			if (word == NULL)
			{
				free_word(result, &*j);
				return (0);
			}
			result[(*j)++] = word;
			start_index = -1;
		}
		(i)++;
	}
	return (1);
}

char	**ft_split(const char *s, char delimiter)
{
	char	**result;
	size_t	j;

	if (!s)
		return (NULL);
	result = malloc((count_words_in_string(s, delimiter) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	j = 0;
	if (!logic(s, delimiter, result, &j))
	{
		return (NULL);
	}
	result[j] = NULL;
	return (result);
}