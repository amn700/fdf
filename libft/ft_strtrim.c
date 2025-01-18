/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaiba <mohamedaminechaibate@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:42:39 by mochaiba          #+#    #+#             */
/*   Updated: 2024/10/05 03:39:01 by mochaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	included(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_size(char *str, char *set)
{
	int	i;
	int	count;
	int	len;

	len = ft_strlen(str);
	i = len - 1;
	count = 0;
	while (str[count] && included(str[count], set))
		count++;
	if (count == len)
		return (len);
	while (i >= 0 && included(str[i], set))
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	char	*new;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	size = ft_strlen(s1) - count_size((char *)s1, (char *)set);
	new = malloc(size + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (included(*s1, (char *)set))
		s1++;
	while (i < size)
	{
		new[i] = s1[i];
		i++;
	}
	new[size] = '\0';
	return (new);
}
