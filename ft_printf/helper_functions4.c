/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:53:40 by mohchaib          #+#    #+#             */
/*   Updated: 2024/11/25 16:53:17 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_null_pointer(t_flags *flags, int *chars_written, t_norm2 *norm)
{
	norm->len = 3;
	if (flags->width > norm->len)
		norm->width_padding = flags->width - norm->len;
	else
		norm->width_padding = 0;
	if (!flags->left_align)
		*chars_written += ft_print_padding(' ', norm->width_padding);
	*chars_written += ft_putstr("0x0", norm->len);
	if (flags->left_align)
		*chars_written += ft_print_padding(' ', norm->width_padding);
}

void	ft_print_p_number(va_list args, t_flags *flags, int *chars_written,
		t_norm2 *norm)
{
	char	buffer[18];

	norm->ptr = va_arg(args, void *);
	if (norm->ptr == NULL)
		return (handle_null_pointer(flags, chars_written, norm));
	norm->len = ft_convert_number((unsigned long)norm->ptr, 16, buffer, 'x');
	norm->total_len = norm->len + 2;
	if (flags->width > norm->total_len)
		norm->width_padding = flags->width - norm->total_len;
	else
		norm->width_padding = 0;
	if (!flags->left_align)
		*chars_written += ft_print_padding(' ', norm->width_padding);
	*chars_written += ft_putstr("0x", 2);
	*chars_written += ft_putstr(buffer, norm->len);
	if (flags->left_align)
		*chars_written += ft_print_padding(' ', norm->width_padding);
}
