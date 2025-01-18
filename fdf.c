#include "fdf.h"

int     get_width(char* file_name, fdf* data)
{
    int fd = open (file_name, O_RDONLY);
    if (fd < 0) 
        return 0;
    char *line = get_next_line(fd);
    if (!line)
        return (close(fd), 0);
    data->width = ft_strlen(line);
    return (free(line),close(fd),1);
}

int     get_height(char* file_name, fdf* data)
{
    int count = 0;
    int fd = open (file_name, O_RDONLY);
    if (fd < 0) 
        return 0;
    char *line = get_next_line(fd);
    if (!line)
        return 0;
    count++;
    free(line);
    while (line != NULL)
    {
        line = get_next_line(fd);
        if (!line)
            return 0;
        count++;
        free(line);
    }
    data->height = count;
    return 1;
}

int     allocate_int_matrix(fdf* data)
{
    data->z_matrix = malloc (sizeof(int *) * (data->height));
    if (!data->z_matrix)
        return 0;
    int i = 0;
    while (i < data->width)
    {
        data->z_matrix[i] = malloc(sizeof(int) * (data->width));
        i++;
    }
    return 1;
}

void    populate_line(fdf *data, char** matrix, int i)
{
    int j = 0;
    while (j < data->width)
    {
        data->z_matrix[i][j] = ft_atoi(matrix[j]);
        j++;
    }
}

int     populate_matrix(char* file_name, fdf * data)
{
    char * line;
    char **matrix;
    int fd = open (file_name, O_RDONLY);
    if(fd < 0)
        return 1;
    int i = 0;
    int j = 0;
    while (i < data->height)
    {
        line = get_next_line(fd);
        if (!line)
            return 1;
        matrix = ft_split(line, 32);
        if (!matrix)
            return 1;
        free(line);
        populate_line(data, matrix, i);
            // data->z_matrix[i][j] = (ft_atoi(matrix[j]));
        free(matrix);
        i++;
    }
    return 0;
}

int     main(int argc, char** argv)
{
    fdf* data;
    data = malloc(sizeof(fdf));
    if(!data)
        return 1;
    if (get_height(argv[1], data) < 0)
        return (free(data), 1);
    if (get_width(argv[1], data) < 0)
        return (free(data), 1);
    if (allocate_int_matrix(data) < 0)
        return (free(data), 1);
    //should free the matrix too from now on 
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
        return (/**/free(data), 1);
    data->win_ptr = mlx_new_window(data->mlx_ptr, 600, 800, "fdf");
    if (!data->win_ptr)
        return (/**/free(data), 1);
    if (!populate_matrix(argv[1], data))
        return (/**/free(data), 1);
}