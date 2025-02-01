#include "fdf.h"

void	free_matrix_fdf(int **matrix)
{
	int i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

int	check_extention(char * file_name)
{
	size_t len = ft_strlen(file_name) - 4;
	file_name += len;
	if (!ft_strncmp(file_name, ".fdf", 4))
		return (1);
	return (0);
}

int	set_max_x_values(char *file_name, t_line *array)
{
	int y = 0;
	int fd = open (file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		array[y++].max_x = count_words(line);
		free(line);
	}
	close(fd);
	return (1);
}
static void	abort_free(t_fdf *data, int y)
{
	while (y >= 0)
	{
		free(data->map[y].line);
		y--;
	}
}

int	allocate_points(t_fdf *data)
{
	int y = 0;
	while (y < data->height)
	{
		data->map[y].line = calloc(sizeof(t_point) , data->map[y].max_x);
		if (!data->map[y].line)
			return (abort_free(data, y), 0);
		y++;
	}
	return (1);
}

static void core_populate(t_line *array, char *line, int y)
{
	char	**matrix;
	int		x;
	int		i;

	x = 0;
	i = 0;
	matrix = ft_split(line, 32);
	if (!matrix)
		return ;
	while (x < array[y].max_x)
	{
		i = 0;
		array[y].line[x].z = ft_atoi_fdf(matrix[x], &i);
		array[y].line[x].color = get_color(matrix[x], i);
		x++;
	}
	free(matrix);
}

int	populate_every_point(t_fdf data, t_line *array, char *file_name)
{
	char 	*line;
	int		y ;

	y = 0;
	int fd = open (file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	while (y < data.height)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		core_populate(array, line, y);
		free(line);
		y++;
	}
	return (1);
}

int	ft_atoi_fdf(const char *nptr, int *i)
{
	int		sign;
	int		total;

	sign = 1;
	total = 0;
	while (nptr[*i] == 32 || (nptr[*i] >= 9 && nptr[*i] <= 13))
		(*i)++;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			sign = -1;
		(*i)++;
	}
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		total = total * 10 + (nptr[*i] - '0');
		(*i)++;
	}
	return (total * sign);
}

int	locate(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

int single_color(char *point, int *i, int *color)
{
	char *base = "0123456789ABCDEF";
	*color = 0;

	if (locate(base, point[(*i)]) == -1 || locate(base, point[(*i)+ 1]) == -1)
		return (0);
	*(color) = locate(base, point[(*i)] * 16 + locate(base, point[(*i)+1]));
	*(i) += 2;
	return (1);
}

int	get_color(char *point, int i)
{
	int		place;
	int		color;
	int		full_rgb;

	place = 0;
    full_rgb = 0;
	if (ft_strlen(&point[i]) != 9)
		return (0);
	if (ft_strncmp(&point[i],",0x", 3))
		return (0);
	i += 3;
	while (place < 3)
	{
		if (!single_color(point, &i, &color))
			return (0);
		full_rgb = full_rgb << 8 | color;
		place++;
	}
	return (full_rgb);
}

int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == 32 || (str[i]>= 9 && str[i]<= 13))
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != 32 && !(str[i]>= 9 && str[i]<= 13))
			i++;
	}
	return (count);
}

int	check_map(int width, char *line)
{
	int count = count_words(line);
	if (count < width)
		return (ft_printf("Found wrong line length. Exiting."), 0);
	return 1;
}

int	get_width_and_height(char* file_name, t_fdf* data)
{
	int count = 0;
	int fd = open (file_name, O_RDONLY);
	if (fd < 0) 
		return 0;
	char *line = get_next_line(fd);
	if (!line)
		return (close(fd), (0));
	count++;
	data->width = count_words(line);
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!check_map(data->width, line))
			return (free(line), (0));
		count++;
		free(line);
	}
	data->height = count;
	close (fd);
	return (1);
}

void	init_struct_fdf(t_fdf* data)
{
	data->height = 0;
	data->width = 0;
	data->map = NULL;
	data->mlx_ptr = NULL;
}


// t_point	*points_array(char *file_name, fdf *data, int points_count)
// {
// 	t_point *points = malloc(sizeof(t_point) * points_count);
// 	if (!points)
// 		return 0;
// 	int fd = open(file_name, O_RDONLY);
// 	if (fd < 0)
// 		return 0;
// 	char *line = get_next_line(fd);
// 	if (!line)
// 		return (close(fd), 0);
// 	int i = 0;
// 	int j = 0;
// 	while (line)
// 	{
// 		char **split = ft_split(line, 32);
// 		if (!split)
// 			return (close(fd), 0);
// 		while (split[j])
// 		{
// 			points[i].x = j;
// 			points[i].y = i;
// 			points[i].z = ft_atoi(split[j]);
// 			if (ft_strchr(split[j], ','))
// 				points[i].color = ft_strdup(ft_strchr(split[j], ',') + 1);
// 			else
// 				points[i].color = NULL;
// 			j++;
// 			i++;
// 		}
// 		free(split);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return points;
// }

// t_point	*get_points(char *file_name, fdf *data)
// {
// 	t_point *points;
// 	int fd = open(file_name, O_RDONLY);
// 	if (fd < 0)
// 		return 0;
// 	char	*line = get_next_line(fd);
// 	int points_count = 0;
// 	if (!line)
// 		return (close(fd), 0);
// 	while (line)
// 	{
// 		points_count += count_words(line, 32);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (points_array(file_name, data, points_count));
// }

// int		parse_map(t_fdf *data, char *file_name)
// {
// 	init_struct_fdf(data);
// 	if (!get_height(file_name, data))
// 		return (free(data), 0);
// 	if (!get_width(file_name, data))
// 		return (free(data), 0);
// //	extract from the file the coordinates of the points and the color of each point
// 	t_point *points = get_points(file_name, data);

// 	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "fdf", false);
// 	if (!data->mlx_ptr)
// 		return (free(data), 0);
// 	return 1;
// }

// int		allocate_int_matrix(fdf* data, char *filename)
// {
// 	int		i = 0;
// 	char	*line = 0;
// 	int 	len = 0;
// 	int		fd = open (filename, O_RDONLY);
// 	if (fd < 0) 
// 		return 0;
// 	data->z_matrix = malloc(sizeof(int *) * (data->height));
// 	if (!data->z_matrix)
// 		return 0;
// 	line = get_next_line(fd);
// 	if (!line)
// 		return (close(fd), 0);
// 	while (!line)
// 	{
// 		data->z_matrix[i] = malloc(sizeof(int) * count_words(line, 32));
// 		if (!data->z_matrix[i])
// 			return 0;
// 		i++;
// 	}
// 	return 1;
// }

// void	populate_line(fdf *data, char** matrix, int i)
// {
// 	int j = 0;
// 	while (j < data->width)
// 	{
// 		data->z_matrix[i][j] = ft_atoi(matrix[j]);
// 		if (matrix[j][0] == '\n')
// 			break;
// 		j++;
// 	}
// }

// int		populate_matrix(char* file_name, fdf * data)
// {
// 	int i = 0;
// 	char **matrix;
// 	char * line = NULL;
// 	int fd = open (file_name, O_RDONLY);
// 	if(fd < 0)
// 		return 0;
// 	while (i < data->height)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			return(close(fd), 0);
// 		matrix = ft_split(line, 32);
// 		if (!matrix)
// 			return(free(line), close(fd), 0);
// 		free(line);
// 		populate_line(data, matrix, i);
// 		free(matrix);
// 		i++;
// 	}
// 	close(fd);
// 	return 1;
// }