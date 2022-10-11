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
	free(cub->textures.north);
	free(cub->textures.south);
	free(cub->textures.east);
	free(cub->textures.west);
	free_cub(cub);
	exit(cub->errnum);
}

void	rotate_camera(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_RIGHT)
		cub->rot.right = 1;
    if (keycode == KEY_LEFT)
		cub->rot.left = 1;
}

void	update_cam(t_cub3d *cub)
{
	if (cub->rot.right)
    {
      double oldDirX = cub->dir.x;
      cub->dir.x = cub->dir.x * cos(-cub->config.rotspeed) - cub->dir.y * sin(-cub->config.rotspeed);
      cub->dir.y = oldDirX * sin(-cub->config.rotspeed) + cub->dir.y * cos(-cub->config.rotspeed);
      double oldPlaneX = cub->plane.x;
      cub->plane.x = cub->plane.x * cos(-cub->config.rotspeed) - cub->plane.y * sin(-cub->config.rotspeed);
      cub->plane.y = oldPlaneX * sin(-cub->config.rotspeed) + cub->plane.y * cos(-cub->config.rotspeed);
    }
    //rotate to the left
    if (cub->rot.left)
    {
      double oldDirX = cub->dir.x;
      cub->dir.x = cub->dir.x * cos(cub->config.rotspeed) - cub->dir.y * sin(cub->config.rotspeed);
      cub->dir.y = oldDirX * sin(cub->config.rotspeed) + cub->dir.y * cos(cub->config.rotspeed);
      double oldPlaneX = cub->plane.x;
      cub->plane.x = cub->plane.x * cos(cub->config.rotspeed) - cub->plane.y * sin(cub->config.rotspeed);
      cub->plane.y = oldPlaneX * sin(cub->config.rotspeed) + cub->plane.y * cos(cub->config.rotspeed);
    }
}

void	valid_move(t_cub3d *cub, t_dpos move)
{
	cub->pos.x += move.x;
	cub->pos.y += move.y;
	cub->pc.x = cub->pos.x * 10;
	cub->pc.y = cub->pos.y * 10;
}

void	update_pos(t_cub3d *cub)
{
	t_dpos	move;

	printf("hello world\r");
	//printf("W: %i A: %i S: %i D: %i \r", cub->move.up, cub->move.left, cub->move.down, cub->move.right);
	if (cub->move.up)
    {
		move.x = cub->dir.x * cub->config.movespeed;
		move.y = cub->dir.y * cub->config. movespeed;
    }
    if (cub->move.down)
    {
      	move.x = -1 * cub->dir.x * cub->config.movespeed;
		move.y = -1 * cub->dir.y * cub->config.movespeed;
    }
	if (cub->move.left)
    {
      	move.x = -1 * cub->dir.y * cub->config.movespeed;
		move.y = cub->dir.x * cub->config.movespeed;
    }
	if (cub->move.right)
    {
      	move.x = cub->dir.y * cub->config.movespeed;
		move.y = -1 * cub->dir.x * cub->config.movespeed;
    }
	if (cub->map[(int) (cub->pos.x + move.x)][(int) (cub->pos.y + move.y)] != '1')
		valid_move(cub, move);
}

void	check_movement(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_W)
		cub->move.up = 1;
    if (keycode == KEY_S)
		cub->move.down = 1;
	if (keycode == KEY_A)
		cub->move.left = 1;
	if (keycode == KEY_D)
		cub->move.right = 1;
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
		cub->move.up = 0;
    if (keycode == KEY_S)
		cub->move.down = 0;
	if (keycode == KEY_A)
		cub->move.left = 0;
	if (keycode == KEY_D)
		cub->move.right = 0;
	if (keycode == KEY_RIGHT)
		cub->rot.right = 0;
    if (keycode == KEY_LEFT)
		cub->rot.left = 0;
	return (0);
}

int	update(t_cub3d *cub)
{
	raycasting(cub);
	minimap(cub);
	update_cam(cub);
	update_pos(cub);
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
