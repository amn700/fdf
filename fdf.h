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
#include <math.h>

// #define WIDTH 1920
// #define HEIGHT 1080
#define WIDTH 500
#define HEIGHT 500

//uint32_t is just a fking unsigned int
typedef struct s_dims{
	uint32_t	x;
	uint32_t	y;
}	t_dims;

typedef struct s_isom{
	double cos;
	double sin;
}	t_isom;

typedef struct s_offset{
	int x;
	int y;
}	t_offset;

typedef struct s_point{
	int		z;
	int		color;
}	t_point;

typedef struct s_line{
	t_point		*line;
	uint32_t	max_x;
}	t_line;

typedef struct s_fdf{
	uint32_t		width;
	uint32_t		height;
	mlx_t			*mlx_ptr;
	t_line			*map;
}	t_fdf;

int	check_extention(char * file_name);
int		ft_atoi_fdf(const char *nptr, int *i);
int		get_color(char *point, int i);
void	init_struct_fdf(t_fdf* data);
int		check_map(int width, char *line);
int		count_words(char *str);
int		populate_every_point(t_fdf data, t_line *array, char *file_name);
int		allocate_points(t_fdf *data);
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