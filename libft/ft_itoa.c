/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaiba <mohamedaminechaibate@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:08:26 by mochaiba          #+#    #+#             */
/*   Updated: 2024/10/01 17:14:23 by mochaiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*populate(char *new, long int nb, int size)
{
	if (nb == 0)
	{
		new[0] = '0';
		return (new);
	}
	if (nb < 0)
	{
		nb = -nb;
		new[0] = '-';
	}
	while (nb > 0)
	{
		new[--size] = nb % 10 + '0';
		nb /= 10;
	}
	return (new);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		size;
	char	*new;

	nb = n;
	size = count_char(nb);
	new = malloc(size + 1);
	if (!new)
		return (NULL);
	new[size] = '\0';
	return (populate(new, nb, size));
}
