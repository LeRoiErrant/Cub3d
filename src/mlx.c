#include "../includes/cub3d.h"
/*

? Testing

*/
int	exit_cub(t_cub3d *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	free_cub(cub);
	exit(cub->error.num);
}

int	key_event(int key, t_cub3d *cub)
{
	if (key == KEY_ESC)
		exit_cub(cub);
	printf("key = %d\n", key);
	return (0);
}

int	key_hook(t_cub3d *cub)
{
	mlx_hook(cub->win, 17, 0L << 0, &exit_cub, cub);
	mlx_hook(cub->win, 2, 1L << 0, &key_event, cub);
	return (0);
}

int	mouse_hook(t_cub3d *cub)
{
	mlx_hook(cub->win, M_LEFT, 0L << 0, &exit_cub, cub);
	mlx_hook(cub->win, M_RIGHT, 1L << 0, &key_event, cub);
	return (0);
}

void	mlx_test(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCREEN_W, SCREEN_H, "cub3d");
	cub->img.img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	cub->img.addr = mlx_get_data_addr(&cub->img.img,
			&cub->img.bpp, &cub->img.ll, &cub->img.endian);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
//	mlx_mouse_hook(cub->win, &mouse_hook, cub);
//	mlx_key_hook(cub->win, &key_hook, cub);
	mlx_loop_hook(cub->mlx, &key_hook, cub);
	init_textures(cub);
	mlx_loop(cub->mlx);
}
