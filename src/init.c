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
	cub->errnum = SUCCESS;
}

void	init_config(t_cub3d *cub)
{
	cub->config.ceiling.red = -1;
	cub->config.ceiling.green = -1;
	cub->config.ceiling.blue = -1;
	cub->config.floor.red = -1;
	cub->config.floor.green = -1;
	cub->config.floor.blue = -1;
	cub->config.path_n = NULL;
	cub->config.path_e = NULL;
	cub->config.path_s = NULL;
	cub->config.path_w = NULL;
	cub->config.movespeed = 0.1;
	cub->config.rotspeed = 0.05;
	cub->config.map_w = 0;
	cub->config.map_h = 0;
}
