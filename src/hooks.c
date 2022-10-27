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

int	key_down(int key, t_cub3d *cub)
{
	if (key == KEY_ESC)
		exit_cub(cub);
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		check_movement(key, cub);
	if (key == KEY_RIGHT || key == KEY_LEFT)
		rotate_camera(key, cub);
	if (key == KEY_SPACE)
	{
		cub->mouse_enable = (cub->mouse_enable + 1) % 2;
		if (cub->mouse_enable == 0)
			mlx_mouse_show();
		else
		{
			mlx_mouse_hide();
			mlx_mouse_move(cub->win, (int)(SCR_W / 2), (int)(SCR_H / 2));
		}
	}
	if (key == KEY_SHIFT)
		cub->config.movespeed *= 2;
	return (0);
}

int	key_release(int key, t_cub3d *cub)
{
	if (key == KEY_W)
		cub->engine.move.up = 0;
	if (key == KEY_S)
		cub->engine.move.down = 0;
	if (key == KEY_A)
		cub->engine.move.left = 0;
	if (key == KEY_D)
		cub->engine.move.right = 0;
	if (key == KEY_RIGHT)
		cub->engine.rot.right = 0;
	if (key == KEY_LEFT)
		cub->engine.rot.left = 0;
	if (key == KEY_E)
		open_door(cub);
	if (key == KEY_SHIFT)
		cub->config.movespeed /= 2;
	return (0);
}

int	mouse_move(int x, int y, t_cub3d *cub)
{
	float	rspeed;
	float	olddirx;
	float	oldplanex;

	(void) y;
	if (!cub->mouse_enable)
		return (0);
	rspeed = ((float)(x - SCR_W / 2)) / 500.0;
	olddirx = cub->dir.x;
	oldplanex = cub->plane.x;
	cub->dir.x = cub->dir.x * cos(-rspeed) - cub->dir.y * sin(-rspeed);
	cub->dir.y = olddirx * sin(-rspeed) + cub->dir.y * cos(-rspeed);
	cub->plane.x = cub->plane.x * cos(-rspeed) - cub->plane.y * sin(-rspeed);
	cub->plane.y = oldplanex * sin(-rspeed) + cub->plane.y * cos(-rspeed);
	mlx_mouse_move(cub->win, (int)(SCR_W / 2), (int)(SCR_H / 2));
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
