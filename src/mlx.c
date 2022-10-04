#include "../includes/cub3d.h"

int	exit_cub(t_cub3d *cub)
{
//	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_image(cub->mlx, cub->buf.img);
	mlx_destroy_image(cub->mlx, cub->textures.north->img);
	mlx_destroy_image(cub->mlx, cub->textures.east->img);
	mlx_destroy_image(cub->mlx, cub->textures.south->img);
	mlx_destroy_image(cub->mlx, cub->textures.west->img);
	mlx_destroy_window(cub->mlx, cub->win);
	free_cub(cub);
	exit(cub->errnum);
}

int	key_down(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_ESC)
		exit_cub(cub);
	return (0);
}

int	key_release(int keycode, t_cub3d *cub)
{
	(void) keycode;
	(void) cub;
	return (0);
}

int	update(t_cub3d *cub)
{
	raycasting(cub);
	return (0);
}

void	loop(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCREEN_W, SCREEN_H, "cub3d");
	init_buffer(&cub->buf, cub);
	init_textures(cub);
	mlx_hook(cub->win, ON_KEYDOWN, 0, key_down, cub);
	mlx_hook(cub->win, ON_KEYUP, 0, key_release, cub);
	mlx_hook(cub->win, ON_DESTROY, 0, exit_cub, cub);
	mlx_loop_hook(cub->mlx, &update, cub);
	mlx_loop(cub->mlx);
}
