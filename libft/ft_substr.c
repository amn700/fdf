/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:44:09 by mochaiba          #+#    #+#             */
/*   Updated: 2024/11/11 11:44:26 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (str[i] && i < len)
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		size;
	char	*new;
	int		i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	size = count((char *)&s[start], len);
	new = malloc(size + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = s[start + i];
		i++;
	}
	new[size] = '\0';
	return (new);
}
