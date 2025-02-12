#include "fdf.h"

double to_radians(int degrees)
{
    return degrees * M_PI / 180.0;
}
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
	double	scale_x;
	double	scale_y;
	double	largest_width;

	largest_width = (double)get_largest_width(data);
	scale_x = img->width / largest_width;
	scale_x = round(img->width / largest_width);
	scale_y = round(img->height / data->height);

	if (scale_x < scale_y)
		return ((int)scale_x);
	else
		return ((int)scale_y);
}

t_dims set_offset(t_fdf *data, mlx_image_t *img, int scale_factor)
{
    u_int32_t offset_x;
    u_int32_t offset_y;

    offset_x = (u_int32_t)round(img->width - (get_largest_width(data) * scale_factor)) / 2;
    offset_y = (u_int32_t)round(img->height - (data->height * scale_factor)) / 2;

    return ((t_dims){offset_x, offset_y});
}

void render_map(t_fdf *data, mlx_image_t *img)
{
    t_dims dims;
    t_screen screen;
    t_dims offset;
    // t_isom calcule;
    int scale_factor;

    // calcule = set_isom(30);
	// double rad = to_radians(45);
    scale_factor = set_scalefactor(data, img);
    offset = set_offset(data, img, scale_factor);

    dims.y = 0;
    while (dims.y < data->height)
	{
        dims.x = 0;
        while (dims.x < data->map[dims.y].max_x)
		{
			screen.x = (/* (float)*/dims.x -/*  (float)*/dims.y) * cos(to_radians(30));
			screen.y = (/* (float)*/dims.x + /* (float)*/dims.y) * sin(to_radians(30)) - data->map[dims.y].line[dims.x].z;	
			// screen.x = (float)dims.x * cos(to_radians(30)) +(float) dims.y * cos(to_radians(30+2)) + data->map[dims.y].line[dims.x].z * cos(to_radians(30-2));
			// screen.y = (float)dims.x * sin(to_radians(30)) +(float) dims.y * sin(to_radians(30+2)) + data->map[dims.y].line[dims.x].z * sin(to_radians(30-2));
			data->map[dims.y].line[dims.x].final.x = offset.x + ((screen.x) * (scale_factor / 2));
			data->map[dims.y].line[dims.x].final.y = offset.y + ((screen.y) * (scale_factor / 2));

            dims.x++;
        }
        dims.y++;
    }
}

void draw_line(t_screen one, t_screen two, mlx_image_t *img)
{
	t_screen 	d;
	t_screen 	screen;
	float 		step;
	float 		i;

	screen.x = one.x;
	screen.y = one.y;
	d.x = fabs(two.x - one.x);
	d.y = fabs(two.y - one.y);
	step = ((d.x >= d.y) ? d.x : d.y);
	// d.x = fabs(two.x - one.x) / step;
    // d.y = fabs(two.y - one.y) / step;
	d.x = d.x / step;
	d.y = d.y / step;
	i = 1;
	while (i < step)
	{
		if (screen.x >= (float)0 && screen.y >= (float)0 && screen.x < (float)img->width && screen.y < (float)img->height)
			mlx_put_pixel(img, screen.x, screen.y, -1);
		screen.x = screen.x + d.x;
		screen.y = screen.y + d.y;
		i++;
	}
}

