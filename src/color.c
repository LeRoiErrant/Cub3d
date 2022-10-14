#include "../includes/cub3d.h"

int	shade_color(int color, double divide)
{
	if (divide <= 1.)
		return (color);
	return (((int)(((0xFF0000 & color) >> 16) / divide) << 16)
		+ ((int)(((0x00FF00 & color) >> 8) / divide) << 8)
		+ ((int)((0x0000FF & color) / divide)));
}

int	distance_shade(int color, double distance)
{
	return (shade_color(color, distance / 4.5));
}

/*int	get_tex_color(t_img *tex, t_ipos *pos)
{
	if (pos->x >= 0 && pos->x < tex->w && pos->y >= 0 && pos->y < tex->h)
	{
		return (*(int*)(tex->img + (4 * tex->w * pos->y) + (4 * pos->x)));
	}
	return (0x0);
}*/