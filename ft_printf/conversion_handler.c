/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:47:44 by mohchaib          #+#    #+#             */
/*   Updated: 2024/11/25 16:52:59 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_conversion(va_list args, const char **format, t_flags *flags,
		int *chars_written)
{
	if (**format == 'c')
		character_conversion(args, flags, chars_written);
	else if (**format == 's')
		string_conversion(args, flags, chars_written);
	else if (**format == 'd' || **format == 'i')
		int_conversion(args, flags, chars_written);
	else if (**format == 'u')
		unsigned_conversion(args, flags, chars_written);
	else if (**format == 'x' || **format == 'X')
		hex_conversion(args, flags, chars_written, **format);
	else if (**format == 'p')
		pointer_conversion(args, flags, chars_written);
	else if (**format == '%')
		percent_conversion(flags, chars_written);
}
