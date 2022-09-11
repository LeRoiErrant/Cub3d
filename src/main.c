#include "../includes/cub3d.h"

//? testing

int	esc_win(t_cub3d *cub)
{
	(void) cub;
	exit(0);
}

int	key_event(int key, t_cub3d *cub)
{
	if (key == 53)
		esc_win(cub);
	return (0);
}

int	key_hook(t_cub3d *cub)
{
	mlx_hook(cub->win_ptr, 17, 0L << 0, esc_win, cub);
	mlx_hook(cub->win_ptr, 2, 1L << 0, key_event, cub);
	return (0);
}

int	main(void)
{
	t_cub3d	cub;

	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, 1920, 1080, "cub3d");
	cub.img = mlx_new_image(cub.mlx_ptr, 1920, 1080);
	cub.img_data = mlx_get_data_addr(cub.img, &cub.bpp, &cub.size_line, &cub.endian);
	mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr, cub.img, 0, 0);
	mlx_loop_hook(cub.mlx_ptr, key_hook, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
