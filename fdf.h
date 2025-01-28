#ifndef FDF_H
#define FDF_H

#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "printf_bonus_norm/ft_printf.h" 

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


typedef struct s_map
{
	int z;
	int x;
	int max_x;//len of line y
	char *color;

}	t_map;

typedef struct s_fdf
{
	int		width;
	int		height;
	t_map 	**line;

}   t_fdf;

#endif