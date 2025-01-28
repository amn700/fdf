#include "fdf.h"

int check_extention(char *file_name)
{
    size_t name_len = ft_strlen(file_name) - 4;
    *file_name += name_len;
    if (!ft_strncmp(file_name, ".fdf", 4))
        return (1);
    return (0);
}

int     get_two_dimentions(char* file_name, t_fdf* data)
{
    int count = 0;
    int fd = open (file_name, O_RDONLY);
    if (fd < 0) 
        return 0;
    char *line = get_next_line(fd);
    if (!line)
        return (close(fd), 0);
    data->width = ft_strlen(line);
    count++;
    free(line);
    while (line != NULL)
    {
        line = get_next_line(fd);
        if (!line)
            return (close(fd), 0);
        count++;
        free(line);
    }
    data->height = count;
    return (close(fd), 1);
}

int     main(int argc, char** argv)
{
    t_fdf* data;

    if (argc != 2)
        return (ft_printf("invalid number of arguments.\n"), (1));
    if (!check_extention(argv[1]))
        return (ft_printf("wrong file extension.\n"), (1));
    data = malloc(sizeof(t_fdf));
    if(!data)
        return (ft_printf("error.\n"), (1));
    if (!get_two_dimentions(argv[1], data))
        return (free(data), 1);
    data->line[0]->y;
    return (0);
}