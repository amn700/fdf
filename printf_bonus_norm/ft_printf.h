/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 23:26:47 by mohchaib          #+#    #+#             */
/*   Updated: 2024/12/22 05:33:39 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_norm2
{
	void	*ptr;
	int		len;
	int		width_padding;
	int		total_len;
}			t_norm2;

typedef struct s_norm
{
	int		base;
	int		is_signed;
	int		is_negative;
	int		is_zero;
	int		precision_padding;
	int		width_padding;
	int		prefix_len;
	int		total_len;
	int		len;

}			t_norm;

typedef struct s_flags
{
	int		left_align;
	int		zero_pad;
	int		width;
	int		precision;
	int		plus_sign;
	int		space_sign;
	int		alt_form;
}			t_flags;

//ft_printf.c
int			ft_printf(const char *format, ...);
//parse_flags.c
void		parse_flags(const char **format, t_flags *flags);
void		initialize_flags(t_flags *flags);
void		parse_width(const char **format, t_flags *flags);
void		parse_precision(const char **format, t_flags *flags);
//conversion_handler.c
void		handle_conversion(va_list args, const char **format, t_flags *flags,
				int *chars_written);
//helper_functions0.c
void		init_struct2(t_norm2 *norm);
void		ft_reverse_str(char *str, int len);
void		pointer_conversion(va_list args, t_flags *flags,
				int *chars_written);
int			ft_convert_number(unsigned long long n, int base, char *buffer,
				char conv);
//helper_functions1.c
int			ft_putchar(char c);
int			ft_putstr(char *str, int len);
int			ft_print_padding(char pad_char, int padding);
void		character_conversion(va_list args, t_flags *flags,
				int *chars_written);
void		string_conversion(va_list args, t_flags *flags, int *chars_written);
//helper_functions2.c
void		init_struct(t_norm *norm);
void		int_conversion(va_list args, t_flags *flags, int *chars_written);
void		unsigned_conversion(va_list args, t_flags *flags,
				int *chars_written);
void		hex_conversion(va_list args, t_flags *flags, int *chars_written,
				char conv);
void		percent_conversion(t_flags *flags, int *chars_written);
//helper_functions3.c
int			get_prefix_len(t_norm *norm, t_flags *flags);
int			get_precision_padding(t_norm *norm, t_flags *flags);
int			get_width_padding(t_norm *norm, t_flags *flags);
int			print_sign(t_norm *norm, t_flags *flags);
int			ft_print_i_number(unsigned long long n, t_norm *norm,
				t_flags *flags);
//helper_functions4.c
void		handle_null_pointer(t_flags *flags, int *chars_written,
				t_norm2 *norm);
void		ft_print_p_number(va_list args, t_flags *flags, int *chars_written,
				t_norm2 *norm);
//helper_functions5.c
int			calculate_precision_padding(int precision, int len);
int			calculate_prefix_len(int alt_form, int is_zero, char conv);
int			calculate_width_padding(int width, int total_len);
int			handle_padding(int condition, int zero_pad, int precision,
				int width_padding);
int			ft_print_x_number(unsigned long long n, t_norm *norm,
				t_flags *flags, char conv);
//helper_functions6.c
int			handle_prefix(int alt_form, int is_zero, char conv);
int			handle_precision_padding(int precision_padding);
int			handle_buffer(int len, char *buffer);
int			ft_print_number(unsigned long long n, t_norm *norm, t_flags *flags,
				char conv);
#endif