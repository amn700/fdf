/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:09:19 by mohchaib          #+#    #+#             */
/*   Updated: 2024/11/25 16:53:09 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_struct2(t_norm2 *norm)
{
	norm->ptr = NULL;
	norm->len = 0;
	norm->width_padding = 0;
	norm->total_len = 0;
}

void	ft_reverse_str(char *str, int len)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i++] = str[j];
		str[j--] = tmp;
	}
}

void	pointer_conversion(va_list args, t_flags *flags, int *chars_written)
{
	t_norm2	norm;

	init_struct2(&norm);
	ft_print_p_number(args, flags, chars_written, &norm);
}

int	ft_convert_number(unsigned long long n, int base, char *buffer, char conv)
{
	char	*digits;
	int		len;

	if (conv == 'x')
		digits = "0123456789abcdef";
	else
		digits = "0123456789ABCDEF";
	len = 0;
	if (n == 0)
		buffer[len++] = '0';
	while (n > 0)
	{
		buffer[len++] = digits[n % base];
		n /= base;
	}
	ft_reverse_str(buffer, len);
	return (len);
}
