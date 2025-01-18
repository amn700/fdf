/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:42:33 by mochaiba          #+#    #+#             */
/*   Updated: 2024/11/11 13:29:18 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	else if (*haystack == '\0')
		return (NULL);
	if (needle_len <= len)
	{
		while (i <= (len - needle_len) && haystack[i])
		{
			if (!ft_strncmp(haystack + i, needle, needle_len))
				return ((char *)(haystack + i));
			i++;
		}
	}
	return (NULL);
}
