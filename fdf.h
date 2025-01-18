#ifndef FDF_H
#define FDF_H

#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "printf_bonus_norm/ft_printf.h" 

#include "minilibx/mlx.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	*mlx_init();
void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);

typedef struct
{
	int		width;
	int		height;
	int		**z_matrix;
	void	*mlx_ptr;
	void	*win_ptr;
}   fdf;

#endif