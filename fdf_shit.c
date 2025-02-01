#include "fdf.h"

void free_fdf_map(t_fdf *data)
{
	uint32_t y = 0;
	while (y < data->height)
	{
		free(data->map[y].line);
		y++;
	}
	free(data->map);
}

uint32_t get_largest_width(t_fdf *data)
{
	uint32_t max = 0;
	uint32_t y = 0;
	while (y < data->height)
	{
		if (data->map[y].max_x > max)
			max = data->map[y].max_x;
		y++;
	}
	return (max);
}

double to_radians(int degrees)
{
    return degrees * M_PI / 180.0;
}

t_isom set_isom(int angle)
{
	double		sin_angle;
	double		cos_angle;
	double		rad;

    rad = to_radians(angle);
    sin_angle = sin(rad);
    cos_angle = cos(rad);
	return ((t_isom){cos_angle, sin_angle});
}

int	set_scalefactor(t_fdf *data, mlx_image_t *img)
{
	int	scale_x;
	int	scale_y;
	int	largest_width;

	largest_width = get_largest_width(data);
	scale_x = img->width / largest_width;
	scale_y = img->height / data->height;
	if (scale_x < scale_y)
		return (scale_x);
	else
		return (scale_y);	
}

t_offset set_offset(t_fdf *data, mlx_image_t *img, int scale_factor)
{
	int offset_x;
    int offset_y;

	offset_x = (img->width - (get_largest_width(data) * scale_factor)) / 2;
    offset_y = (img->height - (data->height * scale_factor)) / 2;
	return ((t_offset){offset_x, offset_y});
}


void render_map(t_fdf *data, mlx_image_t *img)
{
	t_dims 		final;
	t_dims		dims;
	t_dims		screen;
	t_offset	offset;
	t_isom		calcule;
	int			scale_factor;
	int			scale_z;

    dims.y = 0;
	calcule = set_isom(30);
    scale_factor = set_scalefactor(data, img);
	offset = set_offset(data, img, scale_factor);
    while (dims.y < data->height)
	{
        dims.x = 0;
		// scale_z = data->map[dims.y].line[dims.x].z * scale_factor / 10;//min z , maz z gets u the devison
		// screen.y = (dims.x + dims.y) * calcule.sin - scale_z;
        while (dims.x < data->map[dims.y].max_x)
		{
			screen.y = (dims.x + dims.y) * calcule.sin - data->map[dims.y].line[dims.x].z;
            screen.x = (dims.x - dims.y) * calcule.cos;
            final.x =  ((offset.x +screen.x) * scale_factor);
			final.y =  ((offset.y +screen.y) * scale_factor);
            if (final.x >= 0 && final.x < img->width && final.y >= 0 && final.y < img->height)
            	mlx_put_pixel(img, final.x, final.y, data->map[dims.y].line[dims.x].color);
            dims.x++;
        }
        dims.y++;
    }
}

