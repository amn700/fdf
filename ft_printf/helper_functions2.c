/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:33:10 by mohchaib          #+#    #+#             */
/*   Updated: 2024/11/25 16:53:13 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_struct(t_norm *norm)
{
	norm->base = 0;
	norm->is_signed = 0;
	norm->is_negative = 0;
	norm->is_zero = 0;
	norm->precision_padding = 0;
	norm->width_padding = 0;
	norm->prefix_len = 0;
	norm->total_len = 0;
	norm->len = 0;
}

void	int_conversion(va_list args, t_flags *flags, int *chars_written)
{
	t_norm	norm;
	long	num;

	init_struct(&norm);
	num = va_arg(args, int);
	norm.is_zero = (num == 0);
	if (num < 0)
	{
		norm.base = 10;
		norm.is_signed = 1;
		norm.is_negative = 1;
		*chars_written += ft_print_number(-num, &norm, flags, 'i');
	}
	else
	{
		norm.base = 10;
		norm.is_signed = 1;
		norm.is_negative = 0;
		*chars_written += ft_print_number(num, &norm, flags, 'i');
	}
}

void	unsigned_conversion(va_list args, t_flags *flags, int *chars_written)
{
	t_norm			norm;
	unsigned int	num;

	init_struct(&norm);
	num = va_arg(args, unsigned int);
	norm.base = 10;
	norm.is_signed = 0;
	norm.is_negative = 0;
	norm.is_zero = (num == 0);
	*chars_written += ft_print_number(num, &norm, flags, 'u');
}

void	hex_conversion(va_list args, t_flags *flags, int *chars_written,
		char conv)
{
	t_norm			norm;
	unsigned int	num;

	init_struct(&norm);
	num = va_arg(args, unsigned int);
	norm.base = 16;
	norm.is_signed = 0;
	norm.is_negative = 0;
	norm.is_zero = (num == 0);
	*chars_written += ft_print_number(num, &norm, flags, conv);
}

void	percent_conversion(t_flags *flags, int *chars_written)
{
	int	width_padding;

	if (flags->width > 1)
		width_padding = flags->width - 1;
	else
		width_padding = 0;
	if (!flags->left_align)
	{
		while (width_padding-- > 0)
		{
			ft_putchar(' ');
			(*chars_written)++;
		}
	}
	*chars_written += ft_putchar('%');
	if (flags->left_align)
	{
		while (width_padding-- > 0)
		{
			ft_putchar(' ');
			(*chars_written)++;
		}
	}
}
