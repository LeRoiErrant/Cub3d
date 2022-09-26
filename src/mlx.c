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
