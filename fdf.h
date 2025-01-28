#ifndef FDF_H
#define FDF_H

#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "ft_printf/ft_printf.h" 

#include "MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_fdf
{
	mlx_t	*mlx_ptr;
	int		width;
	int		height;
}   t_fdf;

typedef struct{
    int z;
    char *color;
}t_point;

typedef struct {
    t_point *map;
    int max_x;
}t_line;

void	init_struct_fdf(t_fdf* data);
int		check_map(int width, char *line);
int		count_words(char *str);
char	*get_color(char *point);
int		populate_every_point(t_fdf data, t_line *array, char *file_name);
int allocate_points(t_line *array, t_fdf data);
int		get_width_and_height(char* file_name, t_fdf* data);
int		count_words(char *str);
int		set_max_x_values(char *file_name, t_line *array);
// int		parse_map(t_fdf *data, char *file_name);
// void	init_struct_fdf(t_fdf *data);
// int		get_width_and_height(char* file_name, t_fdf *data);
// int		allocate_int_matrix(t_fdf *data, char *filename);
// int		populate_matrix(char *file_name, t_fdf *data);
// void	populate_line(t_fdf *data, char **matrix, int i);
// void	free_matrix_fdf(int **matrix);
// int		count_words(char *str, char c);

#endif