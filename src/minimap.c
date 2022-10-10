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

void d_pc(t_img *img, int x, int y, int color)
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

/*void	minimap(t_cub3d *cub)
{
	t_ipos	test;
	t_img	minimap;
	t_ipos	cell;
	t_ipos	coord;
	int		color;

	test.x = 0;
	test.y = 0;
	minimap.img = mlx_new_image(cub->mlx, SCREEN_W / 8, SCREEN_H);
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
	d_pc(&minimap, (int) cub->pc.x - 3, (int) cub->pc.y - 3, HEX_GREEN);
	mlx_put_image_to_window(cub->mlx, cub->win, minimap.img, 0, 0);
	mlx_destroy_image(cub->mlx, minimap.img);
}*/

void	get_start(t_cub3d *cub, t_ipos *start)
{
	start->x = (int) cub->pos.x - 5;
	start->y = (int) cub->pos.y - 5;
}

int	get_map_color(t_cub3d *cub, int x, int y)
{
	(void) cub;
	(void) x;
	(void) y;
	if (cub->map[x][y] == '1')
		return (HEX_DARK_RED);
	else if (cub->map[x][y] != '.')
		return (0x00AAAAAA);
	else
		return (0x00000000);
	return (HEX_RED);
}

int	is_not_in_map(t_cub3d *cub, t_ipos start, t_ipos cell)
{
	if (start.x + cell.x < 0 || start.x + cell.x >= cub->config.map_h)
		return (1);
	else if (start.y + cell.y < 0 || start.y + cell.y >= cub->config.map_w)
		return (1);
	else
		return (0);
}

void	minimap(t_cub3d *cub)
{
	t_img	minimap;
	t_ipos	start;
	t_ipos	cell;
	t_ipos	coord;
	int		color;

	minimap.img = mlx_new_image(cub->mlx, 120, 120);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bpp, &minimap.ll, &minimap.endian);
	get_start(cub, &start);
	coord.x = 0;
	cell.x = -1;
	while (++cell.x < 11) 
	{
		coord.y = 0;
		cell.y = -1;
		while (++cell.y < 11)
		{
			if (is_not_in_map(cub, start, cell))
				color = 0x00000000;
			else
				color = get_map_color(cub, start.x + cell.x, start.y + cell.y);
			d_cell(&minimap, coord.x, coord.y, color);
			coord.y += 10;
		}
		coord.x += 10;
	}
	d_pc(&minimap, 50 + ((int) cub->pc.x % 10), 50 + ((int) cub->pc.y % 10), HEX_GREEN);
	mlx_put_image_to_window(cub->mlx, cub->win, minimap.img, 0, 0);
	mlx_destroy_image(cub->mlx, minimap.img);
}