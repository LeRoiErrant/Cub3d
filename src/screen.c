#include "../includes/cub3d.h"

static t_img	init_screen(t_cub3d *cub)
{
	t_img	screen;
	
	screen.img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	screen.addr = mlx_get_data_addr(screen.img, &screen.bpp, &screen.ll, &screen.endian);
	return (screen);
}

static t_img	init_minimap(t_cub3d *cub)
{
	t_img	map;

	map.img = mlx_new_image(cub->mlx, 130, 130);
	map.addr = mlx_get_data_addr(map.img, &map.bpp, &map.ll, &map.endian);
	return (map);
}

void	init_screen_win(t_cub3d *cub)
{
	cub->screen = init_screen(cub);
	cub->minimap = init_minimap(cub);
}