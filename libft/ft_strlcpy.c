/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:13:13 by mochaiba          #+#    #+#             */
/*   Updated: 2024/11/03 12:46:03 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	index;

	src_len = ft_strlen(src);
	index = 0;
	if (size)
	{
		while (src[index] && index < (size - 1))
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = 0;
	}
	return (src_len);
}
