#include "fdf.h"

int	main(int argc, char** argv)
{
	if (argc != 2)
		return (write(2, "error00", 7), 1);
	t_fdf data ;
	init_struct_fdf(&data);
	if (!get_width_and_height(argv[1], &data))
		return (write(2, "error0", 6), 1);

	t_line *array = malloc (sizeof(t_line) * data.height);
	if (!array)
		return (1);
	if (!set_max_x_values(argv[1], array))
		return (write(2, "error1", 6),free(array), 1);/**/
	if (!allocate_points(array, data))
		return (write(2, "error2", 6),free(array), 1);
	if (!populate_every_point(data, array, argv[1]))
		return (write(2, "error3", 6),free(array), 1);/**/
	for(int y = 0; y < data.height; y++)
	{
		// ft_printf("%i\n", array[y].max_x);
		for(int x = 0; x < array[y].max_x; x++)
		{
			// ft_printf("%i ",array[y].map[x].z);
			ft_printf("|%s| ",array[y].map[x].color);
		}
		ft_printf("\n");
	}
	// char * line = get_next_line(fd);
	// char **matrix = ft_split(line, 32);
	// if (!matrix)
	// 	return (free(line), (1));
	
	// for (int y = 0; y < data.height; y++)
	// {
	// 	for(int x = 0; x < array[y].max_x; x++)
	// 	{
	// 		line = get_next_line(fd);
	// 		matrix = ft_split(line, 32);
	// 		for(int z = 0; z < array[y].max_x; z++)
	// 		{
	// 			array[y].map[x].z = ft_atoi(line);
	// 			array[y].map[x].color = ;            
	// 		}
	// 	}
	// }

	// t_line *array[data.height];
	// for (int y = 0; y < data.height; y++)
	// {
	// 	for(int x = 0; x < array->max_x; x++)
	// 	{
	// 		array[y].map[x].z = 10;
	// 		array[y].map[x].color = "zrg";
	// 	}
	// }
}

	// mlx_image_t* img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	// if (!img)
	// 	return 1;

	// Set every pixel to white
	// ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));

	// // Display an instance of the image
	// if (mlx_image_to_window(data->mlx_ptr, img, 0, 0) < 0)
	// 	return 1;
	
	// int i = 0;
	// while (i < HEIGHT)
	// 	mlx_put_pixel(img, i++, 10, 0x11000000);
	// mlx_put_pixel(img, 20, 20, 0x00110000);
	// mlx_put_pixel(img, 30, 30, 0x00001100);
	// mlx_put_pixel(img, 40, 40, 0x00000011);

	// mlx_loop(data->mlx_ptr);
	// mlx_close_window(data->mlx_ptr);
	// mlx_terminate(data->mlx_ptr);
	// return (EXIT_SUCCESS);