int	main(int argc, char** argv)
{
	if (argc != 2)
		return (write(2, "error0\n\n", 7), 1);
	t_fdf data;
	init_struct_fdf(&data);
	if(!check_extention(argv[1]))
		return (1);
	if (!get_width_and_height(argv[1], &data))
		return (write(2, "error1\n", 7), 1);
	data.map = malloc (sizeof(t_line) * data.height);
	if (!data.map)
		return (1);
	if (!set_max_x_values(argv[1], data.map))
		return (write(2, "error2\n", 7),free(data.map), 1);
	if (!allocate_points(&data))
		return (write(2, "error3\n", 7),free(data.map), 1);
	if (!populate_every_point(data, data.map, argv[1]))
		return (write(2, "error4\n", 7),free_fdf_map(&data), 1);
	data.mlx_ptr = mlx_init(WIDTH, HEIGHT, "fdf", false);
	if (!data.mlx_ptr)
		return (write(2, "error5\n", 7),free_fdf_map(&data), 1);
	
	mlx_image_t* img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	if (!img)
		return 1;
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	if (mlx_image_to_window(data.mlx_ptr, img, 0, 0) < 0)
		return 1;
	render_map(&data, img);
	// int largest_width = get_largest_width(&data);
	// int scale_x = img->width / largest_width;
	// int scale_y = img->height / data.height;

	// int scale_factor;
	// if (scale_x < scale_y)
	// 	scale_factor = scale_x ;
	// else
	// 	scale_factor = scale_y;
	// int y;
	// int x;
	// int screen_x;
	// int screen_y;
	// int angle;
	// y = 0;
	// x = 0;
	// angle = 20;
	// // int offset_y = 0;
	// // int offset_x = 0;
	// int offset_y = (img->height - (data.height * scale_factor)) / 2;
	// int offset_x = (img->width - (largest_width * scale_factor)) / 2;
	// // printf("%i\n", offset_x);
	// // printf("%i\n", offset_y);
	// while (y < data.height)
	// {
	// 	x = 0;
	// 	screen_y = (x + y) * sin(angle) - data.map[y].line[x].z;
	// 	while (x < data.map[y].max_x)
	// 	{
	// 		screen_x = (x - y) * cos(angle);
	// 		mlx_put_pixel(img,  (offset_x + screen_x)*(scale_factor),  (offset_y + screen_y)*(scale_factor), data.map[y].line[x].color);
	// 		x++;
	// 	}
	// 	y++;
	// }
 	// y' = (x + y) * sin(angle) - z;
	// x' = (x - y) * cos(angle);

	mlx_loop(data.mlx_ptr);
	return (0);
}

	// for(int y = 0; y < data.height; y++)
	// {
	// 	for(int x = 0; x < data.map[y].max_x; x++)
	// 	{
	// 		ft_printf("%-10i",data.map[y].line[x].color);
	// 		ft_printf("%-10i",data.map[y].line[x].z);
	// 	}
	// 	ft_printf("\n");
	// }


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
// 	void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color) {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = (x0 < x1) ? 1 : -1;
//     int sy = (y0 < y1) ? 1 : -1;
//     int err = dx - dy;

//     while (1) {
//         // Draw the pixel if it's within the image boundaries
//         if (x0 >= 0 && x0 < img->width && y0 >= 0 && y0 < img->height) {
//             mlx_put_pixel(img, x0, y0, color);
//         }

//         // Break if we've reached the end point
//         if (x0 == x1 && y0 == y1) break;

//         int e2 = 2 * err;
//         if (e2 > -dy) {
//             err -= dy;
//             x0 += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y0 += sy;
//         }
//     }
// }

// // Render the map with isometric projection
// void render_map(t_fdf *data, mlx_image_t *img) {
//     t_dims dims;
//     t_dims screen;
//     t_offset offset;
//     t_isom calcule;
//     int scale_factor;

//     // Initialize isometric transformation values
//     calcule = set_isom(30);

//     // Calculate scale factor and offset
//     scale_factor = set_scalefactor(data, img);
//     offset = set_offset(data, img, scale_factor);

//     // Render the map
//     for (dims.y = 0; dims.y < data->height; dims.y++) {
//         for (dims.x = 0; dims.x < data->map[dims.y].max_x; dims.x++) {
//             // Apply isometric transformation
//             screen.x = (dims.x - dims.y) * calcule.cos;
//             screen.y = (dims.x + dims.y) * calcule.sin - data->map[dims.y].line[dims.x].z;

//             // Scale and offset the coordinates
//             int final_x = offset.x + (screen.x * scale_factor);
//             int final_y = offset.y + (screen.y * scale_factor);

//             // Store the final coordinates for later use
//             // data->map[dims.y].line[dims.x].final_x = final_x;
//             // data->map[dims.y].line[dims.x].final_y = final_y;

//             // Draw the point
//             if (final_x >= 0 && final_x < img->width && final_y >= 0 && final_y < img->height) {
//                 mlx_put_pixel(img, final_x, final_y, data->map[dims.y].line[dims.x].color);
//             }

//             // Draw lines to adjacent points
//             if (dims.x > 0) {
//                 // Draw line to the left neighbor
//                 int left_x = final_x;
//                 int left_y = final_y;
//                 draw_line(img, final_x, final_y, left_x, left_y, data->map[dims.y].line[dims.x].color);
//             }
//             if (dims.y > 0 && dims.x < data->map[dims.y - 1].max_x) {
//                 // Draw line to the top neighbor
//                 int top_x = final_x;
//                 int top_y = final_y;
//                 draw_line(img, final_x, final_y, top_x, top_y, data->map[dims.y].line[dims.x].color);
//             }
//         }
//     }
// }