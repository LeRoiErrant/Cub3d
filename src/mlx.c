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
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = cub->dir.x;
      cub->dir.x = cub->dir.x * cos(-cub->config.rotspeed) - cub->dir.y * sin(-cub->config.rotspeed);
      cub->dir.y = oldDirX * sin(-cub->config.rotspeed) + cub->dir.y * cos(-cub->config.rotspeed);
      double oldPlaneX = cub->plane.x;
      cub->plane.x = cub->plane.x * cos(-cub->config.rotspeed) - cub->plane.y * sin(-cub->config.rotspeed);
      cub->plane.y = oldPlaneX * sin(-cub->config.rotspeed) + cub->plane.y * cos(-cub->config.rotspeed);
    }
    //rotate to the left
    if (keycode == KEY_LEFT)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = cub->dir.x;
      cub->dir.x = cub->dir.x * cos(cub->config.rotspeed) - cub->dir.y * sin(cub->config.rotspeed);
      cub->dir.y = oldDirX * sin(cub->config.rotspeed) + cub->dir.y * cos(cub->config.rotspeed);
      double oldPlaneX = cub->plane.x;
      cub->plane.x = cub->plane.x * cos(cub->config.rotspeed) - cub->plane.y * sin(cub->config.rotspeed);
      cub->plane.y = oldPlaneX * sin(cub->config.rotspeed) + cub->plane.y * cos(cub->config.rotspeed);
    }
}

void	update_pos(t_cub3d *cub)
{
	t_dpos	move;

	printf("W: %i A: %i S: %i D: %i \r", cub->move.w, cub->move.a, cub->move.s, cub->move.d);
	if (cub->move.w)
    {
		move.x = cub->dir.x * cub->config.movespeed;
		move.y = cub->dir.y * cub->config. movespeed;
    }
    if (cub->move.s)
    {
      	move.x = -1 * cub->dir.x * cub->config.movespeed;
		move.y = -1 * cub->dir.y * cub->config.movespeed;
    }
	if (cub->move.a)
    {
      	move.x = -1 * cub->dir.y * cub->config.movespeed;
		move.y = cub->dir.x * cub->config.movespeed;
	 /*if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;*/
    }
	if (cub->move.d)
    {
      	move.x = cub->dir.y * cub->config.movespeed;
		move.y = -1 * cub->dir.x * cub->config.movespeed;
	 /*if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;*/
    }
	if (cub->map[(int) (cub->pos.x + move.x)][(int) (cub->pos.y + move.y)] != '1')
	{
		cub->pos.x += move.x;
		cub->pos.y += move.y;
		cub->pc.x = cub->pos.x * 10;
		cub->pc.y = cub->pos.y * 10;
		//printf("X: %f | Y: %f\n   pc.x: %i | pc.y: %i\n", cub->pos.x, cub->pos.y, (int) cub->pc.x, (int) cub->pc.y);
	}
}

void	check_movement(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_W)
		cub->move.w = 1;
    if (keycode == KEY_S)
		cub->move.s = 1;
	if (keycode == KEY_A)
		cub->move.a = 1;
	if (keycode == KEY_D)
		cub->move.d = 1;
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
		cub->move.w = 0;
    if (keycode == KEY_S)
		cub->move.s = 0;
	if (keycode == KEY_A)
		cub->move.a = 0;
	if (keycode == KEY_D)
		cub->move.d = 0;
	return (0);
}

int	update(t_cub3d *cub)
{
	raycasting(cub);
	minimap(cub);
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
