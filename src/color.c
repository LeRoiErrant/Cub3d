#include "../includes/cub3d.h"

static int	shade_color(int color, double divide)
{
	if (divide <= 1.)
		return (color);
	return (((int)(((0xFF0000 & color) >> 16) / divide) << 16)
		+ ((int)(((0x00FF00 & color) >> 8) / divide) << 8)
		+ ((int)((0x0000FF & color) / divide)));
}

int	distance_shade(int color, double distance)
{
	return (shade_color(color, distance / 2.));
}

static int	get_color(t_img *img, int x, int y)
{
	char	*color;

	color = img->addr + (y * img->ll + x * (img->bpp / 8));
	return (*(int *)color);
}

int	get_tex_color(t_cub3d *cub)
{
	cub->o_tex.y = (int) cub->o_tex.pos & (TEXTURE_H - 1);
	cub->o_tex.pos += cub->o_tex.step;
	if (!cub->ray.door.tex)
		cub->o_tex.color = get_color(cub->tex[cub->ray.side], cub->o_tex.x, cub->o_tex.y);
	else
		cub->o_tex.color = get_color(cub->tex[cub->ray.door.tex], cub->o_tex.x, cub->o_tex.y);
	return (cub->o_tex.color);
}
