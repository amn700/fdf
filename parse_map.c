#include "fdf.h"

// void	free_matrix_fdf(int **matrix)
// {
// 	int i = 0;
// 	while (matrix[i])
// 		free(matrix[i++]);
// 	free(matrix);
// }
int check_extention(char * file_name)
{
	size_t len = ft_strlen(file_name) - 4;
	file_name += len;
	if (!ft_strncmp(file_name, ".fdf", 4))
		return 1;
	return 0;
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

int allocate_points(t_line *array, t_fdf data)
{
	int y = 0;
	while (y < data.height)
	{
		array[y].map = calloc(sizeof(t_point) , array[y].max_x);
		if (!array[y].map)
			return (0);
		y++;
	}
	return (1);
}

int	populate_every_point(t_fdf data, t_line *array, char *file_name)
{
	int x = 0;
	int y = 0;
	char *line;
	char **matrix;

	int fd = open (file_name, O_RDONLY);
	if (fd < 0)
		return 0;
	while (y < data.height)
	{
		x = 0;
		line = get_next_line(fd);
			if (!line)
				break;
		matrix = ft_split(line, 32);
		if (!matrix)
			return 0;
		while (x < array[y].max_x)
		{
			// ft_printf("|%i|",array[y].max_x);
			// ft_printf("|%s|",line);
			array[y].map[x].z = ft_atoi(matrix[x]);
			// ft_printf("(%i |",array[y].map[x].z);
			array[y].map[x].color = get_color(matrix[x]);
			// ft_printf("%s)",array[y].map->color);
			x++;
		}
		free(line);
		free(matrix);
		y++;
	}
	return 1;
}

char	*get_color(char *point)
{
	int i = 0;
	while (point[i])
	{
		if (point[i] == ',')
			return (ft_strdup(&point[++i]));
			// ft_printf("%s\n", &point[i]);
		i++;
	}
	return NULL;
}

int		count_words(char *str)
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

int		check_map(int width, char *line)
{
	int count = count_words(line);
	if (count < width)
	{
		// ft_printf("%i || %i \n", count, width);
		return (ft_printf("Found wrong line length. Exiting."), 0);
	}
	return 1;
}

int		get_width_and_height(char* file_name, t_fdf* data)
{
	int count = 0;
	int fd = open (file_name, O_RDONLY);
	if (fd < 0) 
		return 0;
	char *line = get_next_line(fd);
	if (!line)
		return (close(fd), (0));
	count++;
	// ft_printf("%s", line);
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