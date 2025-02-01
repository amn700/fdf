#include <stdio.h>
#include "fdf.h"

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
	if (locate(base, point[(*i)]) == -1)
		return (0);
	if (locate(base, point[(*i)+ 1]) == -1)
		return (0);
	*(color) = locate(base, point[(*i)++]);
	*(color) = *(color) * 16 +locate(base, point[(*i)]);
	return (1);
}

int	get_color(char *point, int i)
{
	int		place;
	int		shift;
	int		color;
	int		full_rgba;

	place = 0;
    full_rgba = 0;
	if (ft_strlen(&point[i]) != 11)
		return (-3);//,0x12345678
	if (ft_strncmp(&point[i],",0x", 3))
		return (-2);
	i += 3;
	while (place < 4)
	{
		if (!single_color(point, &i, &color))
			return (-4);
		full_rgba = full_rgba << 8 | color;
		place++;
	}
	return (full_rgba);
}

int main ()
{
    char *r = ",0xFFFFFFFF";

    int color = 0;
    printf("%i\n", get_color(r, 0));
}