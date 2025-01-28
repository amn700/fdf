/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:58:06 by mohchaib          #+#    #+#             */
/*   Updated: 2024/11/25 16:53:15 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	part_one(t_norm *norm, t_flags *flags, char conv)
{
	if (norm->is_zero && flags->precision == 0)
		norm->len = 0;
	if (flags->precision > norm->len)
		norm->precision_padding = flags->precision - norm->len;
	else
		norm->precision_padding = 0;
	norm->prefix_len = 0;
	if (flags->alt_form && !norm->is_zero && (conv == 'x' || conv == 'X'))
		norm->prefix_len = 2;
	if (norm->is_signed && (norm->is_negative || flags->plus_sign
			|| flags->space_sign))
		norm->prefix_len = 1;
	norm->total_len = norm->len + norm->precision_padding + norm->prefix_len;
	if (flags->width > norm->total_len)
		norm->width_padding = flags->width - norm->total_len;
	else
		norm->width_padding = 0;
}

void	part_two(t_norm *norm, t_flags *flags, char conv, int *chars_written)
{
	if (!flags->left_align && (!flags->zero_pad || flags->precision != -1))
		while (norm->width_padding-- > 0)
			*chars_written += ft_putchar(' ');
	if (norm->is_signed)
	{
		if (norm->is_negative)
			*chars_written += ft_putchar('-');
		else if (flags->plus_sign)
			*chars_written += ft_putchar('+');
		else if (flags->space_sign)
			*chars_written += ft_putchar(' ');
	}
	if (flags->alt_form && !norm->is_zero && (conv == 'x' || conv == 'X'))
		*chars_written += ft_putchar('0') + ft_putchar(conv);
	if (!flags->left_align && flags->zero_pad && flags->precision == -1)
		while (norm->width_padding-- > 0)
			*chars_written += ft_putchar('0');
	while (norm->precision_padding-- > 0)
		*chars_written += ft_putchar('0');
}

int	ft_print_number(unsigned long long n, t_norm *norm, t_flags *flags,
		char conv)
{
	char	buffer[10];
	int		chars_written;

	chars_written = 0;
	norm->len = ft_convert_number(n, norm->base, buffer, conv);
	part_one(norm, flags, conv);
	part_two(norm, flags, conv, &chars_written);
	if (norm->len > 0)
		chars_written += ft_putstr(buffer, norm->len);
	if (flags->left_align)
		while (norm->width_padding-- > 0)
			chars_written += ft_putchar(' ');
	return (chars_written);
}
