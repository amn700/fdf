/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:06:39 by mohchaib          #+#    #+#             */
/*   Updated: 2024/11/25 16:53:11 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str, int len)
{
	return (write(1, str, len));
}

int	ft_print_padding(char pad_char, int padding)
{
	int	chars_written;

	chars_written = 0;
	while (padding-- > 0)
		chars_written += ft_putchar(pad_char);
	return (chars_written);
}

void	character_conversion(va_list args, t_flags *flags, int *chars_written)
{
	char	c;
	int		padding;

	c = (char)va_arg(args, int);
	if (flags->width > 1)
		padding = flags->width - 1;
	else
		padding = 0;
	if (!flags->left_align)
		*chars_written += ft_print_padding(' ', padding);
	*chars_written += ft_putchar(c);
	if (flags->left_align)
		*chars_written += ft_print_padding(' ', padding);
}

void	string_conversion(va_list args, t_flags *flags, int *chars_written)
{
	char	*str;
	int		len;
	int		padding;

	len = 0;
	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	while (str[len])
	{
		if (flags->precision != -1 && len >= flags->precision)
			break ;
		len++;
	}
	if (flags->width > len)
		padding = flags->width - len;
	else
		padding = 0;
	if (!flags->left_align)
		*chars_written += ft_print_padding(' ', padding);
	*chars_written += ft_putstr(str, len);
	if (flags->left_align)
		*chars_written += ft_print_padding(' ', padding);
}
