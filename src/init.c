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

int	init_cub(t_cub3d *cub)
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
	cub->door_side = TEX_SIDE0;
	cub->shoot = 0;
	cub->framecount = 0;
	cub->g_framecount = 0;
	cub->appear = 0;
	init_config(cub);
	return (SUCCESS);
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

static void	load_tex(t_cub3d *cub, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx, path, &tex->w, &tex->h);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->ll, &tex->endian);
}

t_img	init_bground(t_cub3d *cub)
{
	t_img	bground;

	cub->config.floor.rgb = create_trgb(cub->config.floor);
	cub->config.ceiling.rgb = create_trgb(cub->config.ceiling);
	bground.img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	bground.addr = mlx_get_data_addr(bground.img, &bground.bpp, &bground.ll, &bground.endian);
	cub->bground = bground;
	return (bground);
}

int	init_tex(t_cub3d *cub)
{
	int	i;
	int	check;

	i = -1;
	check = SUCCESS;
	while (++i < TEX_END)
	{
		cub->tex[i] = ft_calloc(1, sizeof(t_img));
		load_tex(cub, cub->tex[i], cub->config.path[i]);
	}
	return (check);
}
