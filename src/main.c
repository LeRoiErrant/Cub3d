#include "../includes/cub3d.h"

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
	mlx_hook(cub->win.ptr, 17, 0L << 0, &esc_win, cub);
	mlx_hook(cub->win.ptr, 2, 1L << 0, &key_event, cub);
	return (0);
}

int	main(void)
{
	t_cub3d	cub;

	//! temporary
	int	map[5][6] =
	{
		{1,1,1,1,1,1},
		{1,0,0,1,0,1},
		{1,0,1,0,0,1},
		{1,1,0,0,0,1},
		{1,1,1,1,1,1},
	};
	(void) map;
	cub.pos.x = 3.0;
	cub.pos.y = 4.0;
	cub.dir.x = -1.0;
	cub.dir.y = 0.0;
	cub.plane.x = 0;
	cub.plane.y = 0.66;
	cub.reset_buffer = 0;
	cub.mlx.ptr = mlx_init();
	cub.win.ptr = mlx_new_window(cub.mlx.ptr, SCREEN_W, SCREEN_H, "cub3d");
	cub.img.ptr = mlx_new_image(cub.mlx.ptr, SCREEN_W, SCREEN_H);
	cub.img.addr = mlx_get_data_addr(cub.img.ptr, &cub.img.bpp, &cub.img.line_len, &cub.img.endian);
	mlx_put_image_to_window(cub.mlx.ptr, cub.win.ptr, cub.img.ptr, 0, 0);
	mlx_loop_hook(cub.mlx.ptr, &key_hook, &cub);
	mlx_loop(cub.mlx.ptr);
	return (0);
}
