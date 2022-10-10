#include "../includes/cub3d.h"

void d_cell(t_img *img, int x, int y, int color)
{
	t_ipos 	i;
	int		length;

	length = 10;
	i.x = x - 1;
	if (length <= 0)
		return;
	while (++i.x - x != length)
	{
		i.y = y - 1;
		while (++i.y - y != length)
			my_mlx_pixel_put(img, i.x, i.y, color);
	}
}

void	minimap(t_cub3d *cub)
{
	t_ipos	test;
	t_img	minimap;
	t_ipos	cell;
	t_ipos	coord;
	int		color;

	test.x = 0;
	test.y = 0;
	minimap.img = mlx_new_image(cub->mlx, SCREEN_W / 4, SCREEN_H);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bpp, &minimap.ll, &minimap.endian);
	coord.x = 0;
	cell.x = -1;
	while (cub->map[++cell.x]) 
	{
		cell.y = -1;
		coord.y = 0;
		while (cub->map[cell.x][++cell.y])
		{
			if (cub->map[cell.x][cell.y] == '1')
				color = HEX_DARK_RED;
			else if (cub->map[cell.x][cell.y] != '.')
				color = 0x00AAAAAA;
			else if (cub->map[cell.x][cell.y] == '.')
				color = 0x00000000;
			d_cell(&minimap, coord.x, coord.y, color);
			coord.y += 10;
		}
		coord.x += 10;
	}
	d_cell(&minimap, (int) cub->pc.x, (int) cub->pc.y, HEX_GREEN);
	mlx_put_image_to_window(cub->mlx, cub->win, minimap.img, 0, 0);
	mlx_destroy_image(cub->mlx, minimap.img);
}