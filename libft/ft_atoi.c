/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:40:59 by mochaiba          #+#    #+#             */
/*   Updated: 2024/11/11 10:54:02 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int					sign;
	unsigned long long	total;

	sign = 1;
	total = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		total = total * 10 + (*nptr - '0');
		if (total > 9223372036854775807 && sign == 1)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		nptr++;
	}
	return (total * sign);
}