void connect_dots(t_fdf *data, mlx_image_t* img)
{
	t_dims cords;
	t_screen begin;
	t_screen end;
	cords.y = 0;
	while (cords.y < data->height)
	{
		cords.x = 0;
		while (cords.x < data->map[cords.y].max_x)
		{
			begin = data->map[cords.y].line[cords.x].final;
			end = data->map[cords.y].line[cords.x + 1].final;
			draw_line(begin, end, img);
			cords.x++;
		}
		cords.y++;
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
	// ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	if (mlx_image_to_window(data.mlx_ptr, img, 0, 0) < 0)
		return 1;
	render_map(&data, img);
	printf("|%f|", (double)data.height);
	printf("|%f|\n", (double)data.map[0].max_x);
	printf("|%f|\n", (double)data.map[1].max_x);
	printf("|%f|\n", (double)data.map[2].max_x);
	for(int y = 0; (double)y < data.height; y++)
	{
		for(int x = 0; (double)x < data.map[y].max_x; x++)
		{
			// printf("|%f|", (double)y);
			// printf("|%f|", (double)x);
			// printf("|%f|\n",(double)data.map[y].line[x].z);

			// ft_printf("{%f}", data.height);
			// ft_printf("{%f}\n", data.map[y].max_x);
		}
	}
	connect_dots(&data, img);
	// draw_line((t_screen){0,0}, (t_screen){WIDTH, HEIGHT}, img);
	mlx_loop(data.mlx_ptr);
	return (0);
}

            // // Draw lines to adjacent points
            // if (dims.x > 0)
			// {
            //     // Draw line to the left neighbor
            //     int left_x = data->map[dims.y].line[dims.x - 1].final->x;
            //     int left_y = data->map[dims.y].line[dims.x - 1].final->y;
            //     draw_line(img, final_x, final_y, left_x, left_y, data->map[dims.y].line[dims.x].color);
            // }
            // if (dims.y > 0 && dims.x < data->map[dims.y - 1].max_x)
			// {
            //     // Draw line to the top neighbor
            //     int top_x = data->map[dims.y - 1].line[dims.x].final->x;
            //     int top_y = data->map[dims.y - 1].line[dims.x].final->y;
            //     draw_line(img, final_x, final_y, top_x, top_y, data->map[dims.y].line[dims.x].color);
            // }

// void render_map(t_fdf *data, mlx_image_t *img)
// {
// 	t_dims		dims;
// 	t_dims		screen;
// 	t_offset	offset;
// 	t_isom		calcule;
// 	int			scale_factor;
// 	int			scale_z;

//     dims.y = 0;
// 	calcule = set_isom(30);
//     scale_factor = set_scalefactor(data, img);
// 	offset = set_offset(data, img, scale_factor);
//     while (dims.y < data->height)
// 	{
//         dims.x = 0;
//         while (dims.x < data->map[dims.y].max_x)
// 		{
// 			scale_z = data->map[dims.y].line[dims.x].z * scale_factor / 10;//min z , maz z gets u the devison
// 			screen.y = (dims.x + dims.y) * calcule.sin - scale_z;
// 			screen.y = ((dims.x + dims.y) * calcule.sin )- scale_z;
//             screen.x = (dims.x - dims.y) * calcule.cos;
//             final.x =  offset.x + ((screen.x) * scale_factor);
// 			final.y =  offset.y + ((screen.y) * scale_factor);
//             if (final.x >= 0 && final.x < img->width && final.y >= 0 && final.y < img->height)
//             	mlx_put_pixel(img, final.x, final.y, -1);
//             	// mlx_put_pixel(img, dims.x, dims.y, data->map[dims.y].line[dims.x].color);
//             	// mlx_put_pixel(img, screen.x, screen.y, data->map[dims.y].line[dims.x].color);
//             dims.x++;
//         }
//         dims.y++;
//     }
// }
// void render_map(t_fdf *data, mlx_image_t *img)
// {
// 	t_dims 		final;
// 	t_dims		dims;
// 	t_dims		screen;
// 	t_offset	offset;
// 	t_isom		calcule;
// 	int			scale_factor;
// 	int			scale_z;

//     dims.y = 0;
// 	calcule = set_isom(30);
//     scale_factor = set_scalefactor(data, img);
// 	offset = set_offset(data, img, scale_factor);
//     while (dims.y < data->height)
// 	{
//         dims.x = 0;
// 		// scale_z = data->map[dims.y].line[dims.x].z * scale_factor / 10;//min z , maz z gets u the devison
// 		// screen.y = (dims.x + dims.y) * calcule.sin - scale_z;
//         while (dims.x < data->map[dims.y].max_x)
// 		{
// 			screen.y = (dims.x + dims.y) * calcule.sin - data->map[dims.y].line[dims.x].z;
//             screen.x = (dims.x - dims.y) * calcule.cos;
//             final.x =  ((offset.x +screen.x) * scale_factor);
// 			final.y =  ((offset.y +screen.y) * scale_factor);
//             if (final.x >= 0 && final.x < img->width && final.y >= 0 && final.y < img->height)
//             	mlx_put_pixel(img, final.x, final.y, data->map[dims.y].line[dims.x].color);
//             dims.x++;
//         }
//         dims.y++;
//     }
// }
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
// 	void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
// {
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