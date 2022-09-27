#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub;

	if (argc != 2)
		return (cub_error(E_ARGC, STDERR_FILENO));
	init_cub(&cub);
	init_config(&cub);
	if (parsing(argv, &cub) != SUCCESS)
		return (cub_error(E_FAILURE, -1));
	cub.mlx.ptr = mlx_init();
	cub.win.ptr = mlx_new_window(cub.mlx.ptr, SCREEN_W, SCREEN_H, "cub3d");
	cub.img.ptr = mlx_new_image(cub.mlx.ptr, SCREEN_W, SCREEN_H);
	cub.img.addr = mlx_get_data_addr(cub.img.ptr, &cub.img.bpp, &cub.img.ll, &cub.img.endian);
	mlx_put_image_to_window(cub.mlx.ptr, cub.win.ptr, cub.img.ptr, 0, 0);
	mlx_loop_hook(cub.mlx.ptr, &key_hook, &cub);
	mlx_loop(cub.mlx.ptr);
	return (SUCCESS);
}
