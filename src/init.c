#include "../includes/cub3d.h"

static void	init_config(t_cub3d *cub)
{
	cub->config.ceiling.red = -1;
	cub->config.ceiling.green = -1;
	cub->config.ceiling.blue = -1;
	cub->config.floor.red = -1;
	cub->config.floor.green = -1;
	cub->config.floor.blue = -1;
	cub->config.path[TEX_NO] = NULL;
	cub->config.path[TEX_WE] = NULL;
	cub->config.path[TEX_SO] = NULL;
	cub->config.path[TEX_EA] = NULL;
	cub->config.movespeed = 0.02;
	cub->config.rotspeed = 0.02;
	cub->config.map_w = 0;
	cub->config.map_h = 0;
}

void	init_buffer(t_img *buf, t_cub3d *cub)
{
	buf->img = mlx_new_image(cub->mlx, 1, SCREEN_H);
	buf->addr = mlx_get_data_addr(buf->img, &buf->bpp, &buf->ll, &buf->endian);
}

void	init_cub(t_cub3d *cub)
{
	cub->dir.x = 0.0;
	cub->dir.y = 0.0;
	cub->plane.x = 0;
	cub->plane.y = 0;
	cub->reset_buffer = 0;
	cub->map = NULL;
	cub->tmp = NULL;
	cub->errnum = SUCCESS;
	cub->color = 0;
	cub->gun_frame = TEX_GUN0;
	cub->shoot = 0;
	cub->framecount = 0;
	cub->g_framecount = 0;
	cub->appear = 0;
	init_config(cub);
}

void	init_engine(t_cub3d *cub)
{
	cub->engine.move.up = 0;
	cub->engine.move.left = 0;
	cub->engine.move.down = 0;
	cub->engine.move.right = 0;
	cub->engine.rot.left = 0;
	cub->engine.rot.right = 0;
	cub->engine.delta.x = 0;
	cub->engine.delta.y = 0;
}
