/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:34:59 by mohchaib          #+#    #+#             */
/*   Updated: 2024/11/25 16:53:25 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialize_flags(t_flags *flags)
{
	flags->left_align = 0;
	flags->zero_pad = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->plus_sign = 0;
	flags->space_sign = 0;
	flags->alt_form = 0;
}

void	parse_width(const char **format, t_flags *flags)
{
	while (**format >= '0' && **format <= '9')
	{
		flags->width = flags->width * 10 + (**format - '0');
		(*format)++;
	}
}

void	parse_precision(const char **format, t_flags *flags)
{
	if (**format == '.')
	{
		(*format)++;
		flags->precision = 0;
		while (**format >= '0' && **format <= '9')
		{
			flags->precision = flags->precision * 10 + (**format - '0');
			(*format)++;
		}
	}
}

void	parse_flags(const char **format, t_flags *flags)
{
	initialize_flags(flags);
	while (**format == '-' || **format == '0' || **format == '+'
		|| **format == ' ' || **format == '#')
	{
		if (**format == '-')
		{
			flags->left_align = 1;
			flags->zero_pad = 0;
		}
		else if (**format == '0' && !flags->left_align)
			flags->zero_pad = 1;
		else if (**format == '+')
		{
			flags->plus_sign = 1;
			flags->space_sign = 0;
		}
		else if (**format == ' ' && !flags->plus_sign)
			flags->space_sign = 1;
		else if (**format == '#')
			flags->alt_form = 1;
		(*format)++;
	}
	parse_width(format, flags);
	parse_precision(format, flags);
}
