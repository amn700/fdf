// destination.x = source.x * cos(a) + source.y * cos(a+2) + source.z * cos(a-2)
// destination.y = source.x * sin(a) + source.y * sin(a+2) + source.z * sin(a-2)
// https://42-cursus.gitbook.io/guide/rank-02/fdf/understand-fdf
// screen.x = dims.x * cos(angle) + dims.y * cos(angle+2) +  data->map[dims.y].line[dims.x].z * cos(angle-2);
// screen.y = dims.x * sin(angle) + dims.y * sin(angle+2) +  data->map[dims.y].line[dims.x].z * sin(angle-2);

// DDA
// (x1, y1) cordination of the first dot
// (x2, y2) cordination of the second dot

// wtf is dx and dy

// absolute values
// dx = x2-x1;
// dy = y2-y1;

// wtf is step

// step = ((dx >= dy) ? dx : dy)

// wtf is xin and yin

// xin = dx / step
// yin = dy / step

// y and x are the dots to be colored
// why 0.5 ?

// x = x1 + 0.5
// y = y1 + 0.5

// loop

// int i = 0;

// while (i <= step)
// {
//   x = x + xin
//   y = y + yin
//   mlxputpixel(img, x, y, -1);
//   i++;
// }

#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <math.h>

typedef struct s_screen {
    float x;
    float y;
} t_screen;

int main()
{
    t_screen dims, d, one , two;
	float step;
	int i;

	mlx_t * mlx_ptr = mlx_init(500, 500, "5dm t9wd !!", false);
	mlx_image_t* img = mlx_new_image(mlx_ptr, 500, 500);
	if (!img)
		return 1;
	if (mlx_image_to_window(mlx_ptr, img, 0, 0) < 0)
		return 1;
    one.x = 0;
    one.y = 0;
    two.x = 499;
    two.y = 499;

	d.x = fabs(two.x - one.x);
	d.y = fabs(two.y - one.y);

	if(d.x >= d.y)
		step = d.x;
	else
		step = d.y;

	d.x = d.x / step;
	d.y = d.y / step;

	dims.x = one.x;
	dims.y = one.y;

	i = 1;
	while(i <= step)
	{
		mlx_put_pixel(img, dims.x, dims.y, 0xFF0000FF);
		dims.x = dims.x + d.x;
		dims.y = dims.y + d.y;
		i++;
	}

	mlx_loop(mlx_ptr);
}

// void draw_line(t_screen one, t_screen two, mlx_image_t *img)
// {
// 	t_screen d;
// 	t_screen in;
// 	t_screen screen;
// 	double step;

// 	d.x = fabs(two.x - one.x);
// 	d.y = fabs(two.y - one.y);

// 	step = ((d.x >= d.y)? d.x : d.y);

// 	in.x = d.x / step; 
// 	in.y = d.y / step;
	
// 	int i = 0;

// 	while (i <= step)
// 	{
// 		screen.x = screen.x + in.x;
// 		screen.y = screen.y + in.y;
// 		mlxputpixel(img, screen.x, screen.y, -1);
// 		i++;
// 	}
// }