#include "../includes/cub3d.h"

void	init_cub(t_cub3d *cub)
{
	cub->pos.x = 4.0;
	cub->pos.y = 4.0;
	cub->dir.x = -1.0;
	cub->dir.y = 0.0;
	cub->plane.x = 0;
	cub->plane.y = 0.66;
	cub->reset_buffer = 0;
}

void	init_config(t_cub3d *cub)
{
	cub->config.ceiling.red = 0;
	cub->config.ceiling.green = 0;
	cub->config.ceiling.blue = 0;
	cub->config.floor.red = 0;
	cub->config.floor.green = 0;
	cub->config.floor.blue = 0;
	cub->config.path_n = NULL;
	cub->config.path_e = NULL;
	cub->config.path_s = NULL;
	cub->config.path_w = NULL;
	cub->config.movespeed = 0.1;
	cub->config.rotspeed = 0.05;
}
