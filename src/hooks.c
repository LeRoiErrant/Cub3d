#include "../includes/cub3d.h"

int	exit_cub(t_cub3d *cub)
{
	int	i;

	i = -1;
	while (++i < TEX_END)
	{
		mlx_destroy_image(cub->mlx, cub->tex[i]->img);
		free(cub->tex[i]);
	}
	mlx_destroy_window(cub->mlx, cub->win);
	free_cub(cub);
	exit(cub->errnum);
}

int	key_down(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_ESC)
		exit_cub(cub);
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		check_movement(keycode, cub);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		rotate_camera(keycode, cub);
	return (0);
}

int	key_release(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_W)
		cub->engine.move.up = 0;
	if (keycode == KEY_S)
		cub->engine.move.down = 0;
	if (keycode == KEY_A)
		cub->engine.move.left = 0;
	if (keycode == KEY_D)
		cub->engine.move.right = 0;
	if (keycode == KEY_RIGHT)
		cub->engine.rot.right = 0;
	if (keycode == KEY_LEFT)
		cub->engine.rot.left = 0;
	if (keycode == KEY_E)
		open_door(cub);
	return (0);
}

int	mouse_move(int x, int y, t_cub3d *cub)
{
	float	rotspeed;
	float	olddirx;
	float	oldplanex;

	(void) y;
	rotspeed = ((float)(x - SCREEN_W / 2)) / 500.0;
	olddirx = cub->dir.x;
	oldplanex = cub->plane.x;
	cub->dir.x = cub->dir.x * cos(-rotspeed) - cub->dir.y * sin(-rotspeed);
	cub->dir.y = olddirx * sin(-rotspeed) + cub->dir.y * cos(-rotspeed);
	cub->plane.x = cub->plane.x * cos(-rotspeed) - cub->plane.y * sin(-rotspeed);
	cub->plane.y = oldplanex * sin(-rotspeed) + cub->plane.y * cos(-rotspeed);
	mlx_mouse_move(cub->win, (int)(SCREEN_W / 2), (int)(SCREEN_H / 2));
	return (0);
}

int	mouse_down(int button, int x, int y, t_cub3d *cub)
{
	(void) x;
	(void) y;
	if (button == M_LEFT)
		cub->shoot = 1;
	return (SUCCESS);
}
