/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:43:42 by mochaiba          #+#    #+#             */
/*   Updated: 2024/11/11 11:41:41 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_matrix(char **matrix, int i)
{
	while (i >= 0)
		free(matrix[i--]);
	free(matrix);
}

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static char	*ft_addstr(char *str, char c)
{
	int		i;
	int		size;
	char	*new;

	size = 0;
	while (str[size] != c && str[size])
		size++;
	new = malloc(size + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = str[i];
		i++;
	}
	new[size] = '\0';
	return (new);
}

static int	populate(char **matrix, char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
		{
			matrix[i] = ft_addstr(str, c);
			if (!matrix[i])
			{
				free_matrix(matrix, i - 1);
				return (0);
			}
			i++;
		}
		while (*str != c && *str)
			str++;
	}
	matrix[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**matrix;

	if (!s)
		return (NULL);
	size = count_words((char *)s, c);
	matrix = malloc((size + 1) * sizeof(char *));
	if (matrix == NULL)
		return (NULL);
	if (!populate(matrix, (char *)s, c))
		return (NULL);
	return (matrix);
}
