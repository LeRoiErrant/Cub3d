#include "../includes/cub3d.h"

static int	shade_color(int color, double divide)
{
	if (divide <= 1.)
		return (color);
	return (((int)(((0xFF0000 & color) >> 16) / divide) << 16)
		+ ((int)(((0x00FF00 & color) >> 8) / divide) << 8)
		+ ((int)((0x0000FF & color) / divide)));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_color(t_img *img, int x, int y)
{
	char	*color;

	color = img->addr + (y * img->ll + x * (img->bpp / 8));
	return (*(int *)color);
}

int	distance_shade(int color, double distance)
{
	return (shade_color(color, distance / 2.));
}