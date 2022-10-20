#include "../includes/cub3d.h"

void	draw_dir(t_img *img, t_cub3d *cub)
{
	t_ipos	i;
	t_ipos	d;

	d.x = (int) 5 * cub->dir.x;
	d.y = (int) 5 * cub->dir.y;
	i.y = -1;
	while (++i.y < 2)
	{
		i.x = -1;
		while (++i.x < 2)
			my_mlx_pixel_put(img, i.x + 59 + d.y, i.y + 59 + d.x, 0x00000000);
	}
}

void	draw_pc(t_img *img, int color, t_cub3d *cub)
{
	t_ipos	i;
	int		is_it;

	draw_dir(img, cub);
	i.y = -1;
	while (++i.y < 10)
	{
		i.x = -1;
		while (++i.x < 10)
		{
			is_it = in_circle((float)i.x, (float)i.y);
			if (is_it)
				my_mlx_pixel_put(img, i.x + 55, i.y + 55, color);
		}
	}
}

void	draw_frame(t_img *img)
{
	t_ipos	i;

	i.x = -1;
	while (++i.x < 130)
	{
		i.y = -1;
		while (++i.y < 130)
		{
			if (i.x < 10 || i.y < 10 || i.x >= 120 || i.y >= 120)
				my_mlx_pixel_put(img, i.x, i.y, 0xFF000000);
			else if (i.x < 20 || i.y < 20 || i.x >= 110 || i.y >= 110)
				my_mlx_pixel_put(img, i.x, i.y, 0x00FFD700);
		}
	}
}

void	minimap(t_cub3d *cub)
{
	t_ipos	start;
	t_ipos	cell;
	t_ipos	coord;
	int		color;
	t_ipos	mod;

	get_start(cub, &start);
	mod.x = (int) cub->pc.x % 10;
	mod.y = (int) cub->pc.y % 10;
	coord.x = 10;
	cell.x = -1;
	while (++cell.x < 11)
	{
		coord.y = 10;
		cell.y = -1;
		while (++cell.y < 11)
		{
			if (is_not_in_map(cub, start, cell))
				color = 0x00000000;
			else
				color = get_map_color(cub, start.x + cell.x, start.y + cell.y);
			d_cell(&cub->minimap, coord.y - mod.y, coord.x - mod.x, color);
			coord.y += 10;
		}
		coord.x += 10;
	}
	draw_pc(&cub->minimap, HEX_GREEN, cub);
	draw_frame(&cub->minimap);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img, 0, 0);
}
