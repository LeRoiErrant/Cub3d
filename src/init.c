#include "../includes/cub3d.h"

static void	init_config(t_cub3d *cub)
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

//TODO Valeur de retour pour le malloc des erreurs ?
void	init_cub(t_cub3d *cub)
{
	cub->dir.x = -1.0;
	cub->dir.y = 0.0;
	cub->plane.x = 0;
	cub->plane.y = 0.66;
	cub->reset_buffer = 0;
	cub->map = NULL;
	cub->tmp = NULL;
	cub->error.num = SUCCESS;
	init_errors(cub);
	init_config(cub);
}

void	init_buffer(t_img *buf, t_cub3d *cub)
{
	buf->img = mlx_new_image(cub->mlx, 1, SCREEN_H);
	buf->addr = mlx_get_data_addr(buf->img, &buf->bpp, &buf->ll, &buf->endian);
}

static int	init_img(t_img *img, t_cub3d *cub)
{
	if (!img)
		return (cub_error(E_MALLOC, STDERR_FILENO, cub));
	img->img = mlx_xpm_file_to_image(cub->mlx, cub->config.path_n, &img->w, &img->h);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
	return (SUCCESS);
}

void	init_textures(t_cub3d *cub)
{
	cub->textures.north = ft_calloc(1, sizeof(t_img));
	cub->textures.south = ft_calloc(1, sizeof(t_img));
	cub->textures.east = ft_calloc(1, sizeof(t_img));
	cub->textures.west = ft_calloc(1, sizeof(t_img));
	init_img(cub->textures.north, cub);
	init_img(cub->textures.south, cub);
	init_img(cub->textures.east, cub);
	init_img(cub->textures.west, cub);
}
