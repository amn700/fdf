/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:39:44 by mochaiba          #+#    #+#             */
/*   Updated: 2024/11/11 13:42:22 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*src_str;
	char	*dst_str;
	size_t	index;

	if (src == dest)
		return (dest);
	src_str = (char *)src;
	dst_str = dest;
	index = 0;
	while (index < n)
	{
		dst_str[index] = src_str[index];
		index++;
	}
	return (dest);
}
